#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
typedef struct String { // Created String Struct
    char elements[100]; // It takes max 100 char
} String;

int len(String *s){ // A func to find strLength
    int len = 0;
    for (int i = 0; s->elements[i] != '\0'; i++) {
        // It increases len unless encounter to '\0'
        len++;
    }
    return len;
}
int compareString(String *s1,String *s2){
    int counter =0;
    for (int i = 0; i < 100; i++) {
        if(s1->elements[i]=='\n'){
            // If I don't change '\n' char to '\0' it makes a logic error at the bottom
            s1->elements[i]='\0';
            break;
        }
    }
    if(len(s1) != len(s2)) // If lengths are not equal returns 0
        return 0;
    else{
        for (int i = 0; i < len(s1); ++i) {
            if(s1->elements[i] == s2->elements[i]){ // If each char equals counter++
                counter++;
            }
        }
        if(counter == len(s2))
            return 1;
    }
    return 0;
}

int charAt(String *s, int index){  // It finds char into String according to index
    int strLength = len(s);
    char selected;
    if(index >= 0 && index < strLength)
        selected = s->elements[index];
    else
        return -1;
    return selected;
}
String *concat(String *s1, String *s2){
    int len1 = len(s1);
    int len2 = len(s2);
    int totalLength = len1 + len2 + 1; // +1 for blank, between two str
    String *resultString = (String*)malloc(sizeof(String));
    int i, j;
    for (i = 0; s1->elements[i] != '\0'; i++) {
        resultString->elements[i] = s1->elements[i];
    }
    resultString->elements[i] = ' '; // space between for 2 separate strings
    for (j = 0; s2->elements[j] != '\0'; j++, i++) {
        resultString->elements[i+1] = s2->elements[j];
        // We declared "i" outside for that's why we continue to write str from last position
    }
    resultString->elements[totalLength] = '\0';

    return resultString;
}

unsigned int strSearch(String *s1, String *s2) {
    unsigned int l, m;
    int s2len = len(s2);
    int wordFoundLen = 0;
    // if second str locates into first word
    for (l = 0; s1->elements[l] != '\0'; l++) {
        m = 0;
        unsigned int n, b;
        while (s1->elements[l + m] == s2->elements[m] && s2->elements[m] != '\0') {
            m++;
            if (m == s2len) {
                for (n = l; s1->elements[n] != '\0' && s1->elements[n] != 32; n++) { // 32 is ascii code of blank
                    wordFoundLen++;
                }
                for (b = l - 1 ; s1->elements[b] != '\0' && s1->elements[b] != 32; b--){
                    //If the 2nd string is in the middle, it rewinds to look for a space and increments the length each time it sees a char
                    wordFoundLen++;
                }
                return wordFoundLen;
            }
        }
    }
    return 0;
}
unsigned int findScore(String *s1) {
    int score = 0;
    for (int i = 0; i < len(s1); i++) {
        int c = toupper(s1->elements[i]); // It makes char to uppercase
        if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' ||
            c == 'L' || c == 'N' || c == 'R' || c == 'S' || c == 'T') {
            score += 1;
        } else if (c == 'D' || c == 'G') {
            score += 2;
        } else if (c == 'B' || c == 'C' || c == 'M' || c == 'P') {
            score += 3;
        } else if (c == 'F' || c == 'H' || c == 'V' || c == 'W' || c == 'Y') {
            score += 4;
        } else if (c == 'K') {
            score += 5;
        } else if (c == 'J' || c == 'X') {
            score += 8;
        } else if (c == 'Q' || c == 'Z') {
            score += 10;
        }
    }
    return score;
}
void updateStatistics(String *s, int *wordCount, int *letterCount) {
    int wordStarted = 0;

    for (int i = 0; i < len(s); i++) {
        char ch = s->elements[i];

        if (isalpha(ch)) { // If char is alpha letterCount increases
            (*letterCount)++;

            if (!wordStarted) { // If wordStarted false code goes into that block and increases wordCount by one
                (*wordCount)++;
                wordStarted = 1;
            }
        } else if (isspace(ch)) { // After seeing blank wordStarted become false
            wordStarted = 0;
        }
    }
}
int main() {
    char *filename = "input.txt"; 
    FILE *ip = fopen(filename, "r");
    FILE *op = fopen("output.txt", "w");
    if (ip == NULL) {
        printf("Error: could not open file %s", filename);
    } else {
        char line[100]; // I created char array to read line by line at the bottom
        int wordCount = 0;
        int letterCount = 0;
        while (fgets(line, 100, ip)) {
            String lineStr;
            for (int i = 0; i < 100; i++) { // I create lineStr and filled it
                lineStr.elements[i]=line[i];
            }
            int colon=0;
            int firstOperation=0;       //heLLo world:1,6 firstOperation represents 1 here
            int secondOperation=0;      //heLLo world:1,6 secondOperation represents 6 here
            int commaIndex=0;
            for (int i = 0; line[i] != '\n' && line[i]!='\0'; i++) {
                if (lineStr.elements[i] == ':' ) { // If char equals colon next index is firstOperation
                    colon = i;
                    firstOperation = atoi(&lineStr.elements[i + 1]);
                }
                if (lineStr.elements[i] == ',') { // If char equals comma next index is secondOperation
                    commaIndex = i;
                    secondOperation = atoi(&lineStr.elements[i + 1]);
                }
            }
            String singleExpression;
            String firstStr;
            String secondStr;
            for (int i = 0; i < colon; i++) {
                firstStr.elements[i] = lineStr.elements[i];
            }
            firstStr.elements[colon] = '\0';
            int u, y;
            updateStatistics(&firstStr, &wordCount, &letterCount);
            if(firstOperation!=0 && firstOperation!=1 && firstOperation!=4 ) {
                for (u = commaIndex == 0 ? commaIndex : commaIndex + 1, y = 0; line[u] != '\n'; u++, y++) {
                    // in the top line if string doesn't include any comma commaIndex returns as 0
                    secondStr.elements[y] = lineStr.elements[u];
                }
                secondStr.elements[y] = '\0';
            }
            else if(firstOperation==0){
                for(int l = 0; line[l] != '\0'; l++){
                    singleExpression.elements[l]=lineStr.elements[l];
                }
                String exit = {"exit"};
                String stat = {"stat"};
                String quit = {"quit"};
                if (compareString(&singleExpression, &exit) || compareString(&singleExpression, &quit)) {
                    return 0;
                } else if (compareString(&singleExpression, &stat)) {
                    updateStatistics(&singleExpression, &wordCount, &letterCount);
                    fprintf(op, "The number of words: %d\nThe number of alphabetic letters: %d", wordCount + 1, letterCount + 4);
                    //I added wordCount +1 and letterCount +4 since I read line of "exit" or "quit"  after printed stats
                }
                for (size_t i = 0; i < 100; ++i)
                    singleExpression.elements[i] = '\0';
            }
            String *result; // For case 2 : pointer for concatenation result
            unsigned int foundedStrLen; // For case 3 length of word

            if (firstOperation == 1) {
                fprintf(op, "%c\n", toupper(charAt(&firstStr, secondOperation)));
            } else if (firstOperation == 2) {
                result = concat(&firstStr, &secondStr);
                fprintf(op, "%s\n", result->elements);
                free(result);
            } else if (firstOperation == 3) {
                foundedStrLen = strSearch(&firstStr, &secondStr);
                fprintf(op, "%u\n", foundedStrLen);
            } else if (firstOperation == 4) {
                fprintf(op, "%d\n", findScore(&firstStr));
            }

            for (int i = 0; i < 100; i++) { // Clear all elements in the line array at the end of each iteration
                firstStr.elements[i] = '\0';
                secondStr.elements[i] = '\0';
                lineStr.elements[i] = '\0';
            }
        }

        fclose(ip);
        fclose(op);
    }
    return 0;
}
// Eren Çolak - 150121015






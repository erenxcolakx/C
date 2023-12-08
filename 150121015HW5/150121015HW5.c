#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Song {  // Song structure
    char songName[25];
    char duration[7];
    struct Song* next;
};

void addSong(struct Song** head, char* songName, char* duration) {
    struct Song* newSong = (struct Song*)malloc(sizeof(struct Song));  // It allocates a memory for songs
    strcpy(newSong->songName, songName);  // Copies inputed duration and songName to newSong
    strcpy(newSong->duration, duration);
    newSong->next = NULL;
    if (*head == NULL) {
        *head = newSong;   // first element of Linked list
    } else {
        struct Song* current = *head;
        struct Song* prev = NULL;
        while (current != NULL && strcmp(current->duration, duration) < 0) {  // makes time comparison
            /* traverses the list elements if the duration of the current song is shorter than the incoming song
             * until strcmp is 0 or 1 (i.e. until you find the right place for the song duration)*/
            prev = current;
            current = current->next;
        }
        if (prev == NULL) {
            newSong->next = *head;
            *head = newSong;
        } else {
            prev->next = newSong;  // breaks the link and adds the new song at the point of the previous song
            newSong->next = current;  // links the newly added song to the next element
        }
    }
}
void deleteSongByName(struct Song** head, char songNameWillDeleted[], int size) {
    struct Song* current = *head;
    struct Song* pre = NULL;

    while (current != NULL) {
        if (strncmp(current->songName, songNameWillDeleted, size) == 0) {  // compares inputed string and existing strings
            if (pre == NULL) {  // if the song is at the top of the chart
                *head = current->next;  // the leading element is deleted and now the start pointer points to the element pointed to by the deleted element
            } else {  // if the song is in the middle or at the last element
                pre->next = current->next; // previous element of deleted item points next element of deleted element
            }
            free(current); //frees current element
            printf("The song '%s' is deleted from the list!\n", songNameWillDeleted);
            return;
        }
        pre = current;  // shifts back each element
        current = current->next; // also each pointer until current become NULL
    }
    printf("Song '%s' not found\n", songNameWillDeleted);
}
/*void deleteSongById(struct Song** head,int id) { 
    struct Song* current = *head;
    struct Song* prev = NULL;

    if (id == 1) {
        *head = (*head)->next;  // if user wants to delete first element head points second element
        free(current);
        printf("Song deleted\n");
        return;
    }
    for (int i = 1 ;current != NULL && i < id ; i++) {
        //iterates list until i equals id
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Song with ID %d not found\n", id);
        return;
    }
    prev->next = current->next;  // this code breaks the link between prev and current(deletedSong) then links prev to next element
    free(current);
    printf("Song deleted\n");
}*/
void printList(struct Song* head) {
    int id = 1;
    struct Song* current = head;
    printf("The list in duration-time order:\n");
    while (current != NULL) {
        printf("\t\t%u.%s\t%s\n",id,current->songName, current->duration);
        current = current->next;
        id++;
    }
}
int isEmpty(struct Song *head){
    if(head==NULL) // returns isEmpty 1 if linked list is empty
        return 1;
    return 0;
}

void instructions(void){
    printf("Enter your choice:\n"
         " 1 to insert a song into the list.\n"
         " 2 to delete a song from the list.\n"
         " 3 to print the songs in the list.\n"
         " 4 to print the songs to an output file.\n"
         " 5 to end.\n");
}

int main(int argc, char *argv[]) {
    struct Song* head = NULL;  // LinkedList Head element!!
    FILE *ip = fopen(argv[1], "r");
    FILE *op = fopen(argv[2], "w");
    char newSong[100];  // I created this to assign user's music input
    char songNameWillDeleted[25];
    if (ip == NULL) {
        printf("Error: could not open file %s", argv[1]);
    } else {
        char line[100];
        while (fgets(line, 100, ip)) {  // reads
            char *songName = strtok(line, "\t");
            char *duration = strtok(NULL, "\n");
            addSong(&head, songName, duration);
        }
        printList(head);
            unsigned int choice = 0; // user's choice
            while (choice != 5) {
                int id;
                instructions();
                printf("%s", "? ");
                scanf("%u", &choice);
                fflush(stdin);  // I added fflush since I couldn't enter anything after fgets()
                switch (choice) {
                    case 1:  //insert song
                        printf("%s", "Enter a song name with duration ");
                        fgets(newSong, sizeof newSong , stdin);
                        char *songName = strtok(newSong, "\t");
                        char *duration = strtok(NULL, "\n");
                        addSong(&head,songName, duration);
                        printf("Song added to the list\n");
                        break;
                    case 2:  //delete song
                        //if list is not empty
                        if (!isEmpty(head)) {
                            printf("%s", "Enter song name to be deleted: ");
                            fgets(songNameWillDeleted, sizeof songNameWillDeleted, stdin);
                            for (int i = 0; i < 25; i++) {
                                if(songNameWillDeleted[i] == '\n')
                                    songNameWillDeleted[i]='\0'; // I put "\0" sign instead of "\n" since there was an error with \n while comparing strings
                            }
                            deleteSongByName(&head,songNameWillDeleted,25);
                        }
                        else{
                            printf("List is empty");
                        }
                        break;
                    case 3: // print the songs in the list
                        printList(head);
                        break;
                    case 4: // print the songs to an output file
                        id = 1;
                        struct Song* current = head;
                        fprintf(op,"The list in duration-time order:\n");
                        while (current != NULL) {
                            fprintf(op,"\t\t%u.%s\t%s\n",id,current->songName, current->duration);
                            current = current->next;
                            id++;
                        }
                        printf("Output is printed to the file playlist.txt\n");
                        break;
                }
            }

    }
        fclose(ip);
        fclose(op);

    return 0;
}
// Eren Çolak - 150121015


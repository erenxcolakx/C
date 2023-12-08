//Eren Çolak 150121015 Erencan Acýoðlu 150122056
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//This code block is normal struct form of node for Binary Search Tree
struct Node{
    int value;
    int freq;
    struct Node* left;
    struct Node* right;
};

//This code block creates BST by using recursive insert function
struct Node* insert(struct Node* firstNode, struct Node* secondNode){
    if (firstNode == NULL) {
        return secondNode;
    }
    if (firstNode->value < secondNode->value) {
        firstNode->right = insert(firstNode->right, secondNode);
    } else if (firstNode->value > secondNode->value) {
        firstNode->left = insert(firstNode->left, secondNode);
    }
    return firstNode;
}
//This code block is for read and print BST in preorder form
void preorderOutput(struct Node* root,int* count){
	
    if(root != NULL){
		if(count==0){
			//We created these code blocks to make commas proper
			printf("Pre-order traversal of constructed tree : %d",root->value);
            count++;
			preorderOutput(root->left,count);
        	preorderOutput(root->right,count);

		}
		else{
        	printf(", %d",root->value);
        	preorderOutput(root->left,count);
        	preorderOutput(root->right,count);
    	}
    }
}

int main(int argc, char *argv[]) {
	//In this code block we read the inputfile and we can execute in command line
    FILE *ip = fopen(argv[1], "r");
    //This code prints an error message if there is no file or other problems about the file

    if(ip==NULL){
        printf("Error: couldn't open file");
        return 1;
    }

    char row[20];
    struct Node nodeArray[100];
    int count = 0;

    while(fgets(row,sizeof(row), ip ) !=NULL){

        //This code splits inputed values by ","
        char *valueStr = strtok(row,",");
        char *freqStr = strtok(NULL,",");
        //This code converts string to integer
        int value = atoi(valueStr);
        int freq = atoi(freqStr);

        //We created nodes here
		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->value=value;
        newNode->freq=freq;
        newNode->left = NULL;
        newNode->right = NULL;

        //This code assigns nodes to nodeArray which we used for sorting according to frequency
        if (count < 100) {
            nodeArray[count] = *newNode;
            count++;
        } else {
            printf("It can't be more than 100");
            break;
        }
    }
    int i,j;
    // We made bubble sort according to frequance since the highest value of the frequance will be root
    for (i=0 ; i<count ; i++){
        for (j = 1; j < count - i ;j++){
            if(nodeArray[j-1].freq < nodeArray[j].freq){
                struct Node temp = nodeArray[j-1];
                nodeArray[j-1]=nodeArray[j];
                nodeArray[j] = temp;
            }
        }
    }
    /*for (int k = 0; k < count; ++k) {
        printf("freq = %d , value = %d \n", nodeArray[k].freq, nodeArray[k].value);
    }*/

    struct Node *root = &nodeArray[0];
    //This code executes the insert method
    for (int k = 0; k < count; k++) {
        root = insert(root, &nodeArray[k]);
    }
    // This prints the bst according to preorder
    preorderOutput(root,0);
}






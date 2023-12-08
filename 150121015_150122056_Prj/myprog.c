//Eren Çolak 150121015 Erencan Acýoðlu 150122056
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//This code block is normal struct form of node for Binary Search Tree
struct Node {
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
    //We created these code blocks to print in the form of preorder and make commas proper
    if(root != NULL){
        if(count==0){
            printf("Pre-order traversal of constructed tree :(%d, %d)", root->value, root->freq);
            count++;
            preorderOutput(root->left,count);
            preorderOutput(root->right,count);

        }
        else{
            printf(", (%d, %d)", root->value, root->freq);
            preorderOutput(root->left,count);
            preorderOutput(root->right,count);
        }
    }
}
//We search here whether inputed node value is in bst or not
struct Node* search(struct Node* root, int value) {
    if (root == NULL || root->value == value) {
        return root;
    }
    if (root->value < value) {
        return search(root->right, value);
    }
    return search(root->left, value);
}
//This code block is for rotate right
struct Node* rotateRight(struct Node* parent) {

    struct Node* child = parent->left;  // Child should be in the left of parent since we rotate right
    struct Node* rightSideOfChild = child->right;

    child->right = parent; // We put the parent on the right side because value is bigger than the child.
    parent->left = rightSideOfChild;

    return child;
}

//This code block is for rotate left
struct Node* rotateLeft(struct Node* parent) {

    struct Node* child = parent->right; // Child should be in the right of parent since we rotate left
    struct Node* leftSideOfChild = child->left;

    child->left = parent; // We put the parent on the left side because value is smaller than the child.
    parent->right = leftSideOfChild;

    return child;
}

//This code block updates the frequency
struct Node* updateParentbyFrequency(struct Node* root, int value) {

    if (value < root->value) {
        root->left = updateParentbyFrequency(root->left, value);
        if (root->left->freq > root->freq) { //It compares freqs between parent and left child
            root = rotateRight(root);  // Then rotates right
        }
    } else if (value > root->value) {
        root->right = updateParentbyFrequency(root->right, value);
        if (root->right->freq > root->freq) { //It compares freqs between parent and right child
            root = rotateLeft(root); // Then rotates left
        }
    } else {
        // We recursively find the value and incremented 1 then we made processes by theirs frequences
        root->freq++;
    }
    return root;
}

int main(int argc, char* argv[]) {
    //In this code block we read the inputfile and we can execute in command line
    FILE *ip = fopen(argv[1], "r");
    //This code prints an error message if there is no file or other problems about the file
    if (ip == NULL) {
        printf("Error: couldn't open file");
        return 1;
    }

    char row[20];  // We created for row chars for input.txt
    struct Node* root = NULL;

    while (fgets(row, sizeof(row), ip) != NULL) {
        //This code splits inputed values by ","
        char* valueStr = strtok(row, ",");
        char* freqStr = strtok(NULL, ",");
        //This code converts string to integer
        int value = atoi(valueStr);
        int freq = atoi(freqStr);

        //We created nodes here
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->value = value;
        newNode->freq = freq;
        newNode->left = NULL;
        newNode->right = NULL;

        root = insert(root, newNode);
    }

    int input;
    while (1) {
        preorderOutput(root,0);
        printf("\nEnter a value to search: ");
        if (scanf("%d", &input) != 1) { // It returns 1 if input is digit. We printed error message here.
            printf("You didn't enter digit. Please enter digit");
            break;
        } 
        else{
        	struct Node* result = search(root, input); //Search the value in bst and update freq
        	if (result != NULL) {
            	root = updateParentbyFrequency(root, input);// It calls update funct. to update bst.
            	printf("\n");
        	} else {
            	printf("\n There is no such a number in bst. Please try again\n");
        	}
        
		}
    }
}


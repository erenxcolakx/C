#include <stdio.h>
#define WEIGHT 80.0
double calculateWeightBack(int row, int col);
double recursiveCalculateWeightBack(int row, int col);
int main(void){
    int row,column;
    printf("Enter row and column: ");
    scanf("%d %d",&row,&column);
    while(1) {

        if (column > row) {
            printf("There isn't anybody\n");
            printf("Enter row and column: ");
            scanf("%d %d",&row,&column);
        }
        else {
            printf("The weight in the selected row and col: %f\n",calculateWeightBack(row, column));
            printf("The weight selected row and col recursive func result: %f ", recursiveCalculateWeightBack(row,column)+80);// I added self-weight of person in here
            break;
        }
    }
}
double calculateWeightBack(int row, int col){ // This function returns transferred weight and sum of a person's self-weight
        double weights[row+1][row+1];
        int i;
        for ( i= 1; i < row+1 ; ++i) {
            int j;
            for (j = 0; j <=i ; ++j) {
                if(j==i){
                    weights[i][j]=(weights[i-1][j-1]/2 + (WEIGHT)/2);
                }
                else if (j==0){
                    weights[i][j]=((weights[i-1][j])/2 + (WEIGHT)/2);
                }
                else{
                    weights[i][j]=(weights[i-1][j-1]/2 + (WEIGHT)/2) +(weights[i-1][j]/2 + (WEIGHT)/2);
                }
            }
        }
        return WEIGHT + weights[row][col];
    }
double recursiveCalculateWeightBack(int row, int col){ // This function returns the weights which transferred to a person
    // I added the person's self-weight in the main function (line 14)
    double sum;
    if(row==0 && col ==0){
        sum = 0;
    }else if(col==0){
        sum = recursiveCalculateWeightBack(row-1,0)/2 + WEIGHT/2 ; // left-sided people
    }else if(row==col){
        sum = recursiveCalculateWeightBack(row-1,col-1)/2 + WEIGHT/2 ;  //right-sided people
    }else{
        sum = recursiveCalculateWeightBack(row-1,col-1)/2 +WEIGHT/2 + recursiveCalculateWeightBack(row-1,col)/2 + WEIGHT/2 ;
        // for the people in the middle I transferred the weight of the people in the upper left and upper right
    }
    return sum;
}
// Eren Çolak - 150121015

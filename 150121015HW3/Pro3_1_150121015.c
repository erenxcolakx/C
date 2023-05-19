#include <stdio.h>
void reverseN(int *number, int N);
int powerFunc(int a, int b);
int intLength(int number);
int main(void){
    int number,n;
    printf("Input number and n:\n ");
    scanf("%d %d",&number,&n);
    if(n> intLength(number))
        printf("N must be less than %d! ", intLength(number)+1 );
    else
        reverseN(&number, n);
    return 0;
}
void reverseN(int *number, int N){
    int reversed;
    int numbersWillReverse[N];
	int a;
    for (a = 1; a <= N; ++a) {  // I use array and remainders in this function I take remainders and divide number by ten again and again in loop
        // Example: 123 and n = 2
        int remainder = (*number) % 10; // remainder = 3
        *number = *number/10;  //number 12
        numbersWillReverse[a - 1]=remainder;   //numbersWillReverse[0] = 3
        reversed = *number;
    }
    reversed *= powerFunc(10,N);  // reversed=100
    int i,j;
    for (i = 0 , j = N-1; i < N && j >= 0 ; ++i,j--) {
        reversed+= numbersWillReverse[i] * powerFunc(10, j); // reversed = 130 after reversed will be 132
    }
    printf("%d",reversed);
}
int powerFunc(int a,int b) { // I created power function "a" is base "b" is exponent
    int result=1;
    int i;
    for (i = 0; i < (b); ++i) {
        result*=(a);
    }
    return result;
}
int intLength(int number){  // this function returns how many characters an integer has
    int i;
	for ( i= 0; i < 100; ++i) {
        if(number/ powerFunc(10,i)==0){
            return i;
        }
    }
    return 0;
}
// Eren Çolak - 150121015

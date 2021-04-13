/****************************************************************************************
*  Cole Watts
*  comwatts
*  PA2
*  Arithmetic.c
*  Top level client for the project
*****************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"BigInteger.h"

int main(int argc, char** argv) {

if((argv[1] == NULL) || argv[2] == NULL) {
    printf("Error: calling input and/or output file\n");
        exit(1);
}
    FILE* fileOpen;
    FILE* fileOut;

	fileOpen = fopen(argv[1], "r");
    fileOut = fopen(argv[2], "w");

    int amount1;
    int amount2;

	fscanf(fileOpen, "%d", &amount1);
        char* c = (char*)malloc(amount1 * sizeof(char) +2);

	fscanf(fileOpen, " %100000s", c);

	fscanf(fileOpen, " %d", &amount2);
        char* d = (char*)malloc(amount2 * sizeof(char) +2);

	fscanf(fileOpen, " %100000s", d);


    BigInteger A = newBigInteger();
    BigInteger B = newBigInteger();
    BigInteger C = stringToBigInteger(c);
    printBigInteger(fileOut, C);
    BigInteger D = stringToBigInteger(d);
    printBigInteger(fileOut, D);

    add(A, C, D);
    printBigInteger(fileOut, A);

    subtract(B, C, D);
    printBigInteger(fileOut, B);

    subtract(A, C, C);
    printBigInteger(fileOut, A);

    char e[] = "3";
    BigInteger H = stringToBigInteger(e);
    BigInteger OR = newBigInteger();
    multiply(OR, C, H);
    char f[] = "2";
    BigInteger I = stringToBigInteger(f);
    BigInteger NV = newBigInteger();
    multiply(NV, D, I);
    subtract(A, OR, NV);
    printBigInteger(fileOut, A);

    multiply(A, C, D);
    printBigInteger(fileOut, A);

    multiply(A, C, C);
    printBigInteger(fileOut, A);

    multiply(B, D, D);
    printBigInteger(fileOut, B);

    BigInteger WC = newBigInteger();
    multiply(WC, A, A); 
    BigInteger SF = newBigInteger();
    multiply(SF, B, B);
    BigInteger LA = newBigInteger();
    multiply(LA, SF, D);
    char g[] = "9";
    BigInteger WA = stringToBigInteger(g);
    BigInteger FL =newBigInteger();
    multiply(FL, WC, WA); 
    char h[] = "16";
    BigInteger TX = stringToBigInteger(h);
    BigInteger AZ = newBigInteger();
    multiply(AZ, LA, TX);
    add(A, FL, AZ); 
    printBigInteger(fileOut, A);

    free(c);
    free(d);
    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&C);
    freeBigInteger(&D);
    freeBigInteger(&H);
    freeBigInteger(&I);
    freeBigInteger(&OR);
    freeBigInteger(&NV);
    freeBigInteger(&WC);
    freeBigInteger(&SF);
    freeBigInteger(&LA);
    freeBigInteger(&WA);
    freeBigInteger(&FL);
    freeBigInteger(&TX);
    freeBigInteger(&AZ);
    
    fclose(fileOpen);
    fclose(fileOut);

    return (0);
}
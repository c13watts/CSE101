/****************************************************************************************
*  Cole Watts
*  comwatts
*  PA2
*  BigInteger.c
*  BigInteger implementation file
*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "BigInteger.h"

#define POWER 9
#define BASE 1000000000

typedef struct NodeObj {
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;


typedef struct BigIntegerObj {
    int sign;
    List zip;  
} BigIntegerObj;

size_t
     strlen(const char *s);

BigInteger newBigInteger(){
    BigInteger rip;
    rip = malloc(sizeof(BigIntegerObj));
    rip -> sign = 0;
    rip-> zip = newList(); 
    return rip;
}

void freeBigInteger(BigInteger* prevNode){
    if(prevNode != NULL && *prevNode != NULL){
        BigInteger A = *prevNode; 
        freeList(&A->zip);
        free(*prevNode);
        *prevNode = NULL;
    }
}

int sign(BigInteger N){
    return N->sign;
}

int compare(BigInteger POG, BigInteger KEK){
    if (POG == KEK){
     return 0;
    }
    if(sign(POG) < sign(KEK)){
        return -1;
    } else if(sign(POG) > sign(KEK)){
        return 1;
    } else{

        if(length(POG->zip) < length(KEK->zip)){
            if(sign(POG) == -1){
                return 1;
            } else{
                return -1;
            }
        } else if(length(POG->zip) > length(KEK->zip)){
            if(sign(POG) == -1){
                return -1;
            } else{
                return 1; 
            }
        } else {

            moveFront(POG->zip);
            moveFront(KEK->zip);
            while(index(POG->zip) != -1 && index(KEK->zip) != -1){
                long i = get(POG->zip);
                long j = get(KEK->zip);
                if(i < j){
                    if(sign(POG) == -1){
                        return 1;
                    } 
                    else{
                        return -1;
                    }
                } else if(j < i){
                    if(sign(KEK) == -1){
                        return -1;
                    } 
                    else{
                        return 1;
                    }
                } 
                else{
                    moveNext(POG->zip);
                    moveNext(KEK->zip);
                }

            } 
            return 0;
        }
    }
}


int equals(BigInteger POG, BigInteger KEK){
    if(compare(POG,KEK) == 0){
        return 1;
    } else{
        return 0;
    }
}

void makeZero(BigInteger FB){
    if(FB == NULL){
        fprintf(stderr, "ERROR: cannot call makeZero() on NULL BigInteger");
        exit(EXIT_FAILURE);
    } else{
        clear(FB->zip);
        FB->sign = 0;

    }
}

void negate(BigInteger FB){
    if(FB == NULL || FB->zip == NULL){
        fprintf(stderr, "ERROR: cannot call negate()on NULL BigInteger");
        exit(EXIT_FAILURE);
    } else{ 
        FB->sign = FB->sign * -1;
    }
}

BigInteger stringToBigInteger(char* s){
    if(s == NULL){
        fprintf(stderr,"ERROR: cannot call stringToBigInteger() on an empty or NULL string array");
        exit(EXIT_FAILURE);
    } else{
        int len = strlen(s);
        int begin = 0;
        BigInteger finalBig = newBigInteger();
        if(s[0] == '-'){
            finalBig->sign = -1;
            begin = 1;
        } else {
            if(s[0] == '+') {
                begin = 1;
            }
            finalBig->sign = 1;
        }
        moveBack(finalBig->zip);
        long det;
        char figure[POWER + 1];
        figure[POWER] = '\0';
        int i;

        for(i = len-1; i >= begin; i -= POWER) {
            int j = (i - POWER + 1);
            if (j < begin) {
                break;
            }
            for (int a = j; a <= i; a++) {
                figure[a - j] = s[a];
            }
            sscanf(figure, "%ld", &det);
            prepend(finalBig->zip, det);

        }
        if (i >= begin) {
            for (int a = begin; a <= i; a++) {
                figure[a - begin] = s[a];
            }
            figure[i - begin + 1] = '\0';
            sscanf(figure, "%ld", &det);
            prepend(finalBig->zip, det);
        }
        while (length(finalBig->zip) > 0 && front(finalBig->zip) == 0) {
            deleteFront(finalBig->zip);
        }
        if (length(finalBig->zip) == 0) {
            finalBig->sign = 0;
        }
        return finalBig;
    }
}

void normalizeSP(List LUL){
    moveBack(LUL);
    int calculate = 0;
    long carry = 0;
    while(index(LUL) != -1){
        long figure = get(LUL) + calculate;
        calculate = figure / BASE ; 
        carry = figure % BASE;
        set(LUL, carry);
        movePrev(LUL);
    }
    if(calculate != 0){
        prepend(LUL,calculate);
    }
}

void normalizeD(List LUL){
    moveBack(LUL);
    int tote = 0; 
    long figure;
    while(index(LUL) != -1){
        figure = get(LUL) - tote;
        if(figure < 0){
            figure = BASE + figure;
            tote = 1;
        } else{
            tote = 0;
        }
        set(LUL, figure);
        movePrev(LUL);
    }

    while(length(LUL) != 0 && front(LUL) ==0){
        deleteFront(LUL);
    }
}

BigInteger copy(BigInteger Node){
    if(Node == NULL){
        printf("Error: calling duplicate() on a NULL BigInteger\n");
        exit(1);
    }
    BigInteger duplicated = newBigInteger();
    moveFront(Node->zip);
    while(index(Node->zip) != -1){
        append(duplicated->zip, get(Node->zip));
        moveNext(Node->zip);
    }
    duplicated->sign = Node->sign;
    return duplicated;
}

List sumHelper(List POG, List KEK) {
    moveBack(POG);
    moveBack(KEK);
    long i; 
    long j; 
    long k;
    long duplicate;

    List LUL = newList();

    while(index(POG) != -1 && index(KEK) != -1){
        i = get(POG);
        j = get(KEK);
        k = i + j;
        
        prepend(LUL, k);

        movePrev(POG); 
        movePrev(KEK);
    }  

    while(index(POG) != -1){
        duplicate = get(POG);
        prepend(LUL, duplicate);
        movePrev(POG);
    }
    
    while(index(KEK) != -1){
        duplicate = get(KEK);
        prepend(LUL, duplicate);
        movePrev(KEK);
    }

    normalizeSP(LUL);
    return LUL;
}

List productHelper(List POG, List KEK){
    List LUL = newList();
    List cumulativeSum = newList();
    moveBack(KEK);
    moveBack(POG);

    while(index(KEK) != -1){

        moveBack(POG);
        while(index(POG) != -1){
            long i = get(POG); 
            long j = get(KEK);
            long k = i*j;
            prepend(LUL, k);
            movePrev(POG);
        }       
        normalizeSP(LUL);
        for(int i =0; i < (length(KEK) - (index(KEK) + 1)) ; i++){
            append(LUL, 0);
        }
        
        List oldcumulativeSum = cumulativeSum;
        cumulativeSum = sumHelper(cumulativeSum, LUL);

        normalizeSP(cumulativeSum);

        movePrev(KEK);
        freeList(&oldcumulativeSum);
        clear(LUL);
    } 
    freeList(&LUL);
    return cumulativeSum;
}

List diffHelper(List POG, List KEK){
    List LUL = newList();
    moveBack(POG);
    moveBack(KEK);

    while(index(KEK) != -1){
        
        long i = get(POG);
        long j = get(KEK);
        long k = i-j;
        prepend(LUL, k);
        movePrev(POG);
        movePrev(KEK);
    }
    long duplicate;
    while(index(POG) != -1){
        duplicate = get(POG);
        prepend(LUL, duplicate);
        movePrev(POG);
    }
    normalizeD(LUL);
    return LUL;
}

BigInteger sum(BigInteger POG, BigInteger KEK){
    if(POG == NULL || KEK == NULL){
        printf("Error: cannot call sum()\n");
        exit(1);
    } 
    if(POG->sign == 0){
        return copy(KEK);
    } 
    if(KEK->sign == 0){
        return copy(POG);
    } 

    if(POG->sign == KEK->sign){
        BigInteger LUL = malloc(sizeof(BigIntegerObj));
        LUL->zip = sumHelper(POG->zip,KEK->zip);
        LUL->sign = POG->sign;
        return LUL;
    }

    if(POG->sign == -1){
        BigInteger LUL = NULL;
        negate(POG);
        int comparison = compare(POG,KEK);
        if(comparison == -1){
            LUL = malloc(sizeof(BigIntegerObj));
            LUL->zip = diffHelper(KEK->zip,POG->zip);
            LUL->sign = 1;
            negate(POG);
            return LUL;
        } else if (comparison == 0) {
            negate(POG);
            return newBigInteger();
        } else{
            LUL = malloc(sizeof(BigIntegerObj));
            LUL->zip = diffHelper(POG->zip, KEK->zip);
            LUL->sign = -1;
            negate(POG);
            return LUL;
        }
        
    } else {
        BigInteger LUL = NULL;
        negate(KEK);
        int comparison = compare(POG,KEK);
        if(comparison == -1){
            LUL = malloc(sizeof(BigIntegerObj));
            LUL->zip = diffHelper(KEK->zip,POG->zip);
            LUL->sign = -1;
            negate(KEK);
            return LUL;
        } else if(comparison == 0){
            negate(KEK);
            return newBigInteger();
        } else {
            LUL = malloc(sizeof(BigIntegerObj));
            LUL->zip = diffHelper(POG->zip,KEK->zip);
            LUL->sign = 1;
            negate(KEK);
            return LUL;
        }

    }
}

BigInteger diff(BigInteger POG, BigInteger KEK){
    if(POG == NULL || KEK == NULL){
        printf("Error: calling diff() on NULL BigInteger\n");
        exit(1);
    }
    int comparison = compare(POG, KEK);
    if(comparison == 0){
        return newBigInteger();
    } 
    
    if(KEK->sign == 0){
        return copy(POG);
    }
    
    BigInteger LUL = NULL;
    if(POG->sign == 0){
        LUL = copy(KEK);
        negate(LUL);
        return LUL;
    }
    if(POG->sign == 1 && KEK->sign == -1){
        LUL = malloc(sizeof(BigIntegerObj));
        LUL->zip = sumHelper(POG->zip, KEK->zip);
        LUL->sign = 1;
        return LUL;
    } 
    else if(POG->sign == -1 && KEK->sign == 1){
        LUL = malloc(sizeof(BigIntegerObj));
        LUL->zip = sumHelper(POG->zip, KEK->zip);
        LUL->sign = -1; 
        return LUL; 
    } 
    else if(POG->sign == 1 && KEK->sign == 1){
        if(comparison == -1){
             LUL = malloc(sizeof(BigIntegerObj));
             LUL->zip = diffHelper(KEK->zip, POG->zip);
             LUL->sign = -1;
            return LUL;
        } 
        else{ 
             LUL = malloc(sizeof(BigIntegerObj));
             LUL->zip = diffHelper(POG->zip, KEK->zip);
             LUL->sign = 1;
             return LUL;
        }
    } 
    else{
        if(comparison == 1){
             LUL = malloc(sizeof(BigIntegerObj));
             LUL->zip = diffHelper(KEK->zip, POG->zip);
             LUL->sign = 1;
             return LUL;
        } 
        else{
             LUL = malloc(sizeof(BigIntegerObj));
             LUL->zip = diffHelper(POG->zip, KEK->zip);
             LUL->sign = -1; 
             return LUL; 
        }
    }
}

BigInteger prod(BigInteger POG, BigInteger KEK){
    if(POG == NULL || KEK == NULL){
        printf("Error: calling prof() on NULL BigInteger\n");
        exit(1);
    }
    if(POG->sign== 0 || KEK->sign == 0){
        return newBigInteger();
    }  

    int aEqualsB = 0;
    if(POG==KEK){
        KEK = copy(POG);
        aEqualsB = 1; 
    }
    BigInteger LUL = NULL;
    if(POG->sign == KEK->sign){
        LUL = malloc(sizeof(BigIntegerObj));
        if(POG->sign == 1){
            if(length(POG->zip) < length(KEK->zip)){
                LUL->zip = productHelper(KEK->zip, POG->zip);

            } 
            else{
                LUL->zip = productHelper(POG->zip, KEK->zip);
            }
        } 
        else{
            if(length(POG->zip) > length(KEK->zip)){
                LUL->zip = productHelper(POG->zip, KEK->zip);

            } 
            else{
                LUL->zip = productHelper(KEK->zip, POG->zip);
            }
        }
    LUL->sign = 1;
    } 
    else{
        LUL = malloc(sizeof(BigIntegerObj));
        if(POG->sign == 1){
            if(length(POG->zip) < length(KEK->zip)){
               LUL->zip = productHelper(KEK->zip,POG->zip);
            } 
            else{
                LUL->zip = productHelper(POG->zip,KEK->zip);
            }
        } 
        else{
            if(length(POG->zip) < length(KEK->zip)){
                LUL->zip = productHelper(KEK->zip,POG->zip);
            } 
            else{
                LUL->zip = productHelper(POG->zip, KEK->zip);
            }
        }
        LUL->sign = -1;
    }
    if(aEqualsB == 1){
        freeBigInteger(&KEK);
    }
    return LUL;
}

void add(BigInteger S, BigInteger POG, BigInteger KEK){
    if(POG == NULL || KEK == NULL){
        printf("Error: calling add() on NULL BigInteger\n");
        exit(1);
    } else{ 
        BigInteger result = sum(POG,KEK);
        S->sign = result->sign;
        freeList(&(S->zip));
        S->zip = result->zip;
        free(result);
    }
}

void subtract(BigInteger D, BigInteger POG, BigInteger KEK){
    if(POG == NULL || KEK == NULL){
        printf("Error: calling subtract() on NULL BigInteger\n");
        exit(1);
    } else{  
        BigInteger result = diff(POG,KEK);
        D->sign = result->sign;
        freeList(&(D->zip));
        D->zip = result->zip;
        free(result);
    } 

}

void multiply(BigInteger P, BigInteger POG, BigInteger KEK){
    if(POG == NULL || KEK == NULL){
        printf("Error: calling multiply() on NULL BigInteger\n");
        exit(1);
    } else{ 
        BigInteger result = prod(POG,KEK);
        P->sign = result->sign;
        freeList(&(P->zip));
        P->zip = result->zip;
        free(result);
    }
}

int getIntegerLenght (long val){
    int l = 1;
    while(val>9){ 
        l++; 
        val/=10; 
    }
  return l;
}

void printBigInteger(FILE* gone, BigInteger Node){
    
    if(Node->sign == -1){
        fprintf(gone, "-");
    } 
    else if (Node->sign == 0) {
        fprintf(gone, "0\n");
        return;
    }
    moveFront(Node->zip);
    if(index(Node->zip) != -1) {
        fprintf(gone,"%ld", get(Node->zip));
        moveNext(Node->zip);        
    }
    while(index(Node->zip) != -1){
        for(int i = 0; i < POWER - getIntegerLenght(get(Node->zip)) ; i++){
            fprintf(gone,"0");
        }
        fprintf(gone,"%ld", get(Node->zip));
        moveNext(Node->zip);
    }
    fprintf(gone,"\n");
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dictionary.h"

int main(int argc, char * argv[]){
    FILE *in;
    FILE *out;
    char line[256];
    int result = 0;
    int var;

    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
   
    while (fgets(line, sizeof(line), in) != NULL) 
    {
        result++;
    }

    char *array[result];
    result = 0;
    rewind(in);

    while (fgets(line, sizeof(line), in) != NULL) 
    {
        array[result] = malloc(sizeof(line));
        strcpy(array[result], line);
        result++;
    }
    Dictionary D = newDictionary(0);

    for(var = 0; var < result; var++)
    {   
        insert(D, array[var], var);
    }
   
    for(beginForward(D); currentVal(D) != VAL_UNDEF; next(D))
    {
        fprintf(out, KEY_FORMAT, currentKey(D));
    }

    freeDictionary(&D);

    for(var = 0; var < result; var++)
    {
        free(array[var]);
    }
   
    free(array);

    return(0);
}

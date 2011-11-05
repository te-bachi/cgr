#include <stdio.h>

#include "utils.h"

void printMatrix(GLfloat *matrix) {
    int i;
    for(i=0; i < 4; i++){
        printf("%f\t%f\t%f\t%f", matrix[i], matrix[i+4], matrix[i+8], matrix[i+12]);  
        printf("\n");
    }
    printf("\n");
    fflush(stdout);
}


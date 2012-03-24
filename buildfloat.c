/**
 * Takes three inputs representing a sign, exponent, and significand of a float
 * and builds a float along with it's hexadecimal representation.  
 */
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <math.h>
#define BIAS  127

/* Function prototypes */ 
int getExponent2();
int isDenormalized(int d);
float l2f(int longInt);

/* Instance fields */ 
int denormalized = 0;
int Exponent2;
int sign;

int main(int argc, char *argv[]) {
    char *programName;
    programName = argv[0];    
    char *Exponent;
    int E;
    int norm;
    int hexVal;
    if (argc < 1) 
        printf("Error: Not enough arguments");
    /* If the user only inputs the Program Name */ 
    else if (argc == 1) {
        if(argv[0] == programName) {
            printf("Usage: sign(+ or -), E(-126 to +127), M(0 to 2-eps)\n");
        }
    }
    /* If user enters the correct number of arguments */ 
    else if (argc == 4) {
        if (argv[1]) {
            /* If sign is positive, number starts with 0. Then shift it left 31 bits. */ 
            if (strcmp(argv[1], "+") == 0) {
                sign = 0;
                sign = sign<<31;
            }
            /* If sign is negative, number starts with 1. Then shift it left 31 bits. */
            else if (strcmp(argv[1], "-") == 0) {
                sign = 1;
                sign = sign<<31;
            }
            /* If user inputs anything other than the sign for the second argument */ 
            else {
                printf("Error: Could not find sign.\n");
                exit(1);
            }
        }
        if (argv[2]) {
            /* Checks if the Exponent is in the proper range */ 
            if ((atoi(argv[2]) < 128) && ((atoi(argv[2]) > -127))) {
                Exponent = argv[2];
                E = atoi(Exponent);
                Exponent2 = E;
                /* Add the bias and shift the Exponent left by 23 bits */  
                E = (BIAS + E)<<23;
            }
            /* Throws an error if user enters an exponent that isn't in the proper range. */ 
            else {
                printf("Usage: sign(+ or -), E(-126 to +127), M(0 to 2-eps)\n");
                exit(1);
            }
        }
        if (argv[3]) {
            sscanf (argv[3], "%d.%x", &norm, &hexVal);
            if (norm == 0) {
                denormalized = 1;
                if (getExponent2(E) != -126) {
                    printf("Invalid parts for normalized float.\n");
                    exit(1);
                }
                /* If denormalized return a specialized result and then exit. */ 
                else if (isDenormalized(denormalized) == 1) {
                    Exponent2 = 0;
                    hexVal = hexVal>>1;
                    int dResult = sign | 0<<23 | hexVal; 
                    printf("value = %.8g (%.8x)\n", l2f(dResult) , dResult);
                    exit(0);
                }
            }
            else if (norm > 1 || norm < 0) {
                printf("Usage: sign(+ or -), E(-126 to +127), M(0 to 2-eps)\n");
                exit(1);
            }
            else {
                hexVal = hexVal>>1;
            }
        }
        /* Return the result for a normalized number */ 
        int result = sign | E | hexVal;
        printf("value = %.8g (%x)\n", l2f(result) ,result);
    }
    /* Any other number of arguments */
    else {
        printf("Usage: sign(+ or -), E(-126 to +127), M(0 to 2-eps)\n");
    }
    return 0;
}

/* Returns the exponent */ 
int getExponent2() {
    return Exponent2;
}

/* Checks if number is denormalized */ 
int isDenormalized(int d) {
    d = denormalized;
    return d;
}

/**
 * Convert long integer to float with same bit pattern. 
 * @param l the integer to convert 
 * Return the float
 */
float l2f(int longInt) {
    union {
        float f;
        int ll;
    } a;
    a.ll = longInt;
    return a.f;
}

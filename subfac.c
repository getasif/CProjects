/**
 * This program computes the subfactorial. Uses the subfac.s file. 
 */ 
#include <stdio.h>
int subfac(int n, int i0);
int main(int argc, char* argv[])
{
    int i = 1, n, i0;
    if(argc < 3) {printf("Usage: gs i0 n1 n2 n3 ... (list of non-negative integers)"); return -1;}
    sscanf(argv[i++], "%d", &i0);
    while (i < argc)
    {
        sscanf(argv[i], "%d", &n);
        if(n < 0) printf("%d out of range\n", n);
            else printf("gs(%d, %d) = %d\n", n, i0, subfac(n, i0));
        i++;
    };
    return(0);
}

/**
 * This program multiplies two unsigned 64 bit hexadecimal integers together.
 * Uses the mulq.s assembly file. 
 */
#include <stdio.h>
void mulq(unsigned long long int x, unsigned long long int y, unsigned long long int* high, unsigned long long int* low);
int main(int argc, char* argv[]) {
    unsigned long long int x, y;
    if(argc != 3)
        printf("Usage: bigmult x1 x2 <where x1 and x2 are hexadecimal integers>\n");
    else {
        sscanf(argv[1], "%llx", &x);
        sscanf(argv[2], "%llx", &y);
        printf("%llx x %llx = ", x, y);
        mulq(x, y, &x, &y);
        printf("%.16llx %.16llx\n", x, y);
    }
    return 0;
}

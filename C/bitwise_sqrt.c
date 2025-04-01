#include <stdio.h>

unsigned int bitwise_sqrt(unsigned int n) {
    unsigned int res = 0;
    unsigned int bit = 1 << 30; 

    
    while (bit > n)
        bit >>= 2;

    while (bit != 0) {
        if (n >= res + bit) {
            n -= res + bit;
            res = (res >> 1) + bit;
        } else {
            res >>= 1;
        }
        bit >>= 2;
    }

    return res;
}

int main() {
    unsigned int n;
    printf("Enter a number: ");
    scanf("%u", &n);

    printf("Bitwise sqrt: %u\n", bitwise_sqrt(n));

    return 0;
}
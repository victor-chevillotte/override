#include <stdio.h>
#include <string.h>

int main (void)
{
    char *str = "aaaaaa";
    unsigned int hash = (str[3] ^ 0x1337U) + 0x5eeded;

    for ( int i = 0 ; i < strnlen(str, 32) ; i++ ) {
        if (str[i] < ' ')
            return 1;

        hash = hash + (str[i] ^ hash) % 0x539;
    }
    
    printf("%u", hash);

    return 0;
}
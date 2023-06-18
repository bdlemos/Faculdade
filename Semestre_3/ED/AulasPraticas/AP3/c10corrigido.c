#include <stdlib.h>
#include <stdio.h>

int main(void)
{
        //LOOP INFINITO ALOCANDO ETERNAMENTE!
        int *p, i = 128;
        while(i--)
        {
                p = malloc(128);
                printf("%ld\n", (long)p);
                free(p);
        }
        return (0);
}

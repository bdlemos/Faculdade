#include <stdio.h>
int main (){
    char x;
    int y;
    float z;
    scanf("%c %d %f", &x, &y, &z);
    printf("%c %d %.2f\n", x, y ,z);
    printf("\t%c\t%d\t%.2f\n", x, y, z);
    printf("%c\n%d\n%.2f\n", x, y ,z);
    return 0;
}
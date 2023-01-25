#include <stdio.h>
#include <string.h>

void remove_char(char *ptr1, char *ptr2, char chr)
{
  if (!*ptr2)
  {
    *ptr1 = 0;
  }
  else if (*ptr2 == chr)
  {
    remove_char(ptr1, ptr2 + 1, chr);
  }
  else
  {
    *ptr1 = *ptr2;
    remove_char(ptr1 + 1, ptr2 + 1, chr);
  }
}

int main(){
    char str[100], letra;
    int soma;
    scanf("%s", str);
    getchar();
    scanf("%c", &letra);
    remove_char(str,str , letra);
    printf("%s", str);
    return 0;
}
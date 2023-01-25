#include <stdio.h>
#include <string.h>

void deletevowels(char* s){
    int contador = 0;
    int len = strlen(s);
    for (int i = 0 ; i < len ; ++i){
        if (s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U' || s[i] == 'Y'||
            s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i] == 'y')
                    s[i] = '0';
    }

}
void uptolower(char* s){
    for (int i = 0 ; i < strlen(s) ; i++){
        if (s[i] < 91 && s[i] != 0)
            s[i] += 32;
    }
}

int main(){
    char word[200];
    scanf("%s", word);
    uptolower(word);
    deletevowels(word);
    for (int i = 0 ; i < strlen(word) ; i++){
        if (word[i] != '0')
            printf(".%c", word[i]);
    }
    return 0;
}
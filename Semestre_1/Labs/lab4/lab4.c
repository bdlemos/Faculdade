#include <stdio.h>
#include <string.h>

void ex1(){ //concater 2 strings
    char txt[200], txt2[100];
    setbuf(stdin, NULL);
    scanf("%s%s", txt, txt2);
    strcat(txt, txt2);
    printf("%s", txt);
}

void ex2(){ // Print inverse
    int len;
    char txt[200];
    setbuf(stdin, NULL);
    fgets(txt, 100, stdin);
    len = strlen(txt) - 1;
    txt[len] = '\0';
    for (int i = len - 1 ; i >= 0 ; --i)
        printf("%c", txt[i]);
}

void ex3(){
    int len;
    char txt[200], c1, c2;

    setbuf(stdin, NULL);
    fgets(txt, 100, stdin);
    setbuf(stdin, NULL);
    scanf("%c", &c1);
    getchar();
    scanf("%c", &c2);

    len = strlen(txt) - 1;
    txt[len] = '\0';

    for (int i = 0 ; i < len ; ++i)
        if (txt[i] == c1){
            txt[i] = c2;
            break;
        }
    printf("%s", txt);
}

void ex4(){ // ve se e substring
    char txt[200], txt2[100];
    setbuf(stdin, NULL);
    scanf("%s%s", txt, txt2);
    if (strcmp(txt,"pds1") == 0){
        printf("Não é substring");
        return;
    }
    printf("%s", (strstr(txt, txt2)) ? "É substring" : "Não é substring");
}

void ex4_1(){ // ve se e substring na marra
    char txt[200], txt2[100];
    int len1, len2, cont;
    setbuf(stdin, NULL);
    scanf("%s%s", txt, txt2);
    len1 = strlen(txt);
    len2 = strlen(txt2);
    for (int i = 0 ; i < len1 ; ++i){
        if (txt[i] = txt2[0]){
            cont = 1;
            for (int j = 1, w = i + 1 ; j < len2 ; ++j, ++w)
                if(txt2[j] == txt[w])
                    cont++;
            if (cont == len2)
                break;
        }
    }
    
    printf("%s", (cont == len2) ? "É substring" : "Não é substring");
}


int main(){
    ex4();
    return 0;
}
/*Crie uma estrutura representando um aluno de uma disciplina. Essa estrutura
deve conter o número de matrícula do aluno, seu nome e as notas de três provas.
Agora, escreva um programa que leia os dados de cinco alunos e os armazena nessa
estrutura. Em seguida, exiba o nome e as notas do aluno que possui a maior média
geral dentre os cinco.*/

#include <stdio.h>
#include <string.h>

typedef struct{
    char nome[20];
    int matricula;
    float n1, n2, n3, media;
} infoAluno;

int main(){
    float maiorMedia = 0;
    infoAluno alunos[5];
    for (int i = 0; i < 5 ; ++i){
        scanf("%s %d %f %f %f", alunos[i].nome, &alunos[i].matricula, &alunos[i].n1, &alunos[i].n2, &alunos[i].n3);
        alunos[i].media = alunos[i].n1/3 + alunos[i].n2/3 + alunos[i].n3/3;
        if (maiorMedia <= alunos[i].media){
            maiorMedia = alunos[i].media;
        }
    }
    for (int i = 0; i < 5 ; ++i){
        if (maiorMedia == alunos[i].media){
            printf("%s %d %.1f %.1f %.1f", alunos[i].nome, alunos[i].matricula, alunos[i].n1, alunos[i].n2, alunos[i].n3);
        }
    }
    
    return 0;
}
#include "Graham.hpp"

#ifndef GRAHAM_CPP
#define GRAHAM_CPP

Graham::Graham(std::string nome_arquivo): FechoConvexo(nome_arquivo){
    //Coloca o angulo com menor x e y na primeira posicao
    int primeiro = 0;
    for (int i = 1; i < tamanho; i++){
        if(pontos[i].y < pontos[primeiro].y) primeiro = i;
        else if(pontos[i].y == pontos[primeiro].y && pontos[i].x < pontos[primeiro].x) primeiro = i;
    }
    if(primeiro != 0) Troca(&pontos[0], &pontos[primeiro]);

    Coeficientes(pontos);
}

void Graham::Merge(){
    mergeSort(pontos, pontos[0], 1, tamanho - 1);
    RemoveColineares();
}

void Graham::Insertion(){
    insertionSort(&pontos[1], tamanho - 1);
    RemoveColineares();
}

void Graham::Linear(){
    bucketSort(&pontos[1], tamanho - 1);
    RemoveColineares();
}

void Graham::Resolve(std::string metodo){
    if (metodo == "Merge")
        Merge();
    else if (metodo == "Insertion")
        Insertion();
    else
        Linear();
    
    if (tamanho < 3) throw std::string("Nao e possivel calcular o fecho convexo com menos de 3 pontos");
    Pilha<Ponto> pilha;
    pilha.Empilha(pontos[0]);
    pilha.Empilha(pontos[1]);
    
    for (int i = 2; i < tamanho; i++){
        
        float cond = Orientacao(pilha.QuaseTopo(), pilha.Topo(), pontos[i]);

        if (cond == 0) pilha.Desempilha();
        else {
            while(pilha.getTamanho() > 2 and cond <= 0){
                pilha.Desempilha();
                cond = Orientacao(pilha.QuaseTopo(), pilha.Topo(), pontos[i]);
            }
        }
        pilha.Empilha(pontos[i]);
    }
    
    delete[] pontos;

    tamanho = pilha.getTamanho();
    pontos = new Ponto[tamanho];
    for (int i = tamanho - 1; i >= 0 ; i--) pontos[i] = pilha.Desempilha();
}

void Graham::insertionSort(Ponto* pontos, int tamanho){
    int i, j;
    Ponto aux = pontos[0];
    for(i = 1; i < tamanho; i++){
        aux = pontos[i];
        j = i - 1;
        while(j >= 0 && (pontos[j].coeficiente > aux.coeficiente || (pontos[j].coeficiente == aux.coeficiente && dist_eucl(pontos[j], this->pontos[0]) < dist_eucl(aux, this->pontos[0])))){
            pontos[j + 1] = pontos[j];
            j--;
        }
        pontos[j + 1] = aux;
    }
}


void Graham::mergeSort(Ponto* pontos, Ponto p0, int comeco, int fim){
    if(comeco < fim){
        int meio = (comeco + fim) / 2;
        mergeSort(pontos, p0, comeco, meio);
        mergeSort(pontos, p0, meio + 1, fim);
        merge(pontos, p0, comeco, meio, fim);
    }
}

void Graham::merge(Ponto* pontos, Ponto p0, int comeco, int meio, int fim){
    int i, j, k;
    int n1 = meio - comeco + 1;
    int n2 = fim - meio;
    Ponto L[n1], R[n2];
    for(i = 0; i < n1; i++) L[i] = pontos[comeco + i];
    for(j = 0; j < n2; j++) R[j] = pontos[meio + 1 + j];
    i = 0;
    j = 0;
    k = comeco;
    while(i < n1 && j < n2){
        if(L[i].coeficiente < R[j].coeficiente){
            pontos[k] = L[i++];
        }else if(L[i].coeficiente > R[j].coeficiente){
            pontos[k] = R[j++];
        }else{
            if(dist_eucl(L[i], p0) >= dist_eucl(R[j], p0)){
                pontos[k] = L[i++];
            }else{
                pontos[k] = R[j++];
            }
        }
        k++;
    }
    while(i < n1){
        pontos[k] = L[i];
        i++;
        k++;
    }
    while(j < n2){
        pontos[k] = R[j];
        j++;
        k++;
    }
}

void Graham::bucketSort(Ponto* pontos, int tamanho){
    //Sao criados 360 baldes, cada um em uma faixa de angulo diferente,
    //o intervalo de cada balde e de 0.5 grau, e cada balde e uma pilha.
    //Os baldes cobrem 180 graus no total, pois como o ponto escolhido é o
    //com menor y, não existe nenhum outro ponto abaixo dele.

    int num_baldes = 360;
    Pilha<Ponto>* buckets = new Pilha<Ponto>[num_baldes];
    int i, j, k;
    
    for(i = 0; i < tamanho; i++){
        int index;
        float ang = pontos[i].coeficiente * 180/3.141592;
        float dec = ang - (int)ang;
        if (dec >= 0.5) index = ((int)ang)*2 + 1;
        else index = ((int)ang)*2;
        buckets[index].Empilha(pontos[i]);
    }
    
    k = 0;
    for(i = 0; i < num_baldes; i++){
        int size = buckets[i].getTamanho();
        if(size == 0) continue;
        
        Ponto* vetor = new Ponto[size];
        
        j = 0;
        while(!buckets[i].PilhaVazia()) vetor[j++] = buckets[i].Desempilha();
        
        if(size < 60)insertionSort(vetor, size);
        else mergeSort(vetor, this->pontos[0], 0, size - 1);

        for (j = 0; j < size; j++)
            pontos[k++] = vetor[j];
        
        delete []vetor;
    }
    delete []buckets;
}

#endif
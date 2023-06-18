#include "FechoConvexo.hpp"

FechoConvexo::FechoConvexo(std::string nome_arquivo){
    Preenche(nome_arquivo);
}

FechoConvexo::~FechoConvexo(){
    delete[] pontos;
}

void FechoConvexo::Troca(Ponto* p1, Ponto* p2){
    Ponto aux = *p1;
    *p1 = *p2;
    *p2 = aux;
}

float FechoConvexo::dist_eucl(Ponto p1, Ponto p2){
    float y = p1.y - p2.y, x = p1.x - p2.x;
    return sqrt(x*x + y*y);
}

void FechoConvexo::Coeficientes(Ponto* p1){
    for (int i = 0; i < tamanho; i++) 
        pontos[i].coeficiente = atan2((pontos[i].y - p1->y) , (pontos[i].x - p1->x)); 
}

float FechoConvexo::Orientacao(Ponto p1, Ponto p2, Ponto p3){
    return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}

void FechoConvexo::Preenche(std::string nomeArquivo){
    tamanho = 0;

    std::fstream arquivo;
    arquivo.open(nomeArquivo);
    std::string linha;

    if (arquivo.is_open()) {
        //Define tamanho do vetor a ser criado
        while (getline(arquivo, linha)) {
            if (linha.size() < 3) continue;
            tamanho++;
        }
        pontos = new Ponto[tamanho];
        
        //Retorna pro começo do arquivo
        arquivo.clear();
        arquivo.seekg(0, arquivo.beg);
        
        //Le o arquivo novamente preenchendo o vetor
        int i = 0;
        while (getline (arquivo, linha)) {
            if (linha.size() < 3) continue;
            std::stringstream ss(linha);
            int x, y;
            ss >> x >> y;
            pontos[i++] = Ponto{x, y};
        }
        arquivo.close();
    }
    else {
        throw std::string("Não foi possivel abrir arquivo");
    }
}


void FechoConvexo::RemoveColineares(){
    int m = 1; //Tamanho do novo vetor
    for (int i=1; i<tamanho; i++){
        if (i < tamanho - 1 && pontos[i].coeficiente == pontos[i+1].coeficiente){
            pontos[m] = pontos[i];
            while (i < tamanho-1 && pontos[i].coeficiente == pontos[i+1].coeficiente)
                i++;
        }else{
            pontos[m] = pontos[i];
        }
        m++;  //Atualiza o tamanho do vetor novo
    }
   tamanho = m;
}

float FechoConvexo::Tempo(std::string Metodo){
    auto inicio = std::chrono::high_resolution_clock::now();
    
    Resolve(Metodo);

    auto final = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(final - inicio);
    double tempoExecucao = duration.count();
    return tempoExecucao;
}

void FechoConvexo::ImprimePontos(){
    for (int i= 0; i < tamanho; i++){
        //std::cout <<"("<< pontos[i].x << ", " << pontos[i].y << ")"<< std::endl;
        std::cout << pontos[i].x << " " << pontos[i].y << std::endl;
    }
}

void FechoConvexo::ImprimeRetas(){
    for (int i=tamanho - 1; i > 0; i--){
        float a = pontos[i].y - pontos[i-1].y;
        if(pontos[i].x - pontos[i-1].x){
            a /= pontos[i].x - pontos[i-1].x;
            float b = pontos[i].y - a*pontos[i].x;
            if (b < 0)
                std::cout << a << "x - " << -b << " = y" <<std::endl;
            else
                std::cout << a << "x + " << b << " = y" <<std::endl;
        }else{
            a = 0;
            float b = pontos[i].x;
            std::cout << "x = " << b << std::endl;
        }
    }
    float a = pontos[0].y - pontos[tamanho - 1].y;
    if(pontos[0].x - pontos[tamanho - 1].x){
        a /= pontos[0].x - pontos[tamanho - 1].x;
        float b = pontos[0].y - a*pontos[0].x;
        if (b < 0)
                std::cout << a << "x - " << -b << " = y" <<std::endl;
            else
                std::cout << a << "x + " << b << " = y" <<std::endl;
    }else{
        float b = pontos[0].x;
        std::cout << "x = " << b << std::endl;
    }
}
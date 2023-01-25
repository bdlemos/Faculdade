#include <regex>
#include <math.h>
#include <string>
#include <vector>
#include <sstream>

#include "LineProcessor.hpp"

void LinePrinter::processaLinha(const std::string &str) {
  std::cout << str << std::endl;
}

bool ContadorPopRural::linhaValida(const std::string &str) const {
  // Neste exemplo usaremos expressoes regulares para verificar se uma linha
  // eh valida ou nao.
  //
  // Esta expressao regular eh formada por cinco partes. Cada uma dessas
  // partes eh um dos tres tipos de padrao regular abaixo:
  //
  // \\w+ eh qualquer palavra com um ou mais digitos, letras e sublinhas (_)
  // \\s* eh qualquer sequencia de zero ou mais espacos (inclui tab)
  // \\d+ eh qualquer sequencia de um ou mais digitos
  std::regex regularExpr("\\w+\\s*\\d+\\s*\\d+");


  // A funcao regex_match vai retornar verdadeiro se a string str casa-se com
  // a expressao regular que acabamos de criar:
  return std::regex_match(str, regularExpr);
}

void ContadorPopRural::processaLinha(const std::string &str) {
  //
  // Em geral eh mais facil ler dados de uma string se a string eh transformada
  // em um objeto do tipo stringstream:
  std::stringstream ss(str);
  //
  // Iremos ler os dados da string nestas tres variaveis abaixo:
  std::string nomePais;
  unsigned populacao, percUrbana;
  //
  // Como sabemos que a linha contem string int int, podemos fazer a leitura
  // facilmente usando o operador de streaming:
  ss >> nomePais >> populacao >> percUrbana;
  //
  // Note que precisamos arredondar o valor que serah impresso. O arredondamento
  // serah feito via a funcao floor. Ou seja, decimais serao sempre
  // arredondados para baixo:
  unsigned popRural = floor(populacao - (populacao * (percUrbana/100.0)));
  //
  // Uma vez encontrados os valores que precisam ser impressos, seguimos o
  // modelo do enunciado do exercicio:
  std::cout << popRural << " pessoas vivem no campo no " << nomePais <<
    std::endl;
}

bool ContadorNumNaturais::linhaValida(const std::string &str) const {
  for (auto &i : str){
    if((i < '0' or i > '9') and  i != ' ') return false;
  }
  return true;
}

void ContadorNumNaturais::processaLinha(const std::string &str) {
  int sum = 0, val;
  std::stringstream ss(str);
  while (ss >> val) sum += val;
  
  std::cout << sum << std::endl;
}

bool LeitorDeFutebol::linhaValida(const std::string &str) const {
  int aux = 0;
  std::stringstream ss(str);
  std::string s;
  while(ss >> s){
    if(aux % 2 == 0){
      for(auto &&i: s)
        if(!isalpha(i)) return false;
    }else{
      for(auto &&i: s)
        if(i < '0' or i > '9') return false;
    }
    aux++;
  }
  return true;
}

void LeitorDeFutebol::processaLinha(const std::string &str) {
  int val1 = 0, val2 = 0, cont = 0;
  std::string t1, t2, ans;
  std::stringstream ss(str);
  ss >> t1 >> val1 >> t2 >> val2;
  if(val1 > val2) ans = "Vencedor: " + t1;
  else if(val1 < val2) ans = "Vencedor: " + t2;
  else ans = "Empate";
  std::cout << ans << std::endl;
}

void ContadorDePalavras::processaLinha(const std::string &str) {
  std::stringstream ss(str);
  std::string z;
  int cont = 0;
  while (ss >> z) cont++;
  
  std::cout << cont << std::endl;
}

bool InversorDeFrases::linhaValida(const std::string &str) const {
  for (auto &&i : str)
    if(!isalpha(i) and i != ' ') return false;
  
  return true;
}

void InversorDeFrases::processaLinha(const std::string &str) {
  std::stringstream ss(str);
  std::string s;
  std::vector<std::string> v;
  while (ss >> s) v.push_back(s);
  
  for (int i = v.size() - 1; i >= 0; i--) 
    std::cout << v[i] << ' ';
  std::cout << std::endl;
}

bool EscritorDeDatas::linhaValida(const std::string &str) const {
  std::string dateFormat = "\\s*\\d\\d?/\\d\\d?/\\d{4}";
  std::regex format(dateFormat);
  // TODO: Implemente este metodo
  // Note que você pode usar uma expressao regular como:
  // "\\s*\\d\\d?/\\d\\d?/\\d{4}" para saber se a linha eh valida:
  return std::regex_match(str, format);
}

void EscritorDeDatas::processaLinha(const std::string &str) {
  // TODO: Implemente este metodo:
  // Lembre-se que as iniciais dos meses sao:
  // "Jan", "Fev", "Mar", "Abr", "Mai", "Jun", "Jul", "Ago", "Set", "Out",
  // "Nov", e "Dez".
  std::string mes, aux;
  int val = 0;
  bool condition = false;
  for (auto &&i : str){
    if(i == '/') condition = !condition;
    else if(condition) aux += i;
  }
  for (auto &&i : aux) val += i - '0';
  
  if(val == 1) mes = "Jan";
  else if(val == 2) mes = "Fev";
  else if(val == 3) mes = "Mar";
  else if(val == 4) mes = "Abr";
  else if(val == 5) mes = "Mai";
  else if(val == 6) mes = "Jun";
  else if(val == 7) mes = "Jul";
  else if(val == 8) mes = "Ago";
  else if(val == 9) mes = "Set";
  else if(val == 10) mes = "Out";
  else if(val == 11) mes = "Nov";
  else if(val == 12) mes = "Dez";
  
  
  std::cout << mes << std::endl;
}
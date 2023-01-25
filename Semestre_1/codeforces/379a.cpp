#include <iostream>
using namespace std;
 
int main(){
    int a, b, count = 0, horas = 0, resto = 0;
    cin >> a >> b;
    horas += a;
    while(a / b){
        count += a / b;
        resto += a % b;
        a = a / b;
    }
    resto += a % b;
    while(resto / b){
        count += resto / b;
        resto = (resto/b) + (resto % b);
    }
    horas += count;
    cout << horas << endl;
    return 0;
}
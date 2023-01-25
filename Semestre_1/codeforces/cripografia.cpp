#include <iostream>
#include <string>
using namespace std;

string movechar(string txt){
    for ( int i = 0; i < txt.length() ; ++i){
        if ((txt[i] > 64 && txt[i] < 91) || (txt[i] > 96 && txt[i] < 123))
            txt[i] += 3;
    }
    return txt;
}

string invertstring(string txt){
    string copy = txt;
    int len = txt.length();
    for ( int i = len-1, j = 0; i >= 0 ; --i, ++j ){
        txt[j] = copy[i];
    }
    return txt;
}

string laststep(string txt){
    int len = txt.length();
    for ( int i = len / 2 ; i < len ; ++i){
        txt[i] -= 1;
    }
    return txt;
}


int main(){
    string texto;
    long long int n, w;
    cin >> n;
    getchar();
    for  (w = 0 ; w < n ; w++){
        getline(cin,texto);
        texto = laststep(invertstring(movechar(texto)));
        cout << texto << endl;
    }
    return 0;
}
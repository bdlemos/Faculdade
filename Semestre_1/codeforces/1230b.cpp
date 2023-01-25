#include <iostream>
#include <string>
using namespace std;

void minimizing(string &n, int max){
    int len = n.length(), cont = 0, i = 0;
    if (len == 1 && max != 0){
        n[0] = '0';
        return;
    }
    if (n[0] == '1') i++;
    for (i ;  i < len && cont != max ; ++i){
        if (n[0] != '1'){
            n[0] = '1';
            cont++;
        }else if (n[i] != '0'){
            n[i] = '0';
            cont++;
        }
    }
}

int main(){
    int n, k;
    string number;
    cin >> n >> k;
    getchar();
    cin >> number;
    minimizing(number, k);
    cout << number << endl;
    return 0;
}
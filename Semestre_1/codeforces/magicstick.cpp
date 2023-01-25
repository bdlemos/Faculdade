#include <iostream>
using namespace std;
typedef long long unsigned int llu;

string magicstick(int firstnumber, int value){
    if (firstnumber == 1 && value != 1) return "NO";
    if (firstnumber < 4 && value > 3) return "NO";
    else return "YES";
}

int main(){
    int test;
    llu x, y;
    cin >> test;
    for (int i = 0 ; i < test ; ++i){
        cin >> x >> y;
        cout << magicstick(x, y) << endl;
    }
    return 0;
}
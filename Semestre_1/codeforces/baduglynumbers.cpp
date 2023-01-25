#include <iostream>
#include <string>
#include <cmath>
using namespace std;

void BadUgly(int numberdigits){
    int *arr = new int[numberdigits];
    if (numberdigits == 1){
        cout << -1 << endl;
        return;
    }
    for (int j = 0 ; j < numberdigits ; ++j){
        (j == 0) ? arr[j] = 2 : arr[j] = 3;
        cout << arr[j];
    }
    cout << endl;
}

int main(){
    long int t;
    int s;
    cin >> t;
    for (int i = 0 ; i < t; ++i){
        cin >> s;
        BadUgly(s);
    }
    return 0;
}
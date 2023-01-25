#include <iostream>
#include <vector>

using namespace std;

int main(){
    int l1, l2, c2;
    cin >> l1 >> l2 >> c2;  
    
    vector< vector<int> > matriz1(l1, vector<int>(l2));
    vector< vector<int> > matriz2(l2, vector<int>(c2));
    vector< vector<int> > matriz3(l1, vector<int>(c2, 0));
    
    //PREENCHER MATRIZ 1
    for (int i = 0; i < l1; i++)
        for (int j = 0; j < l2; j++)
            cin >> matriz1[i][j];
    //PREENCHER MATRIZ 2
    for (int i = 0; i < l2; i++)
        for (int j = 0; j < c2; j++)
            cin >> matriz2[i][j];

    //MULTIPLICA M1 por M2
    for (int i = 0; i < l1; i++){
        for (int j = 0; j < c2; j++){
            for (int k = 0; k < l2; k++){
                matriz3[i][j] += (matriz1[i][k] * matriz2[k][j]);
            }
            cout << matriz3[i][j];
            if(j == c2 - 1) cout << endl;
            else cout << ' ';
        }
    }
    return 0;
}
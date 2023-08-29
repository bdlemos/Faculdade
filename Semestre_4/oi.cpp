#include <bits/stdc++.h>

using namespace std;

int main(){
    int a = -1, v = -1, n = 1;
    while(true){
        cin >> a >> v;
        if (a == 0 and v == 0) break;
        vector<vector<int>> t(a+1);
        
        for (int i = 0; i < v; i++){
            int aux1, aux2; cin >> aux1 >> aux2;
            t[aux1].push_back(aux2);
            t[aux2].push_back(aux1);
        }
        
        int maior = -1;
        list<int> ans;
        for(int i = 1; i <= a; i++){
            int size = t[i].size();
            if(size > maior){
                ans.clear();
                ans.push_back(i);
                maior = t[i].size();
            }else if(size == maior){
                ans.push_back(i);
            }
        }
        cout << "Teste " << n++ << endl;
        for (auto &&i : ans){
            cout << i << ' ';
        }
        cout << endl<< endl;
    }
    return 0;
}
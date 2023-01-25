#include<bits/stdc++.h>

using namespace std;

typedef tuple<int,int,int,int> T;

int main(){
    int n; cin >> n;
    while (n--){
        set<T> path;
        string s; cin >> s;
        int x = 0, y = 0, ans = 0;
        for (char c : s){
            int ax = x, ay = y;
            if(c == 'N') y++;
            else if(c == 'S') y--;
            else if(c == 'W') x--;
            else x++;
            T direct = make_tuple(ax,ay,x,y);
            T reverse = make_tuple(x,y,ax,ay);
            if(path.find(direct) != path.end() || path.find(reverse) != path.end()){ans++;}
            else{ans+=5; path.insert(direct); path.insert(reverse);}
        }
        cout << ans << endl;
    }
    
    return 0;
}
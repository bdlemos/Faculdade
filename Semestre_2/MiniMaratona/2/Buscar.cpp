#include <bits/stdc++.h>

#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f
#define pii pair<int, int>
#define _ ios_base::sync_withstdio(0);cin.tie(0);

using namespace std;
typedef long long int ll;

struct node{
    ll data;
    node* right;
    node* left;
    node(ll x){
        data = x;
        right = nullptr;
        left = nullptr;
    }
};

node* insert(node* root, ll val){
    if(root == nullptr) return new node(val);
    if(root->data < val) root->right = insert(root->right, val);
    else if(root->data > val) root->left = insert(root->left, val);
    return root;
}

void inOrder(node *root){
    if(root != nullptr){
        inOrder(root->left);
        cout << root->data << ' ';
        inOrder(root->right);
    }
}

void PreOrder(node *root){
    if(root != nullptr){
        cout << root->data << ' ';
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

void PostOrder(node *root){
    if(root != nullptr){
        PostOrder(root->left);
        PostOrder(root->right);
        cout << root->data << ' ';
    }
}

int main() {
    ll x; cin >> x;
    node* root = new node(x);
    while (cin >> x) insert(root, x);
    PreOrder(root);
    cout << endl;
    inOrder(root);
    cout << endl;
    PostOrder(root);
    cout << endl;
    return 0;
}
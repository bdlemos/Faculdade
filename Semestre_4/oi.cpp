//{ Driver Code Starts
//Initial template for C++

#include<bits/stdc++.h> 
using namespace std; 

const int inf = 0x3f3f3f3f;
// } Driver Code Ends
//User function template for C++

class Solution{   
public:
    vector<vector<int>> dp;
    bool isSubsetSum(vector<int>arr, int sum){
        int size = arr.size();
        dp=vector<vector<int>>(sum + 1,vector<int>(size,-1));
        for(int i=0; i < size ; i++) dp[0][i] = 1;

        return SS(arr,sum,0);
    }
    bool SS(vector<int>arr, int sum, int p){
        if(sum == 0) return 1; 
        if((p >= arr.size() and sum > 0) or sum < 0) return 0;
        if(dp[sum][p] != -1) return dp[sum][p];
        
        int ans = max(SS(arr,sum,p+1), SS(arr,sum-arr[p],p+1));
        return dp[sum][p] = ans;
    }
};

//{ Driver Code Starts.
int main() 
{ 
    int t;
    cin>>t;
    while(t--)
    {
        int N, sum;
        cin >> N;
        vector<int> arr(N);
        for(int i = 0; i < N; i++){
            cin >> arr[i];
        }
        cin >> sum;
        
        Solution ob;
        cout << ob.isSubsetSum(arr, sum) << endl;
    }
    return 0; 
} 

// } Driver Code Ends
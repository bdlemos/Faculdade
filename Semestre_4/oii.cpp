//{ Driver Code Starts
#include<bits/stdc++.h>
using namespace std;


// } Driver Code Ends

const int inf = 0x3f3f3f3f;
class Solution
{
    public:
    //Function to return max value that can be put in knapsack of capacity W.
    vector<vector<int>> dp;
    int size;

    Solution() {
        // Example initialization of dp in the constructor
        dp.resize(1000, vector<int>(1000, -inf));
    }


    int knapSack(int W, int wt[], int val[], int n) { 
       for(int i = 0; i < n; i++) dp[0][i] = 0;
       size = n;
       return Sol(W,0,wt,val);
    }
    int Sol(int W, int i, int wt[], int val[]){
        if(W < 0) return -inf;
        if(i >= size) return 0;
        if(dp[W][i] != -inf) return dp[W][i];
        
        int ans = max(Sol(W,i+1,wt,val), Sol(W-wt[i],i+1,wt,val) + val[i]);
        return dp[W][i] = ans;
    }
};

//{ Driver Code Starts.

int main()
 {
    //taking total testcases
    int t;
    cin>>t;
    while(t--)
    {
        //reading number of elements and weight
        int n, w;
        cin>>n>>w;
        
        int val[n];
        int wt[n];
        
        //inserting the values
        for(int i=0;i<n;i++)
            cin>>val[i];
        
        //inserting the weights
        for(int i=0;i<n;i++)
            cin>>wt[i];
        Solution ob;
        //calling method knapSack()
        cout<<ob.knapSack(w, wt, val, n)<<endl;
        
    }
	return 0;
}
// } Driver Code Ends
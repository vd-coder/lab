#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define srt(v) sort(v.begin(),v.end())
#define MOD 1000000007
#define MAX 1000000000000000000
#define lb(v,n) lower_bound(v.begin(),v.end(),n)
#define ub(v,n) upper_bound(v.begin(),v.end(),n)
#define fas ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define endl "\n"


 
 
 int main()
 {
   int b,freq,n;
   cin>>b>>freq>>n;
   vector<int>arr(n+1,0);
   for(int i=1;i<=n;i++)
   {
       cin>>arr[i];
   }
   srt(arr);
   for(int i=1;i<=n;i++)
   {
       cout<<arr[i]<<" ";
   }
 }

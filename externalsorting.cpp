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


 void externalsort(int l,int r,int limit,vector<vector<int>>&v,int freq)
 {
   if(l==r)
   {
       srt(v[l]);
       return;
   }
   int ctr=1;
   int idx=l;
   int size=(r-l+1)/limit;
   if(size==0)
   {
       limit=r-l+1;
       size=1;
   }
   map<pair<int,int>,int>m;
   while(ctr<=limit)
   {
       
       int right=idx+size-1;
       if(ctr==limit)
       {
           right=r;
       }
    //   right=min(r,right);
       externalsort(idx,right,limit,v,freq);
       m.insert(mp(mp(idx,right),idx));
       idx=right+1;
       ctr++;
   }
//   cout<<l<<" "<<r<<endl;
//   cout<<m.size()<<endl;
pair<int,int>p=m.rbegin()->first;
//  cout<<p.first<<" "<<p.second<<endl;
   vector<vector<int>>v1(r-l+2);
   vector<int>v2(r+1,0);
   int i=1;
   int j=0;
//   bool tocontinue=1;
   while(1)
   {
       int mn=INT_MAX;
       auto itt=m.begin();
       for(auto it=m.begin();it!=m.end();it++)
       {
           if(it->second==-1)
           {
               continue;
           }
           int val=v[it->second][v2[it->second]];
           if(val<mn)
           {
               mn=val;
               itt=it;
           }
       }
    //   cout<<mn<<endl;
       v2[itt->second]++;
       if(v2[itt->second]==v[itt->second].size())
       {
           itt->second=itt->second+1;
           if(itt->second==itt->first.second+1)
           {
               itt->second=-1;
           }
       }
       v1[i].pb(mn);
       j++;
       if(j==freq)
       {
           i++;
           j=0;
       }
       bool tocontinue=false;
       for(auto it=m.begin();it!=m.end();it++)
       {
           if(it->second!=-1)
           {
               tocontinue=1;
           }
       }
       if(!tocontinue)
       {
           break;
       }
   }
//   for(int i=1;i<=(r-l+1);i++)
//   {
//       for(int j=0;j<v1[i].size();j++)
//       {
//           cout<<v1[i][j]<<" ";
//       }
//       cout<<endl;
//   }
   int k=1;
  for(int i=l;i<=r;i++)
  {
      v[i].clear();
    //   v[i].resize();
      for(int j=0;j<v1[k].size();j++)
      {
          v[i].pb(v1[k][j]);
      }
      k++;
  }
   return;
 }
 
 int main()
 {
   int b,freq,n;
   cin>>b>>freq>>n;
   vector<int>arr(n+1,0);
   for(int i=1;i<=n;i++)
   {
       cin>>arr[i];
   }
   int pages=n/freq;
   if(n%freq!=0)
   {
       pages++;
   }
   int j=1;
   vector<vector<int>>v(pages+1);
   for(int i=1;i<=n;i++)
   {
       int ctr=0;
       while(ctr<freq&&j<=n)
       {
           v[i].pb(arr[j]);
           j++;
           ctr++;
       }
   }
//   cout<<pages<<endl;
  
  externalsort(1,pages,b-1,v,freq);
  for(int i=1;i<=pages;i++)
  {
      for(int j=0;j<v[i].size();j++)
      {
          cout<<v[i][j]<<" ";
      }
  }
// cout<<pages<<endl;
 }

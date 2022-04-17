#include <bits/stdc++.h>
using namespace std;
#define ll int
#define pb push_back
#define mp make_pair
#define endl "\n"
#define f(i,n) for(ll i=0;i<n;i++)
#define fa(i,a,n) for(ll i=a;i<n;i++)
#define mod 1000000007
int main()
{
    ll sz ;
    cin>>sz;
    vector<vector<ll>>v;
    vector<ll>temp;
    while(true)
    {
        ll x;
        cin>>x;
        if(x==4)
        {
            break;
        }
        if(x==1)
        {
            ll siz;
            cin>>siz;
            ll prim;
            cin>>prim;
            siz+=4;
            bool ans = false;
            f(i,v.size())
            {
                if(sz - v[i][0]>=siz)
                {
                    ans = true;
                    v[i][0]+=siz;
                    v[i].pb(prim);
                    v[i].pb(siz);
                    break;
                }
            }
            if(ans==false)
            {
                temp.pb(16+siz);
                temp.pb(prim);
                temp.pb(siz);
                v.pb(temp);
                temp.clear();
            }
        }
        if(x==2)
        {
            cout<<v.size()<<" ";
            f(i,v.size())
            {
                cout<<v[i].size()/2<<" ";
            }
            cout<<endl;
        }
        if(x==3)
        {
            ll val;
            cin>>val;
            bool ans = false;
            f(i,v.size())
            {
                for(ll j = 1; j<v[i].size(); j+=2)
                {
                    if(v[i][j]==val)
                    {
                        ans = true;
                        cout<<i<<" ";
                        cout<<j/2<<endl;
                        break;
                    }
                }
                if(ans)
                break;
            }
            if(ans == false)
            {
                cout<<-1<<" "<<-1<<endl;
            }
        }
    }   
}

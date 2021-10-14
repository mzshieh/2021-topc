#include<bits/stdc++.h>
#pragma optimize(Ofast)
#define pb push_back
#define x first
#define y second
#define pdd pair<double,double>
#define pii pair<int,int>
#define pll pair<LL,LL>
#define mp make_pair
#define LL long long
#define ULL unsigned long long
#define sqr(x) ((x)*(x))
#define pi acos(-1)
#define MEM(x) memset(x,0,sizeof(x))
#define MEMS(x) memset(x,-1,sizeof(x))
using namespace std;
#define MXN 500005
int a[105];
pii p[105];
int w[105];
vector<int> v[105];
int match[10005];
int vis[105];
bool dfs(int x){
    if(vis[x])return false;
    vis[x]=1;
    for(auto it:v[x]){
        if(match[it]==-1||dfs(match[it])){
            match[it]=x;
            return true;
        }
    }
    return false;
}
int Max_match(vector<int> v){
    MEMS(match);
    int res=0;
    for(auto it:v){
        MEM(vis);
        if(dfs(it))res++;
    }
    return res;
}
int f[105];
int Find(int x){
    if(f[x]==x)return x;
    return f[x]=Find(f[x]);
}
void solve(int T){
    int n,m;
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i = 1;i<=m;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        p[i]=mp(x,y);
        w[i]=sqrt(a[x]+a[y]);
    }
    int k;
    scanf("%d",&k);
    for(int i = 0;i<k;i++){
        int x;
        scanf("%d",&x);
        for(int j = 0;j<x;j++){
            int y;
            scanf("%d",&y);
            v[y].pb(i);
        }  
    }
    int ans[105];
    MEMS(ans);
    for(int i = 0;i<(1<<m);i++){
        int res=0;
        int ok=1;
        for(int j=1;j<=n;j++)f[j]=j;
        vector<int> v;
        for(int j = 0;j<m;j++){
            if(i&(1<<j)){
                res+=w[j+1];
                int a=Find(p[j+1].x),b=Find(p[j+1].y);
                if(a==b)ok=0;
                else f[a]=b;
                v.pb(j+1);
            }
        }
        if(Max_match(v)!=v.size())ok=0;
        if(ok){
            ans[__builtin_popcount(i)]=max(ans[__builtin_popcount(i)],res);
        }
    }
    for(int i = 1;i<n;i++)
    printf("%d ",ans[i]);
    printf("\n");
}
int main(){

    int t=1;0000;
  //  scanf("%d",&t);
    for(int i = 1;i<=t;i++){
       // cerr<<i<<endl;
        solve(i);
    }
    return 0;
}
/*
60.0 0.0 50.0 170.0 
3
40.0 0.0 0.0 0.0
5.0 20.0 5.0 170.0
95.0 0.0 95.0 80.0


0.0 1.0 4.0 1.0 
1
0.0 0.0 4.0 0.0
*/
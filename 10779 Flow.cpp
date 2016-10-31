#include<bits/stdc++.h>
#define vi vector<int>
#define rep(a,b,n) for(int a=b;a<n;a++)
#define pii pair<int,int>
#define fr first
#define sc second
#define LL long long int
#define inf 100000000
#define N 502
using namespace std;
int mf,f,s,t,n;
int res[N][N];
vector<vi > E;
vector<vi > PE;
vi p;
//void ini()
//{
//    for(int i=0;i<n;i++)
//        for(int j=0;j<n;j++)
//        res[i][j]=Res[i][j];
//}
void augm(int v,int me)
{
    if(v==s) {f=me;return;}
    if(p[v]!=-1)
    {
        augm(p[v],min(me,res[p[v]][v]));
        res[p[v]][v]-=f;
        res[v][p[v]]+=f;
    }
    return ;
}
int maxflow()
{
    mf=0;
    while(1)
    {
        f=0;
        vector<bool> vis(n,0);
        queue<int> Q;
        vis[s]=0;
        Q.push(s);
        p.assign(n,-1);
        while(!Q.empty())
        {
        int u=Q.front();
        Q.pop();
        if(u==t) break;
        int z=E[u].size();
        for(int i=0;i<z;i++)
        {
         int v=E[u] [i];
            if((vis[v]==0    )&&( res[u][v]>0))
            vis[v]=1,Q.push(v),p[v]=u;
        }

        }
        augm(t,inf);
        if(f==0) break;
        mf+=f;
    }
    return mf;
}
void add(int a,int b,int c)
{
    E[a].push_back(b);
    E[b].push_back(a);
    res[a][b]=c;
    res[b][a]=0;
}
int A[12];
int B[12][26];
int main(){
    int nn;
    int m;
    int T,I=1;
    T=1;
    cin>>T;
    while(T--)
    {
        scanf("%d",&m);
        if(nn==0) break;
        printf("Case #%d: ",I++);
        scanf("%d",&nn);
     //   memset(res,0,sizeof(res));
        memset(B,0,sizeof(B));
        int a=0,tot=0;
        rep(i,0,m){
        scanf("%d",&A[i]);
        for(int j=0;j<A[i];j++)
        {
            scanf("%d",&a);
            B[i][a]++;
        }
        }
        n=nn+1;
        E.assign(N,vi());
        memset(res,0,sizeof(res));
        rep(i,1,nn+1)
        if(B[0][i])
        add(0,i ,B[0][i]);
        n=0;
        rep(i,1,m)
        {
            n+=nn;
            rep(j,1,nn+1)
            {
            if(B[i][j]>1)
            {
                add(n+j,j,B[i][j]-1);
                rep(k,1,nn+1)
                    if(B[i][k]==0)
                        add(k+n,n+j,1);
            }
            else
                add(j,n+j,1);
            }
        }
        n+=nn;
        n++;
        rep(i,1,nn+1) add(i,n,1);
        s=0;
        t=n++;
        int ans=maxflow();
        printf("%d\n",ans);
    }
    return 0;
}

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
int B[50005];
//int C[50005];
int A[104];
int L[104];
int R[104];
vi Tres;
vector<pii > Res;
int main(){
    int nn;
    int m;
    int T,I=1;
    T=1;
    //cin>>T;
    while(1)
    {
        scanf("%d",&nn);
        if(nn==0) break;
        printf("Case %d: ",I++);
        scanf("%d",&m);
     //   memset(res,0,sizeof(res));
        memset(B,0,sizeof(B));
        int a=0,tot=0;
        rep(i,0,nn){
        scanf("%d %d %d",&A[i],&L[i],&R[i]);
        tot+=A[i];
        B[L[i]]=1;
        B[R[i]]=1;
        a=max(a,R[i]);
        }
        memset(res,0,sizeof(res));
        vector<pii > interval;
        int x=-1,y=-1;
        rep(i,0,a+1)
        if(B[i]==1)
        {
            x=y;
            y=i;
            if(x!=-1) interval.push_back(make_pair(x,y));
        }
        n=nn+interval.size();
        a=interval.size();
        E.assign(n+3,vi());
        rep(i,0,a){
        E[i+nn].push_back(n+2);
        E[n+2].push_back(nn+i);
        res[i+nn][n+2]=m*(interval[i].sc-interval[i].fr);
        res[n+2][i+nn]=0;
        }
        rep(i,0,nn)
        {
            E[i].push_back(n+1);
            E[n+1].push_back(i);
            res[n+1][i]=A[i];
            res[i][n+1]=0;
            rep(j,0,a)
            if(L[i]<=interval[j].fr && R[i]>=interval[j].sc)
            {
                E[i].push_back(nn+j);
                E[nn+j].push_back(i);
                res[i][nn+j]=interval[j].sc-interval[j].fr;
                res[nn+j][i]=0;
            }
        }
        s=n+1;
        t=n+2;
       // cout<<a<<" ";
        n+=4;
        int ans=maxflow();
       if(ans!=tot)
        printf("No\n");
        else
        {
            printf("Yes\n");
            memset(B,0,sizeof(B));
            //memset(C,0,sizeof(C));
            vi D(a,0);
            rep(i,0,a) D[i]=interval[i].fr;
            for(int i=0;i<nn;i++)
            {
            Tres.clear();
            Res.clear();
                for(int j=0;j<a;j++)
                    if(L[i]<=interval[j].fr && interval[j].sc<=R[i])
                    if(res[j+nn][i] > 0)
                {
                    int temp=res[j+nn][i];
                    int k=D[j];
                    while(temp--)
                    {
                        while(B[k]==m ) {k++;if(k==interval[j].sc) k=interval[j].fr;}
                        Tres.push_back(k);
                        B[k]++;
                        k++;
                        if(k==interval[j].sc) k=interval[j].fr;
                    }
                    D[j]=k;
                }
                sort(Tres.begin(),Tres.end());
                x=Tres[0];
                y=Tres[0]+1;
                s=Tres.size();
                if(s!=A[i]) while(1);
               // rep(k,0,s) C[Tres[k]]++;
                for(int k=0;k<s-1;k++)
                {
                    if(y==Tres[k+1])
                        y++;
                    else
                    {
                        Res.push_back(make_pair(x,y));
                        x=Tres[k+1];
                        y=Tres[k+1]+1;
                    }
                }
                Res.push_back(make_pair(x,y));
                s=Res.size();
                printf("%d",s);
                for(int k=0;k<s;k++) printf(" (%d,%d)",Res[k].fr,Res[k].sc);
                printf("\n");
            }

        }
        //rep(i,0,50005) if(C[i]>m) cout<<'h';
    }
    return 0;
}

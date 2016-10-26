#include<bits/stdc++.h>
#define vi vector<int>
#define rep(a,b,n) for(int a=b;a<n;a++)
#define pii pair<int,int>
#define fr first
#define sc second
#define LL long long int
#define inf 1e15
using namespace std;
class UnionFind {                                              // OOP style
private:
  vi p, rank, setSize;                       // remember: vi is vector<int>
  int numSets;
public:
  UnionFind(int N) {
    setSize.assign(N, 1); numSets = N; rank.assign(N, 0);
    p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i; }
  int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
  void unionSet(int i, int j) {
    if (!isSameSet(i, j)) { numSets--;
    int x = findSet(i), y = findSet(j);
    // rank is used to keep the tree short
    if (rank[x] > rank[y]) { p[y] = x; setSize[x] += setSize[y]; }
    else                   { p[x] = y; setSize[y] += setSize[x];
                             if (rank[x] == rank[y]) rank[y]++; } } }
  int numDisjointSets() { return numSets; }
  int sizeOfSet(int i) { return setSize[findSet(i)]; }
};
vector<pair<LL,pii > > Edges;
vector<vector<pair<int,LL> > >E;
vi vis;
LL bfs(int a,int b,int n)
{
    queue<int>Q;
    vector<LL>dis(n+1,-1);
    Q.push(a);
    dis[a]=0;
    while(!Q.empty())
    {
        int u=Q.front();
        Q.pop();
        int z=E[u].size();
        rep(i,0,z)
            {
                int v=E[u][i].fr;
                if(dis[v]!=-1) continue;
                if(v==b)
                    return max(dis[u],E[u][i].sc);
                Q.push(v);
                dis[v]=max(dis[u],E[u][i].sc);
            }
    }
    return dis[b];
}
LL mst(int V,int m,int Q)
{
  LL mst_cost = 0;
  UnionFind UF(V);                     // all V are disjoint sets initially
  sort(Edges.begin(),Edges.end());
  for (int i = 0; i < m; i++) {                      // for each edge, O(E)
    pair<LL, pii> front = Edges[i];
    if (!UF.isSameSet(front.second.first, front.second.second)) {  // check
            //vis[i]=1;
      //mst_cost =max(mst_cost, front.first);                // add the weight of e to MST
      E[front.sc.fr].push_back(make_pair(front.sc.sc,front.fr));
      E[front.sc.sc].push_back(make_pair(front.sc.fr,front.fr));
      UF.unionSet(front.second.first, front.second.second);    // link them
  } }
  int a,b;
    rep(i,0,Q)
    {
            scanf("%d %d",&a,&b);
            if(!UF.isSameSet(a,b)) printf("no path\n");
            else
                printf("%lld\n",bfs(a,b,V));
    }
  return mst_cost;
}
//int col;
//void dfs(int u)
//{
//    vis[u]=col;
//    int z=E[u].size();
//    for(int i=0;i<z;i++)
//        if(vis[E[u][i]]==0)
//        dfs(E[u][i]);
//    return;
//}
int main(){
    int n;
    int m;
    int T,I=1;
    //cin>>T;
//    col=1;
int Q;
    while(scanf("%d %d %d",&n,&m,&Q))
    {
        if(n==0 && m==0&& Q==0) break;
        if(I>1) printf("\n");
        printf("Case #%d\n",I++);
        Edges.clear();
        E.assign(n+1,vector<pair<int,LL> > ());
        vis.assign(m+1,0);
        int a,b;
        LL c;
        LL ans=0;
        rep(i,0,m)
        {
            scanf("%d %d %lld",&a,&b,&c);
            Edges.push_back(make_pair(c,make_pair(a,b)));
        }
        ans=mst(n+1,Edges.size(),Q);
    }
    return 0;
}

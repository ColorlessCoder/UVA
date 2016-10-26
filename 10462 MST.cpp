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
vi vis;
vi MST;
int dont;
LL mst(int V,int m)
{
  LL mst_cost = 0;
  UnionFind UF(V);                     // all V are disjoint sets initially
  sort(Edges.begin(),Edges.end());
  for (int i = 0; i < m; i++) {                      // for each edge, O(E)
    pair<LL, pii> front = Edges[i];
    if(i==dont) continue;
    if (!UF.isSameSet(front.second.first, front.second.second)) {  // check
           // vis[i]=1;
    if(dont==-1) MST.push_back(i);
      mst_cost += front.first;                // add the weight of e to MST
      UF.unionSet(front.second.first, front.second.second);    // link them
  } }
  rep(i,1,V) if(!UF.isSameSet(1,i)) return inf;
  return mst_cost;
}
int main(){
    int n;
    int m;
    int T,I=1;
    cin>>T;
    while(T--)
    {scanf("%d %d",&n,&m);
        printf("Case #%d : ",I++);
      //  if(n==0 && m==0) break;
        Edges.clear();
        vis.assign(n+1,0);
        int a,b;
        LL c;
        LL S1,S2=0;
        rep(i,0,m)
        {
            scanf("%d %d %lld",&a,&b,&c);
            Edges.push_back(make_pair(c,make_pair(a,b)));
        }
        dont=-1;
        MST.clear();
        S1=mst(n+1,Edges.size());
        S2=inf;
        if(S1==inf)
        {
            printf("No way\n");
            continue;
        }
        rep(i,0,n-1){
        dont=MST[i];S2=min(S2,mst(n+1,Edges.size()));
        }
        if(S2==inf)
            printf("No second way\n");
        else printf("%lld\n",S2);
    }
    return 0;
}

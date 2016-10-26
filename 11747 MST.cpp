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
vector<pair<double,pii > > Edges;
vi vis;
double mst(int V,int m)
{
  double mst_cost = 0;
  UnionFind UF(V);                     // all V are disjoint sets initially
  sort(Edges.begin(),Edges.end());
  for (int i = 0; i < m; i++) {                      // for each edge, O(E)
    pair<int, pii> front = Edges[i];
    if (!UF.isSameSet(front.second.first, front.second.second)) {  // check
            vis[i]=1;
      mst_cost += front.first;                // add the weight of e to MST
      UF.unionSet(front.second.first, front.second.second);    // link them
  } }
  return mst_cost;
}
int main(){
    int n;
    int m;
    int T,I=1;
    //cin>>T;
    while(scanf("%d %d",&n,&m)==2)
    {
        //printf("Case #%d: ",I++);
        if(n==0 && m==0) break;
        Edges.clear();
        vis.assign(m+1,0);
        int a,b,c;
        double ans=0;
        rep(i,0,m)
        {
            scanf("%d %d %d",&a,&b,&c);
            Edges.push_back(make_pair(c,make_pair(a,b)));
        }
        mst(n+1,Edges.size());
        vi A;
        rep(i,0,m) if(vis[i]==0) A.push_back(Edges[i].fr);
        a=0;
        b=A.size();
        if(b==0) printf("forest");
        else rep(i,0,b)
        {
            if(a) printf(" ");a=1;
            printf("%d",A[i]);
        }
        printf("\n");
    }
    return 0;
}

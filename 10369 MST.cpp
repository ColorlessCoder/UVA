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
vector<pair<double,pii > > MST;
//vector<vector<pair<int,LL> > >E;
vi vis;

LL mst(int V,int m)
{
  LL mst_cost = 0;
  UnionFind UF(V);                     // all V are disjoint sets initially
  sort(Edges.begin(),Edges.end());
  for (int i = 0; i < m; i++) {                      // for each edge, O(E)
    pair<double, pii> front = Edges[i];
    if (!UF.isSameSet(front.second.first, front.second.second)) {  // check
    MST.push_back(front);
      UF.unionSet(front.second.first, front.second.second);    // link them
  } }

  return mst_cost;
}
double dist (double a,double b,double c,double d){return hypot(a-c,b-d);}
vector<pair<double ,double> > points;
int main(){
    int n;
    int m;
    int T,I=1;
    cin>>T;
//    col=1;
int Q;
    while(T--)
    {
        //if(n==0 && m==0&& Q==0) break;
//        if(I>1) printf("\n");
//        printf("Case #%d\n",I++);
      Edges.clear();
      scanf("%d %d",&n,&m);
      points.clear();
        //E.assign(n+1,vector<pair<int,LL> > ());
        vis.assign(m+1,0);
        double a,b;
        double c;
        rep(i,0,m)
        {
            scanf("%lf %lf",&a,&b);
        rep(j,0,i){
          //  cout<<points[j].fr<<" "<<points[j].sc<<endl;
            c=dist(a,b,points[j].fr,points[j].sc);
            Edges.push_back(make_pair(c,make_pair(i,j)));
        }
        points.push_back(make_pair(a,b));
        }
        MST.clear();
        mst(m+1,Edges.size());
        sort(MST.begin(),MST.end());
        double ans=MST[m-n-1].fr;
            printf("%.2lf\n",ans);
    }
    return 0;
}

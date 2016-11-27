#include<bits/stdc++.h>
#define unt unsigned long long int
using namespace std;
int dp[2005];
int A[2005][2005];
int main()
{
    int T,I=1;
  //  cin>>T;
    int n,m;
    while(scanf("%d",&T)&& T)
    {
        while(T--){
        int a,h,f;
        memset(dp,0,sizeof(dp));
        memset(A,0,sizeof(A));
        scanf("%d %d %d",&n,&h,&f);
        for(int i=0;i<n;i++)
        {
            scanf("%d",&m);
            for(int j=0;j<m;j++)
            {
                scanf("%d",&a);
                A[i][a]++;
            }
        }
        for(int i=0;i<n;i++) dp[h]=max(dp[h],A[i][h]);
        for(int i=h-1;i>=0;i--)
            for(int j=0;j<n;j++)
        {
            A[j][i]+=max(A[j][i+1],(i+f <= h)?dp[i+f]:0);
            dp[i]=max(dp[i],A[j][i]);
        }
        printf("%d\n",dp[0]);
        }
    }
    return 0;
}

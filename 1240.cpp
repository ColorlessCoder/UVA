#include<bits/stdc++.h>
#define unt unsigned long long int
using namespace std;
typedef long long ll;
typedef vector<int> vi;
int n;
int dp[3][300][1<<12];
int A[3][20];
int call(int last,int val,int mask)
{
    if(mask==0) return 0;
    int &ret=dp[last][val][mask];
    if(ret!=-1) return ret;
    int d=(mask== (1<<n)-1)?4:last;
    ret=0;
    for(int i=0;i<n;i++)
        if(mask&(1<<i))
    {
        if((d!=0)&&(A[0][i]+val <=280)) ret=max(ret,1+call(0,val+A[0][i],mask&(~(1<<i))));
        if((d!=1)&&(A[1][i]+val <=280)) ret=max(ret,1+call(1,val+A[1][i],mask&(~(1<<i))));
        if((d!=2)&&(A[2][i]+val <=280)) ret=max(ret,1+call(2,val+A[2][i],mask&(~(1<<i))));
    }
    return ret;
}
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        scanf("%d",&n);
        for(int i=0;i<3;i++)
            for(int j=0;j<n;j++)
            scanf("%d",&A[i][j]);
            memset(dp,-1,sizeof(dp));
        printf("%d\n",call(1,0,(1<<n)-1));
    }
    return 0;
}

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=1e9;
const int magic=348;
const double eps=1e-10;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,k;
int dp[101][101][260][9];
int a[148];bool exist[18];

int main ()
{
	int i,j,Mask,cur,toMask,ca=0;
	while (scanf("%d%d",&n,&k) && n && k)
	{
		memset(exist,false,sizeof(exist));
		for (i=1;i<=n;i++) a[i]=getint()-24,exist[a[i]]=true;
		for (i=0;i<=n;i++)
			for (j=0;j<=k;j++)
				for (Mask=0;Mask<=(1<<8)-1;Mask++)
					for (cur=0;cur<=8;cur++)
						dp[i][j][Mask][cur]=INF;
		dp[0][0][(1<<8)-1][0]=0;
		for (i=0;i<=n-1;i++)
			for (j=0;j<=k;j++)
				for (Mask=0;Mask<=(1<<8)-1;Mask++)
					for (cur=0;cur<=8;cur++)
						if (dp[i][j][Mask][cur]<INF)
						{
							//i+1 is chosen
							if (j<k) dp[i+1][j+1][Mask][cur]=min(dp[i+1][j+1][Mask][cur],dp[i][j][Mask][cur]);
							//i+1 isn't chosen
							toMask=(Mask&(1<<(a[i+1]-1))?Mask^(1<<(a[i+1]-1)):Mask);
							dp[i+1][j][toMask][a[i+1]]=min(dp[i+1][j][toMask][a[i+1]],dp[i][j][Mask][cur]+(a[i+1]!=cur));
						}
		int ans=INF,curans;
		for (Mask=0;Mask<=(1<<8)-1;Mask++)
			for (cur=0;cur<=8;cur++)
				if (dp[n][k][Mask][cur]<INF)
				{
					curans=dp[n][k][Mask][cur];
					for (j=1;j<=8;j++)
						if (exist[j] && Mask&(1<<(j-1))) curans++;
					ans=min(ans,curans);
				}
		printf("Case %d: %d\n\n",++ca,ans);
	}
	return 0;
}

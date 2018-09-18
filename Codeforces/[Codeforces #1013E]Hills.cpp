#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=5000;

int dp[MAXN+48][MAXN+48][2][2];
int ans[MAXN+48];

int n;
int a[MAXN+48];

inline int Up(int x) {if (x&1) return x/2+1; else return x/2;}
inline int update(int &x,int y) {x=min(x,y);}

int main ()
{
	int i,j,k1,k2;n=getint();
	for (i=1;i<=n;i++) a[i]=getint();
	if (n==1)
	{
		puts("0");
		return 0;
	}
	if (n==2)
	{
		if (a[1]==a[2]) puts("1"); else puts("0");
		return 0;
	}
	for (i=1;i<=n;i++)
		for (j=0;j<=Up(i);j++)
			for (k1=0;k1<=1;k1++)
				for (k2=0;k2<=1;k2++)
					dp[i][j][k1][k2]=INF;
	dp[2][0][0][0]=0;
	dp[2][1][0][1]=max(0,a[1]-(a[2]-1));
	dp[2][1][1][0]=0;
	for (i=2;i<=n-1;i++)
		for (j=0;j<=Up(i);j++)
			for (k1=0;k1<=1;k1++)
				for (k2=0;k2<=1;k2++)
					if (dp[i][j][k1][k2]<INF)
					{
						if (k2==1)
						{
							update(dp[i+1][j][1][0],dp[i][j][k1][k2]);
							continue;
						}
						if (k1==0)
						{
							update(dp[i+1][j+1][0][1],dp[i][j][k1][k2]+max(0,a[i]-(a[i+1]-1)));
							update(dp[i+1][j][0][0],dp[i][j][k1][k2]);
						}
						else
						{
							update(dp[i+1][j+1][0][1],dp[i][j][k1][k2]+max(0,a[i]-min(a[i-1]-1,a[i+1]-1)));
							update(dp[i+1][j][0][0],dp[i][j][k1][k2]+max(0,a[i]-(a[i-1]-1)));
						}
					}
	for (j=0;j<=Up(n);j++)
		if (dp[n][j][1][0]<INF) dp[n][j][1][0]+=max(0,a[n]-(a[n-1]-1));
	for (j=0;j<=Up(n);j++)
		ans[j]=min(dp[n][j][0][0],min(dp[n][j][0][1],dp[n][j][1][0]));
	for (j=1;j<=Up(n);j++) printf("%d ",ans[j]);
	puts("");return 0;
}

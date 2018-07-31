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

const LL MOD=1e9+7;
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

char s[248];int len;
char ss[448][148];int slen[448];int n;
int val[448];
int DP[348][348],Dp[348];
int dp[348][348];

inline int solve(int left,int right)
{
	int i,j,k,m;
	for (i=1;i<=n;i++)
	{
		if (ss[i][1]!=s[left]) continue;
		for (j=left;j<=right;j++)
			for (k=0;k<=slen[i];k++)
				dp[j][k]=-INF;
		dp[left][1]=val[i];
		for (j=left+1;j<=right;j++)
			for (k=2;k<=slen[i];k++)
				if (ss[i][k]==s[j])
					for (m=left;m<=j-1;m++)
						if (s[m]==ss[i][k-1])
							dp[j][k]=max(dp[j][k],dp[m][k-1]+(m+1<=j-1?DP[m+1][j-1]:0));
		for (j=left;j<=right;j++)
			DP[left][right]=max(DP[left][right],dp[j][slen[i]]+(j+1<=right?DP[j+1][right]:0));
	}
	return DP[left][right];
}

int main ()
{
	int i,j;
	scanf("%s",s+1);len=strlen(s+1);
	n=getint();
	for (i=1;i<=n*2-1;i+=2)
	{
		scanf("%s%d",ss[i]+1,&val[i]);
		slen[i]=strlen(ss[i]+1);
		slen[i+1]=slen[i];val[i+1]=val[i];
		for (j=slen[i+1];j;j--) ss[i+1][j]=ss[i][slen[i+1]-j+1];
	}
	n*=2;
	for (i=0;i<=len;i++)
		for (j=0;j<=len;j++)
			DP[i][j]=-INF;
	for (i=1;i<=len;i++)
		for (j=1;j<=len-i+1;j++)
			DP[j][j+i-1]=solve(j,j+i-1);
	Dp[0]=0;
	for (i=1;i<=len;i++)
	{
		Dp[i]=Dp[i-1];
		for (j=0;j<=i-1;j++)
			Dp[i]=max(Dp[i],Dp[j]+DP[j+1][i]);
	}
	printf("%d\n",Dp[len]);
	return 0;
}

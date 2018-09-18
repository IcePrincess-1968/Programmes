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
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,k;
int r[48][48];
int dp[17][10][70048];
vector<int> v[20];
bool valid[48][70048];
int num[70048];

inline int calc(int Mask)
{
	int res=1,nn=__builtin_popcount(Mask);
	while (nn>1)
	{
		if (nn%2==0) nn>>=1,res++; else nn=nn/2+1,res++;
	}
	return res;
}

inline int solve(int i,int h,int Mask)
{
	if (dp[i][h][Mask]) return dp[i][h][Mask];
	if (__builtin_popcount(Mask)==1) return 1;
	int sub,j;
	dp[i][h][Mask]=0;
	for (sub=(Mask-1)&Mask;sub;sub=(sub-1)&Mask)
	{
		if (num[sub]>h-1 || num[Mask^sub]>h-1 || !(sub&(1<<(i-1)))) continue;
		int tmp=(Mask^sub);
		do
		{
			j=__builtin_ctz(tmp)+1;
			if (r[i][j]) dp[i][h][Mask]+=solve(i,h-1,sub)*solve(j,h-1,Mask^sub);
			tmp^=(1<<(j-1));
		}
		while (tmp);
	}
	return dp[i][h][Mask];
}


int main ()
{
	freopen ("f.in","r",stdin);
	freopen ("f.out","w",stdout);
	int i,j,Mask,sub,h;
	n=getint();k=getint();
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			r[i][j]=getint();
	for (Mask=0;Mask<=(1<<n)-1;Mask++) num[Mask]=calc(Mask);
	int maxheight=calc((1<<n)-1);
	printf("%d\n",solve(k,maxheight,(1<<n)-1));
	return 0;
}

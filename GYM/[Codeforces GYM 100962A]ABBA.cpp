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
const int INF=2e9;
const int magic=348;
const long double eps=1e-2;

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline long double myabs(double x)
{
	return x>=eps?x:-x;
}

int n,m;
long double b[248][248];
bool taken[248];
int ans=0;

void Remove(int r1,int r2,int col)
{
	int j;long double tmp=b[r1][col];
	for (j=1;j<=m;j++) b[r1][j]-=b[r2][j]*tmp;
}

void solve()
{
	memset(taken,false,sizeof(taken));
	int i,j,rr;
	for (j=1;j<=m;j++)
	{
		rr=1;
		while (rr<=n && (taken[rr] || myabs(b[rr][j])<eps)) rr++;
		if (rr>n) continue;
		taken[rr]=true;
		if (myabs(b[rr][j]-1.0)>eps)
		{
			long double tmp=b[rr][j];
			for (i=1;i<=m;i++) b[rr][i]/=tmp;
		}
		for (i=1;i<=n;i++) if (!taken[i] && myabs(b[i][j])>eps) Remove(i,rr,j);
	}
}

int main ()
{
	int i,j;
	n=getint();m=getint();
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			cin>>b[i][j];
	solve();
	for (i=1;i<=n;i++) if (taken[i]) ans++;
	printf("%d\n",ans);
	return 0;
}

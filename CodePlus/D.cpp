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

int n,m;
int a[20][20];
bool visited[20][20];
int ans=0;

void dfs(int x,int y)
{
	if (x==n+1)
	{
		ans++;
		return;
	}
	int xx,yy;
	xx=x;yy=y+1;
	if (yy==m+1)
	{
		xx++;
		yy=1;
	}
	if (a[i][j]) dfs(xx,yy);

int main ()
{
	int i,j;
	cin>>n>>m;
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			cin>>a[i][j];
	dfs(1,1);

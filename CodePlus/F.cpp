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

vector<int> a[4000048];
int n,m;
vector<int> sum[4000048];

int main ()
{
	int i,j,x;
	n=getint();m=getint();
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
		{
			x=getint();
			a[i].pb(x);
		}
	for (i=1;i<=n;i++)
		for (j=0;j<=m-1;j++)
			if (j==0) sum[i].pb(a[i][0]); else sum[i].pb(sum[i].back+a[i][j]);
	for (i=2;i<=n;i++)
		for (j=0;j<=m-1;j++)
			sum[i][j]+=sum[i-1][j];
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			for (int len=
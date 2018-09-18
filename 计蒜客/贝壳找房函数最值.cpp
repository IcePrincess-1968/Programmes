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
const LB eps=1e-10;
const LB pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

Pair a[100048];
int n,g;

inline bool cmp(Pair x,Pair y)
{
	return y.x*x.y+y.y>x.x*y.y+x.y;
}

int main ()
{
	int ca;ca=getint();
	while (ca--)
	{
		int i;n=getint();g=getint();
		for (i=1;i<=n;i++) a[i].x=getint();
		for (i=1;i<=n;i++) a[i].y=getint();
		sort(a+1,a+n+1,cmp);
		int ans=g;
		for (i=1;i<=n;i++) ans=(ans*a[i].x+a[i].y)%10;
		printf("%d\n",ans);
	}
	return 0;
}

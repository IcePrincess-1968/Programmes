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

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline LL getLL()
{
	char ch;LL res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n;
LL a[148];

struct LinerBase
{
	LL d[60];
	inline void init()
	{
		for (int i=0;i<=50;i++) d[i]=0;
	}
	inline void add(LL x)
	{
		int i;
		for (i=50;i>=0;i--)
		{
			if ((x>>i)&1)
				if (d[i]==0)
				{
					d[i]=x;
					break;
				}
				else
					x^=d[i];
		}
	}
	inline LL querymax()
	{
		LL res=0;int i;
		for (i=50;i>=0;i--)
			if ((res^d[i])>res) res^=d[i];
		return res;
	}
}base;

int main ()
{
	n=getint();base.init();
	for (int i=1;i<=n;i++) a[i]=getLL(),base.add(a[i]);
	printf("%lld\n",base.querymax());
	return 0;
}

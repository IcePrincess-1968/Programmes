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

int k,n;

inline int doit(int x)
{
	x=(x-1)%n+1;
	if (x<=0) x+=n;
	return x;
}

int main ()
{
	int i,j;
	k=getint();n=k*2;
	printf("%d\n",n);
	int cur,to,starter=1;int delta;
	for (i=1;i<=k;i++)
	{
		cur=starter;delta=1-n;
		to=doit(cur+delta);
		for (j=1;j<=n-1;j++)
		{
			printf("%d %d\n",cur,to);
			delta=-delta;if (delta<0) delta++; else delta--;
			cur=to;to=doit(cur+delta);
		}
		starter=doit(--starter);
	}
	return 0;
}
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

int n;
struct CLOUD
{
	int x,y;
	int rlen,clen;
}a[100048],b[100048];
int rtot,ctot;

inline bool judge(int ind1,int ind2)
{
	int st1,et1,st2,et2;
	st1=b[ind2].x-(a[ind1].x+a[ind1].rlen)+1;
	et1=b[ind2].x+b[ind2].rlen-a[ind1].x-1;
	st2=a[ind1].y-(b[ind2].y+b[ind2].clen)+1;
	et2=a[ind1].y+a[ind1].clen-b[ind2].y-1;
	if (et1<st2 || et2<st1) return false; else return true;
}

int main ()
{
	int i,j,ca,x,y,rlen,clen,dir;
	ca=getint();
	while (ca--)
	{
		rtot=0;ctot=0;
		n=getint();
		for (i=1;i<=n;i++)
		{
			x=getint();y=getint();rlen=getint();clen=getint();dir=getint();
			if (dir==0) a[++rtot]=CLOUD{x,y,rlen,clen}; else b[++ctot]=CLOUD{x,y,rlen,clen};
		}
		bool f=false;
		for (i=1;i<=rtot;i++)
		{
			for (j=1;j<=ctot;j++)
				if (judge(i,j))
				{
					f=true;
					break;
				}
			if (f) break;
		}
		if (f) printf("2\n"); else printf("1\n");
	}
	return 0;
}
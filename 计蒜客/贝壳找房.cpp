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

const int MOD=1e9+9;
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

LL a[1000048];
int b[100048];

int main ()
{
	a[1]=1;int i,m;
	for (i=2;i<=1000000;i++) a[i]=a[i-1]+(i-1)+2;
	int n;n=getint();
	while (n--)
	{
		m=getint();
		for (i=1;i<=m;i++) b[i]=getint();
		int pt=1;
		for (pt=1;a[pt]<b[1];pt++) {}
		if (a[pt]>b[1]) {puts("no");continue;}
		bool f=true;
		for (i=pt;i<=pt+m-1;i++) if (a[i]!=b[i-pt+1]) {f=false;break;}
		if (f) puts("yes"); else puts("no");
	}
	return 0;
}

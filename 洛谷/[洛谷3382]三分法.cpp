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

const int MOD=998244353;
const LL LINF=2e16;
const int INF=1e9;
const int magic=348;
const double eps=1e-7;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n;double L,R;
double coef[48];

inline double mypow(double x,int y)
{
	double res=1;
	while (y--) res=res*x;
	return res;
}

inline double calc(double X)
{
	double res=0;
	for (register int i=n;i>=0;i--) res=res+mypow(X,i)*coef[i];
	return res;
}

int main ()
{
	int i;double l,r,lmid,rmid;
	n=getint();scanf("%lf%lf",&L,&R);
	for (i=n;i>=0;i--) scanf("%lf",&coef[i]);
	l=L;r=R;
	while (r-l>eps)
	{
		lmid=l+(r-l)/3;rmid=r-(r-l)/3;
		if (calc(lmid)<calc(rmid)) l=lmid; else r=rmid;
	}
	printf("%.5lf\n",l);
	return 0;
}

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
#define DEBUG(...) 
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
int vn[48],vm[48];
char s[48];
int a[2000048],atot,b[2000048],btot;
bool dpn[2000048],dpm[2000048];
vector<int> stan[48],stam[48];
int A[48],B[48],t;

int main ()
{
	int i,j,sz,Mask,toMask;n=getint();m=getint();
	for (i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		for (j=1;j<=m;j++) if (s[j]=='1') vn[i]|=(1<<(j-1)),vm[j]|=(1<<(i-1));
	}
	for (i=1;i<=n;i++) A[i]=getint();
	for (i=1;i<=m;i++) B[i]=getint();
	t=getint();
	atot=btot=0;
	for (Mask=1;Mask<(1<<n);Mask++) stan[__builtin_popcount(Mask)].pb(Mask);
	for (Mask=1;Mask<(1<<m);Mask++) stam[__builtin_popcount(Mask)].pb(Mask);
	dpn[0]=true;a[++atot]=0;
	for (sz=1;sz<=n;sz++)
		for (j=0;j<int(stan[sz].size());j++)
		{
			Mask=stan[sz][j];toMask=0;
			for (i=1;i<=n;i++) if (Mask&(1<<(i-1))) toMask|=vn[i];
			if (__builtin_popcount(toMask)<sz) {dpn[Mask]=false;continue;}
			bool f=true;
			for (i=1;i<=n;i++)
				if (Mask&(1<<(i-1)))
				{
					toMask=(Mask^(1<<(i-1)));
					if (!dpn[toMask]) {f=false;break;}
				}
			dpn[Mask]=f;
			if (dpn[Mask]==true)
			{
				int sum=0;
				for (i=1;i<=n;i++) if (Mask&(1<<(i-1))) sum+=A[i];
				a[++atot]=sum;
			}
		}
	dpm[0]=true;b[++btot]=0;
	for (sz=1;sz<=m;sz++)
		for (j=0;j<int(stam[sz].size());j++)
		{
			Mask=stam[sz][j];toMask=0;
			for (i=1;i<=m;i++) if (Mask&(1<<(i-1))) toMask|=vm[i];
			if (__builtin_popcount(toMask)<sz) {dpm[Mask]=false;continue;}
			bool f=true;
			for (i=1;i<=m;i++)
				if (Mask&(1<<(i-1)))
				{
					toMask=(Mask^(1<<(i-1)));
					if (!dpm[toMask]) {f=false;break;}
				}
			dpm[Mask]=f;
			if (dpm[Mask]==true)
			{
				int sum=0;
				for (i=1;i<=m;i++) if (Mask&(1<<(i-1))) sum+=B[i];
				b[++btot]=sum;
			}
		}
	sort(a+1,a+atot+1);sort(b+1,b+btot+1);
	LL ans=0;int pt=btot+1;
	for (i=1;i<=atot;i++)
	{
		for (;pt>1 && a[i]+b[pt-1]>=t;pt--) {}
		ans+=(btot-pt+1);
	}
	printf("%lld\n",ans);
	return 0;
}
/*
3 2
01
11
10
1 2 3
4 5 
8
*/

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

int n,k,d;
int a[100048][5];
int anslen,l,r;
vector<int> cur;

bool check(int pos)
{
	int i,j;
	for (i=0;i<int(cur.size());i++)
		for (j=1;j<=d;j++)
			if (cur[i]==a[pos][j]) return true;
	return false;
}

int go_left(int curl,int liml)
{
	while (curl>=liml && check(curl)) curl--;
	return curl;
}

int go_right(int curr,int limr)
{
	while (curr<=limr && check(curr)) curr++;
	return curr;
}

void calc(int curl,int curr,int left,int right,int step,int lim)
{
	if (step!=1)
	if (curr-curl+1-2>anslen)
	{
		anslen=curr-curl+1-2;
		l=curl+1;r=curr-1;
	}
	else if (curr-curl+1-2==anslen && curl+1<l)
	{
		l=curl+1;r=curr-1;
	}
	int i,tmpl,tmpr;
	if (step>lim) return;
	for (i=1;i<=d*2;i++)
		if (i<=d)
		{
			if (curl<left) continue;
			cur.pb(a[curl][i]);
			tmpl=go_left(curl,left);
			tmpr=go_right(curr,right);
			calc(tmpl,tmpr,left,right,step+1,lim);
			cur.pop_back();
		}
		else
		{
			if (curr>right || curr==curl) continue;
			cur.pb(a[curr][i-d]);
			tmpl=go_left(curl,left);
			tmpr=go_right(curr,right);
			calc(tmpl,tmpr,left,right,step+1,lim);
			cur.pop_back();
		}
}

void solve2(int left,int right)
{
	int mid=(left+right)>>1;
	calc(mid,mid,left,right,1,2);
	if (left+1<right)
	{
		solve2(left,mid-1);
		solve2(mid+1,right);
	}
}

void solve3(int left,int right)
{
	int mid=(left+right)>>1;
	calc(mid,mid,left,right,1,3);
	if (left+1<right)
	{
		solve3(left,mid-1);
		solve3(mid+1,right);
	}
}

int main ()
{
	freopen ("D-large.in","r",stdin);
	freopen ("D-large.out","w",stdout);
	int i,j,ca,tt=0;
	ca=getint();
	while (ca--)
	{
		n=getint();d=getint();k=getint();
		for (i=1;i<=n;i++)
			for (j=1;j<=d;j++)
				a[i][j]=getint();
		anslen=-1;
		if (k==2) solve2(1,n); else solve3(1,n);
		printf("Case #%d: %d %d\n",++tt,l-1,r-1);
	}
	return 0;
}
/*
4
8 1 2
1 2 3 2 4 5 4 6
4 3 2
1 2 3 4 5 6 7 8 9 10 11 12
6 2 3
10 20 50 60 70 30 40 40 30 30 20 40
10 1 3
2 4 3 1 4 5 3 1 1 2
*/
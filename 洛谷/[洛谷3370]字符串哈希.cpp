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

typedef pair<LL,LL> pii;
const int p=19260817;
const int MOD1=1e9+7,MOD2=998244353;

int n;
char s[1548];int len;
pii a[100048];

pii gethash()
{
	LL res1=0,res2=0;int i;
	for (i=1;i<=len;i++)
	{
		res1=(res1*p+s[i])%MOD1;
		res2=(res2*p+s[i])%MOD2;
	}
	return mp(res1,res2);
}

int main ()
{
	int i;
	n=getint();
	for (i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		len=strlen(s+1);
		a[i]=gethash();
	}
	sort(a+1,a+n+1);
	int ans=1;
	for (i=2;i<=n;i++)
		if (a[i]!=a[i-1]) ans++;
	printf("%d\n",ans);
	return 0;
}

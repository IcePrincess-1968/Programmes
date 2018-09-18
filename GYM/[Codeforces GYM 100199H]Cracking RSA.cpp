#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <map>
#include <stack>
#include <set>
#include <vector>
#include <queue>
#include <deque>
#include <cassert>
#include <sstream>
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LL long long
#define LB long double
#define Pair pair<int,int>
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const double eps=1e-10;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const LL lim=1e15;

inline int getint()
{
	char ch;bool f;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	f=(ch=='-')?true:false;
	res=(ch=='-')?0:ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?-res:res;
}

int t,n;
int a[148];
int b[148][148];
bool taken[148];

int prime[1048],tot=0;
bool isprime[1048];
void sieve()
{
	memset(isprime,true,sizeof(isprime));
	int i,j;
	for (i=2;i<=1000;i++)
	{
		if (isprime[i]) prime[++tot]=i;
		for (j=1;j<=tot;j++)
		{
			if (prime[j]*i>1000) break;
			isprime[prime[j]*i]=false;
			if (i%prime[j]==0) break;
		}
	}
}

void Remove(int r1,int r2)
{
	for (int j=1;j<=n;j++) b[r1][j]^=b[r2][j];
}

void solve()
{
	int rr,i,j;
	memset(taken,false,sizeof(taken));
	for (j=1;j<=n;j++)
	{
		rr=1;
		while (rr<=t && (taken[rr] || b[rr][j]==0)) rr++;
		if (rr>t) continue;
		taken[rr]=true;
		for (i=1;i<=t;i++) if (!taken[i] && b[i][j]) Remove(i,rr);
	}
}

int main ()
{
	freopen ("rsa.in","r",stdin);
	freopen ("rsa.out","w",stdout);
	int i,j,cnt;
	scanf("%d%d",&t,&n);
	for (i=1;i<=n;i++) scanf("%d",&a[i]);
	sieve();
	for (i=1;i<=n;i++)
		for (j=1;j<=t;j++)
		{
			cnt=0;
			while (a[i]%prime[j]==0) a[i]/=prime[j],cnt++;
			b[j][i]=cnt%2;
		}
	solve();
	int Free=n;
	for (i=1;i<=t;i++) if (taken[i]) Free--;
	LL res1=0,res2=1ll,prod;
	for (i=1;i<=Free;i++)
	{
		prod=2ll*res2;
		res2=prod%lim;prod/=lim;
		res1=2ll*res1+prod;
	}
	res2--;
	if (res2<0ll) res1--,res2+=lim;
	if (res1)
	{
		printf("%I64d",res1);
		for (LL pw=lim/10ll;pw>=1ll;pw/=10ll) printf("%d",res2/pw%10);
		printf("\n");
	}
	else
		printf("%I64d\n",res2);
	return 0;
}

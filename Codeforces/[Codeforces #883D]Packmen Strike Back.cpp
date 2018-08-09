#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>

const int INF=1e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=1e6;

int n;
char s[MAXN+48];
int cnt;
int L[MAXN+48],R[MAXN+48];

inline void init_interval(int len)
{
}

int main ()
{
	int i;
	n=getint();scanf("%s",s+1);
	for (i=1;i<=n;i++) if (s[i]=='P') cnt++;
	if (cnt==1)
	{
		int cc[2],cur=1,p1,p2,pp;
		for (i=1;i<=n;i++)
		{
			if (s[i]=='.') continue;
			if (s[i]=='*') cc[cur]++;
			if (s[i]=='P') cur^=1,pp=i;
		}
		for (p1=1;s[p1]!='*';p1++) {}
		for (p2=n;s[p2]!='*';p2--) {}
		if (cc[0]<cc[1]) printf("%d %d\n",cc[0],pp-p1); else printf("%d %d\n",cc[1],p2-pp);
		return 0;
	}
	int l=1,r=n-1,mid,ans;
	while (l<=r)
	{
		mid=(l+r)>>1;
		init_interval(mid);
	}
}

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

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='0') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=1e6+48;

char s[MAXN+48];int len;
vector<int> v[MAXN*2];int sz[MAXN*2];

namespace SAM
{
	int tot,nxt[MAXN*2][27],par[MAXN*2],maxn[MAXN*2],root,last;
	inline void init() {tot=1;root=last=1;}
	inline void insert(char ch)
	{
		int p=last,np=++tot;;maxn[np]=maxn[p]+1;sz[np]=1;int w=ch-'a'+1;
		while (p && !nxt[p][w]) nxt[p][w]=np,p=par[p];
		if (!p) {par[np]=root;last=np;return;}
		int q=nxt[p][w];
		if (maxn[q]==maxn[p]+1) {par[np]=q;last=np;return;}
		int nq=++tot;maxn[nq]=maxn[p]+1;
		memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
		par[nq]=par[q];par[np]=nq;par[q]=nq;
		while (p && nxt[p][w]==q) nxt[p][w]=nq,p=par[p];
		last=np;
	}
}

using namespace SAM;

inline void dfs(int cur)
{
	for (register int i=0;i<int(v[cur].size());i++) {dfs(v[cur][i]);sz[cur]+=sz[v[cur][i]];}
}

int main ()
{
	scanf("%s",s+1);len=strlen(s+1);int i;
	init();
	for (i=1;i<=len;i++) insert(s[i]);
	for (i=2;i<=tot;i++) v[par[i]].pb(i);
	dfs(1);
	LL ans=0;
	for (i=2;i<=tot;i++)
		if (sz[i]>1) ans=max(ans,1ll*sz[i]*maxn[i]);
	printf("%lld\n",ans);
	return 0;
}

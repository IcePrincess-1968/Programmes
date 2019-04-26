//I'll always miss you like a darlong.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define uint unsigned int
#define ull unsigned long long
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) ((x) & (-x))
#define rep(i,l,r) for (register int i=int(l);i<=int(r);i++)
#define Rep(i,l,r) for (register int i=int(l);i<int(r);i++)
#define REP(i,r,l) for (register int i=int(r);i>=int(l);i--)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}

const int MAXN=1e5;

char s[MAXN+48];

namespace PAM
{
	int nxt[MAXN+48][27],fail[MAXN+48],h[MAXN+48],len[MAXN+48],dp[MAXN+48],tot,last;
	inline int Create() {++tot;memset(nxt[tot],0,sizeof(nxt[tot]));fail[tot]=len[tot]=h[tot]=dp[tot]=0;return tot;}
	inline void init()
	{
		memset(nxt[0],0,sizeof(nxt[0]));memset(nxt[1],0,sizeof(nxt[1]));
		fail[0]=1;fail[1]=0;len[0]=0;len[1]=-1;h[0]=0;
		tot=last=1;
	}
	inline int getfail(int pos,int x) {while (s[pos-len[x]-1]!=s[pos]) x=fail[x];return x;}
	inline int geth(int pos,int x,int cmp)
	{
		if (cmp==1) return 1;
		if (cmp==2) return fail[x];
		while (s[pos-len[x]-1]!=s[pos] || 2*(len[x]+2)>cmp) x=fail[x];return x;
	}
	inline void extend(int pos)
	{
		int w=s[pos]-'A'+1,fa=getfail(pos,last);
		if (!nxt[fa][w])
		{
			int cur=Create();len[cur]=len[fa]+2;
			int tmp=getfail(pos,fail[fa]);fail[cur]=nxt[tmp][w];
			tmp=geth(pos,h[fa],len[cur]);h[cur]=nxt[tmp][w];
			nxt[fa][w]=cur;
		}
		last=nxt[fa][w];
	}
	inline void build()
	{
		int len=strlen(s+1);init();
		rep(i,1,len) extend(i);
	}
	int head,tail,q[MAXN+48];
	inline int calc_dp()
	{
		dp[0]=1;head=tail=1;q[1]=0;
		int L=strlen(s+1),ans=L;
		while (head<=tail)
		{
			int cur=q[head++];
			if (~len[cur]&1) check_min(ans,dp[cur]+L-len[cur]);
			rep(i,1,26)
				if (nxt[cur][i])
				{
					int to=nxt[cur][i];
					dp[to]=dp[cur]+1;
					if (~len[h[to]]&1) check_min(dp[to],dp[h[to]]+len[to]/2-len[h[to]]+1);
					q[++tail]=to;
				}
		}
		return ans;
	}
}

inline void input() {scanf("%s",s+1);}

inline void Clear()
{
}

inline void solve()
{
	PAM::build();
	printf("%d\n",PAM::calc_dp());
}

int main ()
{
#ifndef ONLINE_JUDGE
	double T=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	int ca;Get(ca);
	while (ca--)
	{
		input();
		Clear();
		solve();
	}
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-T)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}

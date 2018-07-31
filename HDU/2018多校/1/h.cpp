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
#define LOWBIT(x) x & (-x)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
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
int a[MAXN+48];
vector<int> v[MAXN+48];

int inv[MAXN+48],finv[MAXN+48],fac[MAXN+48];
inline void init_inv()
{
	fac[0]=fac[1]=inv[0]=inv[1]=finv[0]=finv[1]=1;
	for (register int i=2;i<=MAXN;i++)
	{
		inv[i]=MOD-((long long)(MOD/i)*inv[MOD%i])%MOD;
		fac[i]=(1ll*fac[i-1]*i)%MOD;
		finv[i]=(1ll*finv[i-1]*inv[i])%MOD;
	}
}

inline int quick_pow(int x,int y)
{
	int res=1;
	while (y)
	{
		if (y&1) res=(1ll*res*x)%MOD,y--;
		x=(1ll*x*x)%MOD;y>>=1;
	}
	return res;
}

inline int C(int x,int y)
{
	int res=fac[x];
	res=(1ll*res*finv[y])%MOD;res=(1ll*res*finv[x-y])%MOD;
}

int pos[MAXN+48];
set<int> s;
set<int>::iterator iter;

namespace SegmentTree
{
	int lson[MAXN*4],rson[MAXN*4],minn[MAXN*4],maxn[MAXN*4];int tot=0;
	inline void clear() {tot=1;lson[tot]=rson[tot]=0;minn[0]=INF;maxn[0]=-INF;}
	inline void init(int cur) {lson[cur]=rson[cur]=0;minn[cur]=INF;maxn[cur]=-INF;}
	inline void insert(int pos)
	{
		int cur=1;int l=0,r=n+1,mid;
		while (l<=r)
		{
			minn[cur]=min(minn[cur],pos);maxn[cur]=max(maxn[cur],pos);
			if (l==r) break;
			mid=(l+r)>>1;
			if (pos<=mid)
			{
				if (!lson[cur]) lson[cur]=++tot,init(tot);
				cur=lson[cur];r=mid;
			}
			else
			{
				if (!rson[cur]) rson[cur]=++tot,init(tot);
				cur=rson[cur];l=mid+1;
			}
		}
	}
	inline int query1(int pos)
	{
		int cur=1,l=0,r=n+1,mid,res=INF;
		while (l<=r)
		{
			if (!cur) break;
			int mid=(l+r)>>1;
			if (l==r) break;
			if (pos<=mid) res=min(res,minn[rson[cur]]),r=mid,cur=lson[cur];
			else cur=rson[cur],l=mid+1;
		}
		return res;
	}
	inline int query2(int pos)
	{
		int cur=1,l=0,r=n+1,mid,res=-INF;
		while (l<=r)
		{
			if (!cur) break;
			if (l==r) break;
			int mid=(l+r)>>1;
			if (pos>=mid+1) res=max(res,maxn[lson[cur]]),l=mid+1,cur=rson[cur];
			else cur=lson[cur],r=mid;
		}
		return res;
	}
}

int main ()
{
	int ca;ca=getint();int i,j,pt;
	init_inv();
	while (ca--)
	{
		n=getint();
		for (i=1;i<=n;i++) a[i]=getint();
		for (i=1;i<=n;i++) v[i].clear();
		for (i=n;i>=1;i--) v[a[i]].pb(i);
		pt=0;
		for (i=1;i<=n;i++)
			for (j=0;j<int(v[i].size());j++)
				a[v[i][j]]=++pt,pos[pt]=v[i][j];
		int num=1;SegmentTree::clear();SegmentTree::insert(0);SegmentTree::insert(n+1);
		for (i=n;i>=1;i--)
		{
			int R=SegmentTree::query1(pos[i])-1;int L=SegmentTree::query2(pos[i])+1;
			num=(1ll*num*C(R-L,R-pos[i]))%MOD;
			SegmentTree::insert(pos[i]);
		}
		int ans=((1ll*num*finv[n])%MOD*(1ll*inv[2]*n)%MOD)%MOD;
		printf("%d\n",ans);
	}
	return 0;
}

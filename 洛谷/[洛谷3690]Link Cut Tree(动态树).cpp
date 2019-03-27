#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define uing unsigned int 
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
// #define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	T res;bool f;char ch;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:-res);
}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
template<typename T> inline T gcd(T x,T y) {return (!y)?x:gcd(y,x%y);}
template<typename T> inline T myabs(T x) {return (x>0)?x:-x;}
template<typename T> inline T add(T x) {if (x>=MOD) x-=MOD;return x;}
template<typename T> inline T sub(T x) {if (x<0) x+=MOD;return x;}
template<typename T> inline void Add(T &x,T y) {x=add(x+y);}
template<typename T> inline void Sub(T &x,T y) {x=sub(x-y);}

const int MAXN=3e5;

int n,q;

namespace LCT
{
	struct node
	{
		int ch[2];
		int xsum,val,father,flip;
	}tree[MAXN*2];int tot;
	inline void pushdown(int cur) {if (tree[cur].flip) tree[tree[cur].ch[0]].flip^=1,tree[tree[cur].ch[1]].flip^=1,swap(tree[cur].ch[0],tree[cur].ch[1]),tree[cur].flip=0;}
	inline void pushup(int cur) {tree[cur].xsum=tree[tree[cur].ch[0]].xsum^tree[tree[cur].ch[1]].xsum^tree[cur].val;}
	inline void Create(int nv) {++tot;tree[tot].ch[0]=tree[tot].ch[1]=tree[tot].father=0;tree[tot].val=nv;pushup(tot);}
	inline bool isroot(int cur) {return tree[tree[cur].father].ch[0]!=cur && tree[tree[cur].father].ch[1]!=cur;}
	inline void rotate(int x)
	{
		int y=tree[x].father,z=tree[y].father;
		pushdown(y);pushdown(x);
		int k=(tree[y].ch[1]==x);
		if (!isroot(y)) tree[z].ch[tree[z].ch[1]==y]=x;
		tree[y].ch[k]=tree[x].ch[k^1];tree[x].ch[k^1]=y;
		tree[tree[y].ch[k]].father=y;tree[y].father=x;tree[x].father=z;
		pushup(y);pushup(x);
	}
	inline void splay(int x)
	{
		pushdown(x);
		while (!isroot(x))
		{
			int y=tree[x].father,z=tree[y].father;
			if (!isroot(y)) ((tree[y].ch[1]==x)^(tree[z].ch[1]==y))?rotate(x):rotate(y);
			rotate(x);
		}
	}
	inline void access(int cur)
	{
		for (register int pre=0;cur;pre=cur,cur=tree[cur].father)
			splay(cur),tree[cur].ch[1]=pre,pushup(cur);
	}
	inline int findroot(int x) {access(x);splay(x);while (tree[x].ch[0]) x=tree[x].ch[0];return x;}
	inline void makeroot(int x) {access(x);splay(x);tree[x].flip^=1;}
	inline void link(int u,int v)
	{
		makeroot(u);if (findroot(v)==u) return;
		tree[u].father=v;
	}
	inline void cut(int u,int v)
	{
		makeroot(u);access(v);splay(v);
		if (tree[v].ch[0]==u) tree[v].ch[0]=0,tree[u].father=0,pushup(v);
	}
	inline void modify(int u,int nv)
	{
		makeroot(u);
		tree[u].val=nv;pushup(u);
	}
	inline int query(int u,int v)
	{
		makeroot(u);access(v);splay(v);
		return tree[v].xsum;
	}
}

int main ()
{
#ifdef LOCAL
	double T=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	Get(n);Get(q);int x,y,op;
	for (register int i=1;i<=n;i++) Get(x),LCT::Create(x);
	while (q--)
	{
		Get(op);Get(x);Get(y);
		if (op==0) printf("%d\n",LCT::query(x,y));
		if (op==1) LCT::link(x,y);
		if (op==2) LCT::cut(x,y);
		if (op==3) LCT::modify(x,y);
	}
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-T)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}

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
const int MOD=998244353;
const int magic=348;
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

const int MAXN=3e5;

int n,q;
vector<Pair> v[MAXN+48];

int depth[MAXN+48],seq[MAXN+48],pos[MAXN+48],fa[MAXN+48],ind=0;
int ST[MAXN+48][21],mpos[MAXN+48][21];int Log[MAXN+48];

inline void dfs(int cur,int father)
{
	fa[cur]=father;int i,y;pos[cur]=++ind;seq[ind]=cur;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i].x;
		if (y!=father) depth[y]=depth[cur]+v[cur][i].y,dfs(y,cur);
	}
	seq[++ind]=fa[cur];
}

inline void construct_ST()
{
	int i,j;
	for (i=1;i<=ind;i++) ST[i][0]=depth[seq[i]],mpos[i][0]=seq[i];
	Log[0]=Log[1]=0;for (i=2;i<=ind;i++) Log[i]=Log[i>>1]+1;
	for (j=1;j<=20;j++)
		for (i=1;i<=ind;i++)
		{
			ST[i][j]=ST[i][j-1];mpos[i][j]=mpos[i][j-1];
			if (i+(1<<(j-1))<=ind && ST[i+(1<<(j-1))][j-1]<ST[i][j])
			{
				ST[i][j]=ST[i+(1<<(j-1))][j-1];
				mpos[i][j]=mpos[i+(1<<(j-1))][j-1];
			}
		}
}

inline int getlca(int u,int v)
{
	u=pos[u];v=pos[v];if (u>v) swap(u,v);
	int k=v-u+1;
	if (ST[u][Log[k]]<ST[v-(1<<Log[k])+1][Log[k]]) return mpos[u][Log[k]]; else return mpos[v-(1<<Log[k])+1][Log[k]];
}

struct node
{
	int left,right;
	int maxdist,u,v;
	inline bool operator < (const node &other) const {return maxdist<other.maxdist;}
}tree[MAXN*4];

namespace SegmentTree
{
	inline void Update(node &cur,int curdist,int x,int y)
	{
		if (cur.maxdist<curdist)
		{
			cur.maxdist=curdist;
			cur.u=x;cur.v=y;
		}
	}
	inline void pushup(node &cur,node &x,node &y,bool type)
	{
		if (type==true)
		{
			Update(cur,x.maxdist,x.u,x.v);
			Update(cur,y.maxdist,y.u,y.v);
		}
		if (x.maxdist>=0 && y.maxdist>=0)
		{
			Update(cur,depth[x.u]+depth[y.u]-2*depth[getlca(x.u,y.u)],x.u,y.u);
			Update(cur,depth[x.u]+depth[y.v]-2*depth[getlca(x.u,y.v)],x.u,y.v);
			Update(cur,depth[x.v]+depth[y.u]-2*depth[getlca(x.v,y.u)],x.v,y.u);
			Update(cur,depth[x.v]+depth[y.v]-2*depth[getlca(x.v,y.v)],x.v,y.v);
		}
	}
	inline void build(int cur,int left,int right)
	{
		tree[cur].left=left;tree[cur].right=right;tree[cur].maxdist=-1;
		if (left!=right)
		{
			int mid=(left+right)>>1;
			build(cur<<1,left,mid);build(cur<<1|1,mid+1,right);
			pushup(tree[cur],tree[cur<<1],tree[cur<<1|1],true);
		}
		else
			tree[cur].maxdist=0,tree[cur].u=tree[cur].v=left;
	}
	inline node query(int cur,int left,int right)
	{
		if (left<=tree[cur].left && tree[cur].right<=right) return tree[cur];
		node res1;node res2;res1.maxdist=res2.maxdist=-INF;node res;res.maxdist=-1;
		int mid=(tree[cur].left+tree[cur].right)>>1;
		if (left<=mid) res1=query(cur<<1,left,right);
		if (mid+1<=right) res2=query(cur<<1|1,left,right);
		pushup(res,res1,res2,true);
		return res;
	}
}

int main ()
{
	int i,x,y,c,l1,r1,l2,r2;n=getint();
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();c=getint();
		v[x].pb(mp(y,c));v[y].pb(mp(x,c));
	}
	dfs(1,-1);construct_ST();
	SegmentTree::build(1,1,n);
	node res1,res2,res;
	q=getint();
	while (q--)
	{
		l1=getint();r1=getint();l2=getint();r2=getint();
		res1=SegmentTree::query(1,l1,r1);res2=SegmentTree::query(1,l2,r2);
		res.maxdist=-1;
		SegmentTree::pushup(res,res1,res2,false);
		printf("%d\n",res.maxdist);
	}
	return 0;


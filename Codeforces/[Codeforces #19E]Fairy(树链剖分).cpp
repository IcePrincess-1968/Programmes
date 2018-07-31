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

int n,e;
Pair edge[10048];
vector<Pair> v[10048];
int ansnum;vector<int> ans;

struct Edge
{
	int x,y;
	int ind;
};vector<Edge> tedge,ntgedge,ntbedge;
int fa[10048],fa_ind[10048];
bool visited[10048];
int num[10048];
vector<int> vv[10048];int tot;

int dep[10048],depth[10048],sz[10048],son[10048],ffa[10048];
int tpos[10048],ind=0,top[10048];
int anc[10048][21];

void dfs(int cur)
{
	visited[cur]=true;
	if (!fa[cur]) num[fa_ind[cur]]=++tot;
	int i,j,to;
	for (i=0;i<int(v[cur].size());i++)
	{
		to=v[cur][i].x;
		if (!visited[to])
		{
			fa[to]=cur;fa_ind[to]=v[cur][i].y;
			tedge.pb(Edge{cur,to,v[cur][i].y});
			num[v[cur][i].y]=++tot;
			anc[to][0]=cur;dep[to]=dep[cur]+1;
			for (j=1;j<=20;j++) anc[to][j]=anc[anc[to][j-1]][j-1];
			dfs(to);
			vv[num[fa_ind[cur]]].pb(num[v[cur][i].y]);
		}
		else
		{
			if (to!=fa[cur] && dep[cur]>dep[to])
			{
				if (!((dep[cur]-dep[to])&1))
					ntbedge.pb(Edge{to,cur,v[cur][i].y});
				else
					ntgedge.pb(Edge{to,cur,v[cur][i].y});
			}
		}
	}
}

void dfs1(int cur,int father)
{
	ffa[cur]=father;sz[cur]=1;son[cur]=0;
	int i,to,max_size=-1;
	for (i=0;i<int(vv[cur].size());i++)
	{
		to=vv[cur][i];depth[to]=depth[cur]+1;
		dfs1(to,cur);
		sz[cur]+=sz[to];
		if (sz[to]>max_size)
		{
			max_size=sz[to];
			son[cur]=to;
		}
	}
}

void dfs2(int cur,int tp)
{
	top[cur]=tp;tpos[cur]=++ind;
	if (son[cur]) dfs2(son[cur],tp);
	int i;
	for (i=0;i<int(vv[cur].size());i++)
		if (vv[cur][i]!=son[cur]) dfs2(vv[cur][i],vv[cur][i]);
}

struct node
{
	int left,right;
	int cnt;
}tree_good[40048],tree_bad[40048];

void build_good(int cur,int left,int right)
{
	tree_good[cur].left=left;tree_good[cur].right=right;tree_good[cur].cnt=0;
	if (left!=right)
	{
		int mid=(left+right)>>1;
		build_good(cur<<1,left,mid);
		build_good(cur<<1|1,mid+1,right);
	}
}

void build_bad(int cur,int left,int right)
{
	tree_bad[cur].left=left;tree_bad[cur].right=right;tree_bad[cur].cnt=0;
	if (left!=right)
	{
		int mid=(left+right)>>1;
		build_bad(cur<<1,left,mid);
		build_bad(cur<<1|1,mid+1,right);
	}
}

void update_good(int cur,int left,int right)
{
	if (left<=tree_good[cur].left && tree_good[cur].right<=right)
	{
		tree_good[cur].cnt++;
		return;
	}
	int mid=(tree_good[cur].left+tree_good[cur].right)>>1;
	if (left<=mid) update_good(cur<<1,left,right);
	if (mid+1<=right) update_good(cur<<1|1,left,right);
}

void update_bad(int cur,int left,int right)
{
	if (left<=tree_bad[cur].left && tree_bad[cur].right<=right)
	{
		tree_bad[cur].cnt++;
		return;
	}
	int mid=(tree_bad[cur].left+tree_bad[cur].right)>>1;
	if (left<=mid) update_bad(cur<<1,left,right);
	if (mid+1<=right) update_bad(cur<<1|1,left,right);
}

int query_good(int cur,int pos)
{
	if (tree_good[cur].left==tree_good[cur].right) return tree_good[cur].cnt;
	int mid=(tree_good[cur].left+tree_good[cur].right)>>1;
	if (pos<=mid)
		return query_good(cur<<1,pos)+tree_good[cur].cnt;
	else
		return query_good(cur<<1|1,pos)+tree_good[cur].cnt;
}

int query_bad(int cur,int pos)
{
	if (tree_bad[cur].left==tree_bad[cur].right) return tree_bad[cur].cnt;
	int mid=(tree_bad[cur].left+tree_bad[cur].right)>>1;
	if (pos<=mid)
		return query_bad(cur<<1,pos)+tree_bad[cur].cnt;
	else
		return query_bad(cur<<1|1,pos)+tree_bad[cur].cnt;
}

void doit_good(int u,int v)
{
	int tp1=top[u],tp2=top[v];
	while (tp1!=tp2)
	{
		if (depth[tp1]<depth[tp2])
		{
			swap(u,v);
			swap(tp1,tp2);
		}
		update_good(1,tpos[tp1],tpos[u]);
		u=ffa[tp1];tp1=top[u];
	}
	if (depth[u]<depth[v]) swap(u,v);
	update_good(1,tpos[v],tpos[u]);
}

void doit_bad(int u,int v)
{
	int tp1=top[u],tp2=top[v];
	while (tp1!=tp2)
	{
		if (depth[tp1]<depth[tp2])
		{
			swap(u,v);
			swap(tp1,tp2);
		}
		update_bad(1,tpos[tp1],tpos[u]);
		u=ffa[tp1];tp1=top[u];
	}
	if (depth[u]<depth[v]) swap(u,v);
	update_bad(1,tpos[v],tpos[u]);
}

int lca(int u,int v)
{
	if (dep[u]<dep[v]) swap(u,v);
	int i;
	for (i=20;i>=0;i--)
		if (dep[anc[u][i]]>=dep[v]) u=anc[u][i];
	if (u==v) return u;
	for (i=20;i>=0;i--)
		if (anc[u][i]!=anc[v][i])
		{
			u=anc[u][i];
			v=anc[v][i];
		}
	return anc[u][0];
}

int getbelow(int u,int v)
{
	int i;
	for (i=20;i>=0;i--)
		if (dep[anc[u][i]]>dep[v]) u=anc[u][i];
	return u;
}

Pair query_node(int u,int v)
{
	int LCA=lca(u,v);
	if (LCA!=u && LCA!=v) return mp(num[fa_ind[u]],num[fa_ind[v]]);
	if (dep[u]<dep[v]) swap(u,v);
	int tmp=getbelow(u,v);
	return mp(num[fa_ind[u]],num[fa_ind[tmp]]);
}

int main ()
{
	int i,j,cur,x,y;int wei;
	n=getint();e=getint();
	for (i=1;i<=e;i++)
	{
		x=getint();y=getint();
		if (i==1) wei=x;
		edge[i]=mp(x,y);
		v[x].pb(mp(y,i));v[y].pb(mp(x,i));
	}
	memset(visited,false,sizeof(visited));
	int all_cnt=0;ansnum=0;
	for (cur=1;cur<=n;cur++)
		if (!visited[cur])
		{
			for (j=1;j<=tot;j++) vv[j].clear();
			tot=0;fa[cur]=fa_ind[cur]=0;dep[cur]=1;
			tedge.clear();ntgedge.clear();ntbedge.clear();
			dfs(cur);
			depth[cur]=1;dfs1(1,0);
			ind=0;dfs2(1,1);
			if (!int(ntbedge.size())) continue;
			all_cnt++;
			if (int(ntbedge.size())==1)
			{
				ansnum++;
				ans.pb(ntbedge[0].ind);
			}
			build_good(1,1,ind);build_bad(1,1,ind);
			for (i=0;i<int(ntgedge.size());i++)
			{
				Pair res=query_node(ntgedge[i].x,ntgedge[i].y);
				doit_good(res.x,res.y);
			}
			for (i=0;i<int(ntbedge.size());i++)
			{
				Pair res=query_node(ntbedge[i].x,ntbedge[i].y);
				doit_bad(res.x,res.y);
			}
			for (i=0;i<int(tedge.size());i++)
			{
				if (dep[tedge[i].x]>dep[tedge[i].y]) swap(tedge[i].x,tedge[i].y);
				if (query_good(1,tpos[num[fa_ind[tedge[i].y]]])==0 && query_bad(1,tpos[num[fa_ind[tedge[i].y]]])==int(ntbedge.size()))
				{
					ansnum++;
					ans.pb(tedge[i].ind);
				}
			}
		}	
	if (all_cnt==0)
	{
		printf("%d\n",e);
		for (i=1;i<=e;i++) printf("%d ",i);
		printf("\n");return 0;
	}
	if (all_cnt>1)
	{
		printf("0\n");
		return 0;
	}
	printf("%d\n",ansnum);
	sort(ans.begin(),ans.end());
	for (i=0;i<int(ans.size());i++)
		printf("%d ",ans[i]);
	printf("\n");
	return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define LL long long

const int MAXN=100;
const int MAXM=1e4;
const int INF=1e9;

int n,m,r;

struct Edge
{
	int x,y,c;
	inline void input() {scanf("%d%d%d",&x,&y,&c);}
}edge[MAXM+48];

namespace zhuliu
{
	int in[MAXN+48],pre[MAXN+48],bel[MAXN+48],visited[MAXN+48],root,tot;
	inline LL solve()
	{
		int tot=n,cirind;LL res=0;
		for (;;)
		{
			for (register int i=1;i<=tot;i++) in[i]=INF;
			for (register int i=1;i<=m;i++)
				if (edge[i].x!=edge[i].y && edge[i].c<in[edge[i].y])
					in[edge[i].y]=edge[i].c,pre[edge[i].y]=edge[i].x;
			for (register int i=1;i<=tot;i++) if (root!=i && in[i]>=INF) return -1;
			in[root]=0;cirind=0;
			memset(bel,0,sizeof(bel));
			memset(visited,0,sizeof(visited));
			for (register int i=1;i<=tot;i++)
			{
				res+=in[i];
				int v=i;while (!bel[v] && visited[v]!=i && v!=root) visited[v]=i,v=pre[v];
				if (v!=root && !bel[v])
				{
					int u=pre[v];++cirind;
					while (u!=v) bel[u]=cirind,u=pre[u];
					bel[u]=cirind;
				}
			}
			if (!cirind) return res;
			for (register int i=1;i<=tot;i++) if (!bel[i]) bel[i]=++cirind;
			for (register int i=1;i<=m;i++)
			{
				int v=edge[i].y;
				edge[i].x=bel[edge[i].x];edge[i].y=bel[edge[i].y];
				if (edge[i].x!=edge[i].y) edge[i].c-=in[v];
			}
			tot=cirind;root=bel[root];
		}
	}
}

int main ()
{
	// freopen ("a.in","r",stdin);
	// freopen ("a.out","w",stdout);
	scanf("%d%d%d",&n,&m,&r);
	for (register int i=1;i<=m;i++) edge[i].input();
	zhuliu::root=r;LL res=zhuliu::solve();
	printf("%lld\n",res);return 0;
}

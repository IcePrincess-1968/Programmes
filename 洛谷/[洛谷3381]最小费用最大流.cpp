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

int n,e,s,t;

int head[200048],nxt[2000548],to[200048],f[200048],w[200048],tot=1;
inline void addedge(int s,int t,int l,int cost)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=l;w[tot]=cost;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;w[tot]=-cost;
}

int prevv[200048],preve[200048];
int h[200048];

priority_queue<Pair> q;int dist[200048];
bool dijkstra()
{
	int i,x,y,dd;
	for (i=1;i<=n;i++) dist[i]=INF;
	dist[s]=0;q.push(mp(0,s));
	while (!q.empty())
	{
		x=q.top().y;dd=-q.top().x;q.pop();
		if (dd>dist[x]) continue;
		for (i=head[x];i;i=nxt[i])
		{
			y=to[i];
			if (f[i] && dist[x]+w[i]+h[x]-h[y]<dist[y])
			{
				dist[y]=dist[x]+w[i]+h[x]-h[y];
				prevv[y]=x;preve[y]=i;
				q.push(mp(-dist[y],y));
			}
		}
	}
	if (dist[t]>=INF) return false; else return true;
}

Pair min_cost_flow()
{
	int i,u,res,minf;
	for (i=1;i<=n;i++) h[i]+=dist[i];
	minf=INF;
	for (u=t;u!=s;u=prevv[u]) minf=min(minf,f[preve[u]]);
	res=minf*h[t];
	for (u=t;u!=s;u=prevv[u])
	{
		f[preve[u]]-=minf;
		f[preve[u]^1]+=minf;
	}
	return mp(minf,res);
}

int main ()
{
	int i,x,y,l,c;
	n=getint();e=getint();s=getint();t=getint();
	for (i=1;i<=e;i++)
	{
		x=getint();y=getint();l=getint();c=getint();
		addedge(x,y,l,c);
	}
	Pair ans=mp(0,0);
	while (dijkstra())
	{
		Pair res=min_cost_flow();
		ans.x+=res.x;ans.y+=res.y;
	}
	printf("%d %d\n",ans.x,ans.y);
	return 0;
}
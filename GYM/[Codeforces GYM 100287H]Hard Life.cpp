#include <bits/stdc++.h>
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

const int MOD=1e9+9;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const LB eps=1e-15;
const LB pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

inline bool islarger(LB x,LB y) {return x-y>eps;}

int n,e;
Pair edge[1048];

int head[1148],cur[1148],to[10048],nxt[10048];LB f[10048];int tot=1,t;
inline void addedge(int s,int t,LB cap)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
}

int q[10048],Head,Tail;int depth[10048];
inline bool bfs()
{
	int i,x,y;
	for (i=0;i<=t;i++) depth[i]=-1;
	depth[0]=0;q[1]=0;Head=Tail=1;
	while (Head<=Tail)
	{
		x=q[Head++];
		for (i=head[x];i;i=nxt[i])
		{
			y=to[i];
			if (depth[y]==-1 && islarger(f[i],0))
			{
				depth[y]=depth[x]+1;
				q[++Tail]=y;
			}
		}
	}
	if (depth[t]==-1) return false; else return true;
}

inline LB dfs(int x,LB maxf)
{
	if (x==t) return maxf;
	int y;LB minf,now,ans=0;
	for (int &i=cur[x];i;i=nxt[i])
	{
		y=to[i];
		if (depth[y]==depth[x]+1 && islarger(f[i],0))
		{
			minf=min(maxf-ans,f[i]);
			now=dfs(y,minf);
			f[i]-=now;f[i^1]+=now;ans+=now;
		}
	}
	if (!islarger(ans,0)) depth[x]=-1;
	return ans;
}

vector<int> anslist;bool visited[1148];
inline void getans(int x)
{
	visited[x]=true;
	if (x>e) anslist.pb(x);
	for (register int i=head[x];i;i=nxt[i])
		if (!visited[to[i]] && islarger(f[i],0)) getans(to[i]);
}

inline bool check(LB mid)
{
	int i;
	for (i=0;i<=t;i++) head[i]=0;tot=1;
	for (i=1;i<=e;i++) addedge(0,i,1);
	for (i=1;i<=n;i++) addedge(e+i,t,mid);
	for (i=1;i<=e;i++) addedge(i,e+edge[i].x,INF),addedge(i,e+edge[i].y,INF);
	LB ans=0;
	while (bfs())
	{
		for (i=0;i<=t;i++) cur[i]=head[i];
		ans+=dfs(0,INF);
	}
	ans=e-ans;
	return islarger(ans,0);
}

int main ()
{
	freopen ("hard.in","r",stdin);
	freopen ("hard.out","w",stdout);
	LB st=clock();
	int i,x,y;n=getint();e=getint();
	for (i=1;i<=e;i++)
	{
		x=getint();y=getint();
		edge[i]=mp(x,y);
	}
	if (!e) {printf("1\n");printf("1\n");return 0;}
	LB l=0,r=e,mid;t=e+n+1;
	while (r-l>eps)
	{
		mid=(l+r)/2;
		if (check(mid)) memset(visited,false,sizeof(visited)),anslist.clear(),getans(0),l=mid; else r=mid;
		if ((clock()-st)/CLOCKS_PER_SEC>1.5) break;
	}
	printf("%d\n",int(anslist.size()));
	sort(anslist.begin(),anslist.end());
	for (i=0;i<int(anslist.size());i++) printf("%d\n",anslist[i]-e);
	return 0;
}

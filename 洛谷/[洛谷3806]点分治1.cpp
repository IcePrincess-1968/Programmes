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
const int INF=1e9;
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

int n,q;
int head[200048],to[200048],nxt[200048],f[200048],tot=1;
inline void addedge(int s,int t,int cap)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
}
int k[100048];
int sz[100048];bool taboo[100048];
bool ans[100048];int depth[100048];
bool exist[100048];

inline void dfs(int cur,int father)
{
	int i,y;sz[cur]=1;
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (y!=father && !taboo[y]) dfs(y,cur),sz[cur]+=sz[y];
	}
}

inline int getroot(int cur,int father,int Sz)
{
	int i,y;
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (y!=father && !taboo[y] && sz[y]>Sz) return getroot(y,cur,Sz);
	}
	return cur;
}

int d[100048],dtot;

inline void Dfs(int cur,int father)
{
	int i,y;
	for (i=1;i<=q;i++) if (k[i]>=depth[cur] && exist[k[i]-depth[cur]]) ans[i]=true;
	d[++dtot]=depth[cur];
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (y!=father && !taboo[y]) depth[y]=depth[cur]+f[i],Dfs(y,cur);
	}
}

int used[100048],utot;

inline void solve(int cur,int Sz)
{
	dfs(1,-1);
	int root=getroot(cur,-1,Sz),i,j,y;
	utot=0;
	for (i=head[root];i;i=nxt[i])
	{
		y=to[i];
		if (!taboo[y])
		{
			depth[y]=f[i];
			dtot=0;Dfs(y,root);
			for (j=1;j<=dtot;j++)
			{
				if (!exist[d[j]]) used[++utot]=d[j];
				exist[d[j]]=true;
			}
		}
	}
	for (i=1;i<=utot;i++) exist[used[i]]=false;
	taboo[root]=true;
	for (i=head[root];i;i=nxt[i])
	{
		y=to[i];
		if (!taboo[y]) solve(y,sz[y]);
	}
}

int main ()
{
	n=getint();q=getint();
	int i,x,y,c;
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();c=getint();
		addedge(x,y,c);
	}
	for (i=1;i<=q;i++) k[i]=getint();
	exist[0]=true;solve(1,n);
	for (i=1;i<=q;i++) if (ans[i] || !k[i]) printf("AYE\n"); else printf("NAY\n");
	return 0;
}

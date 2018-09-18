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

int head[200048],to[200048],nxt[200048],f[200048],tot=1;
inline void addedge(int s,int t,int l)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=l;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
}

queue<int> q;int depth[200048];
bool bfs()
{
	int i,x,y;
	for (i=1;i<=n;i++) depth[i]=-1;
	depth[s]=0;q.push(s);
	while (!q.empty())
	{
		x=q.front();q.pop();
		for (i=head[x];i;i=nxt[i])
		{
			y=to[i];
			if (depth[y]==-1 && f[i])
			{
				depth[y]=depth[x]+1;
				q.push(y);
			}
		}
	}
	if (depth[t]==-1) return false; else return true;
}

int dfs(int x,int maxf)
{
	if (x==t) return maxf;
	int i,y,minf,now,ans=0;
	for (i=head[x];i;i=nxt[i])
	{
		y=to[i];
		if (depth[y]==depth[x]+1 && f[i])
		{
			minf=min(maxf-ans,f[i]);
			now=dfs(y,minf);
			f[i]-=now;
			f[i^1]+=now;
			ans+=now;
		}
	}
	return ans;
}

int main ()
{
	int i,x,y,c;
	n=getint();e=getint();s=getint();t=getint();
	for (i=1;i<=e;i++)
	{
		x=getint();y=getint();c=getint();
		addedge(x,y,c);
	}
	int ans=0;
	while (bfs()) ans+=dfs(s,2e9);
	printf("%d\n",ans);
	return 0;
}
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
#define Pair pair<int,LL>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;
 
const int MOD=998244353;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);
 
inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int head[100048],to[200048],f[200048],nxt[200048],cost[200048],tot=1;
inline void addedge(int s,int t,int cap,int cc)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;cost[tot]=cc;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;cost[tot]=-cc;
}

int n,n1,n2;
int a[1048];

struct node
{
	int val,ind;
}A[1048],B[1048];

inline int calc(int x,int y)
{
	if (x>y) swap(x,y);
	return min(y-x,n-(y-x));
}

int mincost=0;bool visited[1048];int D[1048];
inline int aug(int cur,int maxf)
{
	if (cur==n1+n2+1)
	{
		mincost+=maxf*(-D[0]);
		return maxf;
	}
	if (maxf==0) return 0;
	visited[cur]=true;
	int i,y,minf,now,ans=0;
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (!visited[y] && f[i] && D[cur]+cost[i]-D[y]==0)
		{
			minf=min(maxf-ans,f[i]);
			now=aug(y,minf);
			f[i]-=now;f[i^1]+=now;ans+=now;
		}
		if (ans>=maxf) return ans;
	}
	return ans;
}

inline bool relabel()
{
	int cur,i,y,d=INF;
	for (cur=0;cur<=n1+n2+1;cur++)
		for (i=head[cur];i;i=nxt[i])
		{
			y=to[i];
			if (visited[cur] && !visited[y] && f[i]) d=min(d,D[cur]+cost[i]-D[y]);
		}
	if (d==INF) return false;
	for (cur=0;cur<=n1+n2+1;cur++)
		if (visited[cur]) D[cur]-=d;
	return true;
}

int main ()
{
	int i,j,sum=0;n=getint();
	for (i=1;i<=n;i++) a[i]=getint(),sum+=a[i];
	sum/=n;
	for (i=1;i<=n;i++)
	{
		if (a[i]>sum) A[++n1]=node{a[i],i};
		if (a[i]<sum) B[++n2]=node{a[i],i};
	}
	for (i=1;i<=n1;i++) addedge(0,i,A[i].val-sum,0);
	for (i=1;i<=n2;i++) addedge(n1+i,n1+n2+1,sum-B[i].val,0);
	for (i=1;i<=n1;i++)
		for (j=1;j<=n2;j++)
			addedge(i,n1+j,INF,calc(A[i].ind,B[j].ind));
	do
		do
			memset(visited,false,sizeof(visited));
		while (aug(0,INF));
	while (relabel());
	printf("%d\n",mincost);
	return 0;
}

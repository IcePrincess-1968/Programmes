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
 
const int MOD=100003;
const LL LINF=2e16;
const int INF=1e9;
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

int n,K,A,B,C;
int dist[2000048];
int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
int a[148][148];

int head[2000048],to[1200048],nxt[1200048],f[1200048],tot=1;
inline void addedge(int s,int t,int cap) {to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;}

inline int getind(int x,int y,int k) {return ((x-1)*n+y)*100+k;}

/*
bool inq[2000048];queue<int> q;
inline void spfa()
{
	int i,y,cur;
	memset(inq,false,sizeof(inq));
	for (i=1;i<=2000000;i++) dist[i]=INF;
	dist[getind(1,1,K)]=0;q.push(getind(1,1,K));inq[getind(1,1,K)]=true;
	while (!q.empty())
	{
		cur=q.front();q.pop();inq[cur]=false;
		for (i=head[cur];i;i=nxt[i])
		{
			y=to[i];
			if (dist[cur]+f[i]<dist[y])
			{
				dist[y]=dist[cur]+f[i];
				if (!inq[y]) inq[y]=true,q.push(y);
			}
		}
	}
}
*/		

priority_queue<Pair> q;
inline void dijkstra()
{
	int i,y,cur,dd;
	for (i=1;i<=2000000;i++) dist[i]=INF;
	dist[getind(1,1,K)]=0;q.push(mp(0,getind(1,1,K)));
	while (!q.empty())
	{
		cur=q.top().y;dd=-q.top().x;q.pop();
		if (dd>dist[cur]) continue;
		for (i=head[cur];i;i=nxt[i])
		{
			y=to[i];
			if (dist[cur]+f[i]<dist[y])
			{
				dist[y]=dist[cur]+f[i];
				q.push(mp(-dist[y],y));
			}
		}
	}
}

int main ()
{
	int i,j,cur,to,x,y,c,k,dir,tok;
	n=getint();K=getint();A=getint();B=getint();C=getint();
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			a[i][j]=getint();
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			for (k=1;k<=K;k++)
			{
				cur=getind(i,j,k);
				for (dir=0;dir<4;dir++)
				{
					x=i+dx[dir];y=j+dy[dir];
					if (1<=x && x<=n && 1<=y && y<=n)
					{
						tok=k-1;c=0;
						if (dir==0 || dir==3) c+=B;
						if (a[x][y]) tok=K,c+=A;
						to=getind(x,y,tok);
						addedge(cur,to,c);
						tok=K;c+=C+A;to=getind(x,y,tok);
						addedge(cur,to,c);
					}
				}
			}
	dijkstra();
	//spfa();
	int ans=INF;
	for (k=0;k<=K;k++) ans=min(ans,dist[getind(n,n,k)]);
	printf("%d\n",ans);
	return 0;
}

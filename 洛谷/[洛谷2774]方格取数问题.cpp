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

const int MOD=998244353;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const long double pi=acos(-1);
const int G=3;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,m;
int a[148][148];
inline int getind(int x,int y) {return (x-1)*m+y;}

int head[100048],to[200048],nxt[200048],tot=1;LL f[200048];
inline void addedge(int s,int t,LL cap)
{
    to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
    to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
}

int depth[100048];queue<int> q;
inline bool bfs()
{
    int i,x,y;
    for (i=0;i<=n*m+1;i++) depth[i]=-1;
    depth[0]=0;q.push(0);
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
    if (depth[n*m+1]!=-1) return true; else return false;
}

inline LL dfs(int x,LL maxf)
{
    if (x==n*m+1 || maxf==0) return maxf;
    int i,y;LL minf,now,ans=0ll;
    for (i=head[x];i;i=nxt[i])
    {
        y=to[i];
        if (depth[y]==depth[x]+1 && f[i])
        {
            minf=min(maxf-ans,f[i]);
            now=dfs(y,minf);
            f[i]-=now;f[i^1]+=now;ans+=now;
        }
        if (ans>=maxf) return ans;
    }
    return ans;
}

int dx[]={-1,0,1,0},dy[]={0,1,0,-1};

int main ()
{
    int i,j,k,x,y;
    n=getint();m=getint();
    LL ans=0;
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
        {
            a[i][j]=getint();int Ind=getind(i,j);
            ans+=a[i][j];
            if ((i+j)%2==1)
            {
                addedge(0,Ind,a[i][j]);
                for (k=0;k<4;k++)
                {
                    x=i+dx[k];y=j+dy[k];
                    if (1<=x && x<=n && 1<=y && y<=m) addedge(Ind,getind(x,y),LINF);
                }
            }
            else
                addedge(Ind,n*m+1,a[i][j]);
        }
    while (bfs()) ans-=dfs(0,LINF);
    printf("%lld\n",ans);
    return 0;
}

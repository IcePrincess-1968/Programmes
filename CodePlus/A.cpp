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

bool visited[148][148];
int a[148][148];
Pair to[148][148];
int n,m,sx,sy,ex,ey;
int mve[5][3];

inline Pair go(int x,int y)
{
	if (x<1 || x>n || y<1 || y>m) return mp(-1,-1);
	if (visited[x][y]) return mp(-1,-1);
	if (a[x][y]==0) return mp(x,y);
	if (x==ex && y==ey) return mp(x,y);
	visited[x][y]=true;
	return go(x+mve[a[x][y]][1],y+mve[a[x][y]][2]);
}

bool superf=false;

inline void dfs(int x,int y)
{
	//cout<<x<<' '<<y<<endl;
	x=to[x][y].x;y=to[x][y].y;
	if (x==-1) return;
	if (x==ex && y==ey)
	{
		superf=true;
		return;
	}
	if (visited[x][y]) return;
	visited[x][y]=true;
	for (int i=1;i<=4;i++)
	{
		if (1<=x+mve[i][1] && x+mve[i][1]<=n && 1<=y+mve[i][2] && y+mve[i][2]<=m)
		{
			a[x][y]=i;
			//cout<<x<<' '<<y<<"     ";
			dfs(x+mve[i][1],y+mve[i][2]);
			if (superf) return;
			a[x][y]=0;
		}
	}
	visited[x][y]=false;
}

inline void Init(int x,int y)
{
	cout<<x<<' '<<y<<endl;
	if (x==ex && y==ey) return;
	Init(x+mve[a[x][y]][1],y+mve[a[x][y]][2]);
}

int main ()
{
	freopen ("10.txt","r",stdin);
	freopen ("10.out","w",stdout);
	n=getint();m=getint();sx=getint();sy=getint();ex=getint();ey=getint();
	int i,j;string s;
	mve[4][1]=-1;mve[4][2]=0;
	mve[1][1]=0;mve[1][2]=1;
	mve[2][1]=1;mve[2][2]=0;
	mve[3][1]=0;mve[3][2]=-1;
	for (i=1;i<=n;i++)
	{
		cin>>s;
		for (j=1;j<=m;j++)
		{
			if (s[j-1]=='w') a[i][j]=4;
			if (s[j-1]=='d') a[i][j]=1;
			if (s[j-1]=='s') a[i][j]=2;
			if (s[j-1]=='a') a[i][j]=3;
			if (s[j-1]=='.') a[i][j]=0;
		}
	}
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
		{
			memset(visited,false,sizeof(visited));
			to[i][j]=go(i,j);
		}
	memset(visited,false,sizeof(visited));
	dfs(sx,sy);
	//Init(sx,sy);
	cout<<n<<' '<<m<<' '<<sx<<' '<<sy<<' '<<ex<<' '<<ey<<endl;
	for (i=1;i<=n;i++)
	{
		for (j=1;j<=m;j++)
		{
			if (a[i][j]==4) cout<<'w';
			if (a[i][j]==1) cout<<'d';
			if (a[i][j]==2) cout<<'s';
			if (a[i][j]==3) cout<<'a';
			if (a[i][j]==0) cout<<'.';
		}
		cout<<endl;
	}
	return 0;
}
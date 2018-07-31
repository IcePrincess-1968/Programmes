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
const LB eps=1e-10;
const LB pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,e;
struct Edge
{
	int x,y;
	LL a,b;
	Edge () {}
	inline Edge (int xx,int yy,LL aa,LL bb) {x=xx;y=yy;a=aa;b=bb;}
};
vector<Edge> v[5048];

int vmin[5048],vmax[5048];
LL dmin[5048],dmax[5048];
queue<int> q;bool inqmin[5048],inqmax[5048];

int main ()
{
	int i,x,y,A,B,ca,cur,type;ca=getint();
	while (ca--)
	{
		n=getint();e=getint();
		for (i=1;i<=n;i++) v[i].clear();
		for (i=1;i<=e;i++)
		{
			x=getint();y=getint();A=getint();B=getint();
			v[x].pb(Edge(x,y,A,B));
		}
		for (i=1;i<=n;i++) vmin[i]=vmax[i]=0,inqmin[i]=inqmax[i]=false,dmin[i]=LINF,dmax[i]=-LINF;
		dmin[1]=dmax[1]=0;q.push(1);q.push(1);q.push(1);q.push(2);inqmax[1]=inqmin[1]=true;
		while (!q.empty())
		{
			cur=q.front();q.pop();type=q.front();q.pop();
			if (type==1)
			{
				inqmax[cur]=false;
				vmax[cur]++;
				if (vmax[cur]>n) dmax[cur]=LINF;
				for (i=0;i<int(v[cur].size());i++)
				{
					y=v[cur][i].y;
					if (v[cur][i].a==1)
					{
						if (dmax[cur]==LINF)
						{
							if (dmax[y]!=LINF)
							{
								dmax[y]=LINF;
								if (!inqmax[y]) inqmax[y]=true,q.push(y),q.push(1);
							}
						}
						else
						{
							if (dmax[cur]+v[cur][i].b>dmax[y])
							{
								dmax[y]=dmax[cur]+v[cur][i].b;
								if (!inqmax[y]) inqmax[y]=true,q.push(y),q.push(1);
							}
						}
					}
					else
					{
						if (dmax[cur]==LINF)
						{
							if (dmin[y]!=-LINF)
							{
								dmin[y]=-LINF;
								if (!inqmin[y]) inqmin[y]=true,q.push(y),q.push(2);
							}
						}
						else
						{
							if (-dmax[cur]+v[cur][i].b<dmin[y])
							{
								dmin[y]=-dmax[cur]+v[cur][i].b;
								if (!inqmin[y]) inqmin[y]=true,q.push(y),q.push(2);
							}
						}
					}
				}
			}
			else
			{
				inqmin[cur]=false;vmin[cur]++;
				if (vmin[cur]>n) dmin[cur]=-LINF;
				for (i=0;i<int(v[cur].size());i++)
				{
					y=v[cur][i].y;
					if (v[cur][i].a==1)
					{
						if (dmin[cur]==-LINF)
						{
							if (dmin[y]!=-LINF)
							{
								dmin[y]=-LINF;
								if (!inqmin[y]) inqmin[y]=true,q.push(y),q.push(2);
							}
						}
						else
						{
							if (dmin[cur]+v[cur][i].b<dmin[y])
							{
								dmin[y]=dmin[cur]+v[cur][i].b;
								if (!inqmin[y]) inqmin[y]=true,q.push(y),q.push(2);
							}
						}
					}
					else
					{
						if (dmin[cur]==-LINF)
						{
							if (dmax[y]!=LINF)
							{
								dmax[y]=LINF;
								if (!inqmax[y]) inqmax[y]=true,q.push(y),q.push(1);
							}
						}
						else
						{	
							if (-dmin[cur]+v[cur][i].b>dmax[y])
							{
								dmax[y]=-dmin[cur]+v[cur][i].b;
								if (!inqmax[y]) inqmax[y]=true,q.push(y),q.push(1);
							}
						}
					}
				}
			}
		}
		if (dmax[n]==-LINF)
		{
			printf("No solution\n");
			continue;
		}
		if (dmax[n]==LINF)
		{
			printf("Infinity\n");
			continue;
		}
		printf("%lld\n",dmax[n]);
	}
	return 0;
}

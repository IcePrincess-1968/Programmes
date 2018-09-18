#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>

const int INF=1e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=400;

int n,nl,nr;
int ga[MAXN+48][MAXN+48];
bool visitedx[MAXN+48],visitedy[MAXN+48];int linkx[MAXN+48],linky[MAXN+48];
int wx[MAXN+48],wy[MAXN+48],slack[MAXN+48];

inline bool find(int cur)
{
	visitedx[cur]=true;int t;
	for (register int i=1;i<=n;i++)
		if (!visitedy[i] && (t=wx[cur]+wy[i]-ga[cur][i])<=slack[i])
			if (!t)
			{
				visitedy[i]=true;
				if (!linky[i] || find(linky[i]))
				{
					linky[i]=cur;linkx[cur]=i;
					return true;
				}
			}
			else slack[i]=min(slack[i],t);
	return false;
}

inline void update()
{
	int d=INF;
	for (register int i=1;i<=n;i++) if (!visitedy[i]) d=min(d,slack[i]);
	for (register int i=1;i<=n;i++) if (visitedx[i]) wx[i]-=d;
	for (register int i=1;i<=n;i++) if (visitedy[i]) wy[i]+=d; else slack[i]-=d;
}

inline void KM()
{
	memset(linkx,0,sizeof(linkx));
	memset(linky,0,sizeof(linky));
	for (register int i=1;i<=n;i++) wx[i]=-INF;
	memset(wy,0,sizeof(wy));
	for (register int i=1;i<=n;i++)
		for (register int j=1;j<=n;j++)
			wx[i]=max(wx[i],ga[i][j]);
	for (register int i=1;i<=n;i++)
	{
		for (register int j=1;j<=n;j++) slack[j]=INF;
		for (;;)
		{
			memset(visitedx,false,sizeof(visitedx));
			memset(visitedy,false,sizeof(visitedy));
			if (find(i)) break; else update();
		}
	}
}

int main ()
{
//	freopen ("a.in","r",stdin);
//	freopen ("a.out","w",stdout);
	nl=getint();nr=getint();n=max(nl,nr);int e=getint();int i,j,x,y,c;
	memset(ga,0,sizeof(ga));
	for (i=1;i<=e;i++)
	{
		x=getint();y=getint();c=getint();
		ga[x][y]=max(ga[x][y],c);
	}
	KM();
	LL ans=0;
	for (i=1;i<=n;i++) ans+=ga[i][linkx[i]];
	printf("%lld\n",ans);
	for (i=1;i<=nl;i++)
		if (ga[i][linkx[i]]>0) printf("%d ",linkx[i]); else printf("0 ");
	puts(""); 
	return 0;
}

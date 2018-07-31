#include <bits/stdc++.h>
#include <tr1/unordered_map>
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
#define LOWBIT(x) x & (-x)

const int INF=2e9;
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

const int MAXN=3e5;

int n,m;

struct Hasher
{
	inline LL operator () (const Pair &x) const
	{
		return 1ll*x.x*(n+1)+x.y;
	}
};
unordered_map<Pair,int,Hasher> Mppos;
unordered_map<Pair,int,Hasher> Mpneg;

Pair edge[MAXN+48];
vector<Pair> v[MAXN+48];
bool visited[MAXN+48];
bool vv[MAXN+48];

stack<int> s;
vector<int> ans[MAXN+48];int tot=0;
int d[MAXN+48];
int cc;

int seq[MAXN+48],T;

inline void dfs(int cur)
{
	int i,y,en;s.push(cur);
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i].x;en=v[cur][i].y;
		if (visited[en]) continue;
		visited[en]=true;dfs(y);
	}
	seq[++T]=s.top();s.pop();
}

int order[MAXN+48],ptot=0;
int odd[MAXN+48],otot=0;

inline void Dfs(int cur)
{
	vv[cur]=true;order[++ptot]=cur;int i,y;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i].x;
		if (!vv[y]) Dfs(y);
	}
}

int main ()
{
	//freopen ("a.in","r",stdin);
	int i,j,ca,x,y;
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		memset(d,0,sizeof(d));cc=0;
		for (i=1;i<=tot;i++) ans[i].clear();
		for (i=1;i<=n;i++) v[i].clear();
		for (i=1;i<=m;i++)
		{
			x=getint();y=getint();
			edge[i]=mp(x,y);
			v[x].pb(mp(y,i));v[y].pb(mp(x,i));
			Mppos[mp(x,y)]=i;Mpneg[mp(y,x)]=-i;
			d[x]++;d[y]++;
		}
		memset(visited,false,sizeof(visited));
		memset(vv,false,sizeof(vv));
		tot=0;
		for (i=1;i<=n;i++)
			if (!vv[i])
			{
				ptot=0;Dfs(i);
				if (ptot==1) continue;
				otot=0;for (j=1;j<=ptot;j++) if (d[order[i]]&1) odd[++otot]=order[i];
				for (i=1;i<=otot;i+=2)
					v[odd[i]].pb(mp(odd[i+1],++m)),v[odd[i+1]].pb(mp(odd[i],m));
				T=0;dfs(order[1]);
				memcpy(seq+T+1,seq+1,T*sizeof(int));
				if (!otot)
				{
					++tot;
					for (j=1;j<=T-1;j++)
						if (Mppos[mp(seq[j],seq[j+1])]) ans[tot].pb(Mppos[mp(seq[j],seq[j+1])]); else ans[tot].pb(Mpneg[mp(seq[j],seq[j+1])]);
				}
				else
				{
					for (j=1;Mppos[mp(seq[j],seq[j+1])] || Mpneg[mp(seq[j],seq[j+1])];j++) {}
					j++;while (!Mppos[mp(seq[j],seq[j+1])] && !Mpneg[mp(seq[j],seq[j+1])]) j++;
					bool ff=false;
					for (int k=j;k<=j+T-2;k++)
					{
						if (!Mppos[mp(seq[j],seq[j+1])] && !Mpneg[mp(seq[j],seq[j+1])])
						{
							ff=false;
							continue;
						}
						if (!ff) ++tot;
						ff=true;	
						if (Mppos[mp(seq[j],seq[j+1])]) ans[tot].pb(Mppos[mp(seq[j],seq[j+1])]); else ans[tot].pb(Mpneg[mp(seq[j],seq[j+1])]);
					}
				}
			}
		printf("%d\n",tot); 
		for (i=1;i<=tot;i++)
		{
			printf("%d ",int(ans[i].size()));
			for (int j=0;j<int(ans[i].size());j++)
				printf("%d ",ans[i][j]);
			puts("");
		}
	}
	return 0;
}

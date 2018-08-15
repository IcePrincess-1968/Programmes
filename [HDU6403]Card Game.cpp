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

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

struct fastio
{
    static const int S=1e7;
    char rbuf[S+48],wbuf[S+48];int rpos,wpos,len;
    fastio() {rpos=len=wpos=0;}
    inline char Getchar()
    {
        if (rpos==len) rpos=0,len=fread(rbuf,1,S,stdin);
        if (!len) return EOF;
        return rbuf[rpos++];
    }
    template <class T> inline void Get(T &x)
    {
        char ch;bool f;T res;
        while (!isdigit(ch=Getchar()) && ch!='-') {}
        if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
        while (isdigit(ch=Getchar())) res=res*10+ch-'0';
        x=(f?res:-res);
    }
    inline void getstring(char *s)
    {
        char ch;
        while ((ch=Getchar())<=32) {}
        for (;ch>32;ch=Getchar()) *++s=ch;
        *(s+1)='\0';
    }
    inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
    inline void Writechar(char ch)
    {
        if (wpos==S) flush();
        wbuf[wpos++]=ch;
    }
    template <class T> inline void Print(T x)
    {
        char s[20];int pt=0;
        if (x==0) s[++pt]='0';
        else
        {
            if (x<0) Writechar('-'),x=-x;
            while (x) s[++pt]='0'+x%10,x/=10;
        }
        while (pt) Writechar(s[pt--]);
        Writechar('\n');
    }
    inline void printstring(char *s)
    {
        int pt=1;
        while (s[pt]!='\0') Writechar(s[pt++]);
    }
}io;

const int MAXN=1e5;

struct Edge
{
	int u,v;
	inline void input () {io.Get(u);io.Get(v);}
}edge[MAXN+48];

vector<int> v[MAXN*2+48];

int cnt=0,cid;
bool visited[MAXN*2+48];int depth[MAXN*2+48],fa[MAXN*2+48];

inline int getanother(int id,int cur) {return edge[id].u==cur?edge[id].v:edge[id].u;}

inline void dfs(int cur,int father)
{
	visited[cur]=true;fa[cur]=father;
	for (auto id : v[cur])
	{
		int y=getanother(id,cur);
		if (!visited[y])
		{
			depth[y]=depth[cur]+1;
			dfs(y,cur);
		}
		else if (y!=father)
			cnt++;cid=id;
	}
}

inline void Clear()
{
	for (register int i=1;i<=n*2;i++) v[i].clear();
	memset(visited,false,sizeof(visited));
}

int minn,minnum;

namespace circletree
{
	int cirlist[MAXN*2+48],ctot;
	inline void getcircle()
	{
		int u=edge[cid].u,v=edge[cid].v;
		if (depth[u]<depth[v]) swap(u,v);
		for (;u!=v,u=fa[u]) cirlist[++ctot]=u;
	}
	inline void solve()
	{
		getcircle();
	}
}

namespace tree
{
	inline void solve()
	{
	}
}

int main ()
{
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	int i,ca;io.Get(ca);
	while (ca--)
	{
		io.Get(n);Clear();
		for (i=1;i<=n;i++)
		{
			edge[i].input();
			v[edge[i].u].pb(i);v[edge[i].v].pb(i);
		}
		bool f=true;minn=0;minnum=0;
		for (i=1;i<=n*2;i++)
			if (!visited[i])
			{
				cnt=0;dfs(i,-1);
				if (cnt>1) {f=false;break;}
				if (!cnt) tree::solve(); else circletree::solve();
			}
		if (!f) {io.Print(-1);continue;}
		io.Print(minn);io.Print(minnum);
	}
	io.flush();return 0;
}

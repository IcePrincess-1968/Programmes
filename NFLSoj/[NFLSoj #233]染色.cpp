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
#define LOWBIT(x) x & (-x)
#define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
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
        for (;ch>32;ch=Getchar()) *s++=ch;
        *s='\0';
    }
    inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
    inline void Writechar(char ch)
    {
        if (wpos==S) flush();
        wbuf[wpos++]=ch;
    }
    template <class T> inline void Print(T x,char ch)
    {
        char s[20];int pt=0;
        if (x==0) s[++pt]='0';
        else
        {
            if (x<0) Writechar('-'),x=-x;
            while (x) s[++pt]='0'+x%10,x/=10;
        }
        while (pt) Writechar(s[pt--]);
        Writechar(ch);
    }
    inline void printstring(char *s)
    {
        int pt=1;
        while (s[pt]!='\0') Writechar(s[pt++]);
    }
}io;

template<typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template<typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template<typename T> inline T myabs(T x) {return x>=0?x:-x;}
template<typename T> inline T gcd(T x,T y) {return y==0?x:gcd(y,x%y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int add(int x,int MO) {if (x>=MO) x-=MO;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline int sub(int x,int MO) {if (x<0) x+=MO;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Add(int &x,int y,int MO) {x=add(x+y,MO);}
inline void Sub(int &x,int y) {x=sub(x-y);}
inline void Sub(int &x,int y,int MO) {x=sub(x-y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=1e5;

int n,m,L,R;
vector<int> v[MAXN+48];

int Head[MAXN*20+48],nxt[MAXN*20+48],to[MAXN*20+48],etot=1;
inline void addedge(int s,int t)
{
    to[++etot]=t;nxt[etot]=Head[s];Head[s]=etot;
}

int anc[MAXN+48][21];int depth[MAXN+48];

inline void dfs_anc(int cur,int father)
{
    for (register int i=0;i<int(v[cur].size());i++)
    {
        int y=v[cur][i];
        if (y!=father)
        {
            anc[y][0]=cur;
            for (register int j=1;j<=20;j++) anc[y][j]=anc[anc[y][j-1]][j-1];
            dfs_anc(y,cur);
        }
    }
}

inline void init_dist()
{
    depth[1]=1;dfs_anc(1,-1);
}

inline int getlca(int u,int v)
{
    if (depth[u]<depth[v]) swap(u,v);
    for (register int i=20;i>=0;i--)
        if (depth[anc[u][i]]>=depth[v]) u=anc[u][i];
    if (u==v) return u;
    for (register int i=20;i>=0;i--)
        if (anc[u][i]!=anc[v][i]) u=anc[u][i],v=anc[v][i];
    return anc[u][0];
}

inline int getdist(int x,int y) {return depth[x]+depth[y]-2*depth[getlca(x,y)];}

int id=0;
int sgn[MAXN*20+48],toc[MAXN+48],tod[MAXN*20+48];
namespace BIT
{
    int c[MAXN*20+48];
    int starter[MAXN*3+48],len[MAXN*3+48];int tot;
    inline void Create(int ind,int l)
    {
        starter[ind]=tot+1;len[ind]=l;
        tot+=l;
    }
    inline void update(int ind,int x,int delta)
    {
        x+=starter[ind]-1;
        int N=starter[ind]+len[ind]-1;
        while (x<=N) c[x]+=delta,x+=LOWBIT(x);
    }
    inline int query(int ind,int x)
    {
        int res=0;x+=starter[ind]-1;
        while (x>=starter[ind]) res+=c[x],x^=LOWBIT(x);
        return res;
    }
    inline int calc(int ind,int left,int right) {return query(ind,right)-query(ind,left-1);}
}

int sz[MAXN+48];bool visited[MAXN+48];

inline void init(int cur,int father)
{
    sz[cur]=1;
    for (register int i=0;i<int(v[cur].size());i++)
    {
        int y=v[cur][i];
        if (y!=father && !visited[y]) init(y,cur),sz[cur]+=sz[y];
    }
}

inline int getroot(int cur,int father,int Sz)
{
    cerr<<cur<<"))"<<endl;
    for (register int i=0;i<int(v[cur].size());i++)
    {
        int y=v[cur][i];
        if (y!=father && !visited[y] && sz[y]>Sz/2) return getroot(y,cur,Sz);
    }
    return cur;
}

int q[MAXN+48];int head,tail;
inline void doit(int id,int cur,int Sgn)
{
    sgn[id]=Sgn;
    BIT::Create(id,sz[cur]);
}

inline void dfs(int cur,int father)
{
    init(cur,-1);
    doit(++id,cur,-1);tod[id]=cur;
    if (father!=-1) addedge(id,father);
    int rt=getroot(cur,-1,sz[cur]);
    cerr<<cur<<' '<<rt<<"^^^^^^^"<<endl;
    doit(++id,rt,1);visited[rt]=true;int cid=id;toc[rt]=cid;tod[id]=rt;
    for (register int i=0;i<int(v[rt].size());i++)
    {
        int y=v[rt][i];
        if (!visited[y]) dfs(y,cid);
    }
}

inline int querygo(int cur,int Len)
{
    int res=0,ori=tod[cur];
    for (register int i=cur;Head[i];i=to[Head[i]])
    {
        int rt=tod[i],dis=getdist(ori,rt);
        if (sgn[i]==1) Add(res,BIT::calc(i,Len-dis-1,BIT::len[i])); else Sub(res,BIT::calc(i,Len-dis-1,BIT::len[i]));
    }
    return res;
}

inline void updatego(int cur)
{
    int res=0,ori=tod[cur];
    for (register int i=cur;Head[i];i=to[Head[i]])
    {
        int rt=tod[i],dis=getdist(ori,rt);
        BIT::update(i,dis+1,1);
    }
}

bool vv[MAXN+48];
inline int solve(int Len)
{
    head=tail=1;q[head]=1;
    memset(vv,false,sizeof(vv));
    int res=1;
    while (head<=tail)
    {
        int x=q[head++];vv[x]=true;
        // Add(res,querygo(toc[x]));
        if (Len==1) cerr<<querygo(toc[x],Len)<<"#"<<endl;
        res=1ll*res*(n-querygo(toc[x],Len))%MOD;
        updatego(toc[x]);
        for (register int i=0;i<int(v[x].size());i++)
        {
            int y=v[x][i];
            if (!vv[y]) q[++tail]=y;
        }
    }
    return res;
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(n);io.Get(m);io.Get(L);io.Get(R);
    cerr<<n<<' '<<m<<' '<<L<<' '<<R<<endl;
    int x,y;
    for (register int i=1;i<=n-1;i++)
    {
        io.Get(x);io.Get(y);
        v[x].pb(y);v[y].pb(x);
    }
    cerr<<"!"<<endl;
    init_dist();
    cerr<<"!"<<endl;
    dfs(1,-1);
    cerr<<"!"<<endl;
    cerr<<solve(L)<<"$"<<endl;
    io.Print(sub(solve(L)-solve(R+1)),'\n');
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<fixed<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}
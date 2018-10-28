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

const int MAXN=1000;
const int MAXM=10000;

int n,m,L,s,t;
LL w[MAXM+48];
vector<Pair> v[MAXN+48];
vector<Pair> vv[MAXN+48];
int List[MAXM+48],tot;
bool mark[MAXM+48];

LL dist[MAXN+48];
priority_queue<pair<LL,int> > q;
inline void dijkstra()
{
    for (register int i=1;i<=n;i++) dist[i]=LINF;
    dist[s]=0;q.push(mp(0,s));
    while (!q.empty())
    {
        int x=q.top().y;LL dd=-q.top().x;q.pop();
        if (dd>dist[x]) continue;
        for (register int i=0;i<int(v[x].size());i++)
        {
            int y=v[x][i].x;LL ww=w[v[x][i].y];
            if (dist[x]+ww<dist[y])
            {
                dist[y]=dist[x]+ww;
                q.push(mp(-dist[y],y));
            }
        }
    }
}

int dp[MAXN+48],to[MAXN+48],id[MAXN+48];
inline int solve(int cur)
{
    cerr<<cur<<endl;
    if (dp[cur]!=-1) return dp[cur];
    if (cur==t)
    {
        dp[cur]=0;to[cur]=-1;
        return cur;
    }
    for (register int i=0;i<int(vv[cur].size());i++)
    {
        int y=vv[cur][i].x;
        if (solve(y)+(mark[vv[cur][i].y]?1:0)>dp[cur]) dp[cur]=solve(y)+vv[cur][i].x,to[cur]=y,id[cur]=vv[cur][i].y;
    }
    return dp[cur];
}

inline void doit(int cur,int left)
{
    if (!left) return;
    if (mark[id[cur]]) w[id[cur]]--,left--;
    doit(to[cur],left);
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    int x,y;
    io.Get(n);io.Get(m);io.Get(L);io.Get(s);io.Get(t);
    for (register int i=1;i<=m;i++)
    {
        io.Get(x);io.Get(y);x++;y++;
        v[x].pb(mp(y,i));v[y].pb(mp(x,i));
        io.Get(w[i]);
        if (!w[i]) List[++tot]=i,mark[i]=true;
    }
    LL l=1,r=INF,mid,ans=-1;
    while (l<=r)
    {
        mid=(l+r)>>1;
        for (register int i=1;i<=tot;i++) w[List[i]]=mid;
        dijkstra();
        if (dist[t]>=L) ans=mid,r=mid-1; else l=mid+1;
    }
    if (ans<0) {printf("NO\n");return 0;}
    if (ans==1 && dist[t]>L) {printf("NO\n");return 0;}
    l=0;r=tot-1;
    while (l<=r)
    {
        mid=(l+r)>>1;
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}
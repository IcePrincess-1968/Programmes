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

const int MAXN=2e5;

int n,N;
char s[MAXN+48];int a[MAXN+48],id[MAXN+48];
int ans[MAXN+48];

vector<int> boundary,inner;

namespace allone
{
    inline void solve()
    {
        if (n%4==0)
        {
            printf("Yes\n");
            for (register int i=1,j=1;i<=n*2;i+=4,j+=2) printf("%d %d %d %d ",j,j+1,j,j+1);
        }
        else
            printf("No\n");
    }
}

namespace four
{
    vector<int> free;
    inline void solve()
    {
        int ind=1;
        for (register int i=0;i<int(inner.size());i+=4,ind+=2)
            ans[inner[i]]=ans[inner[i+2]]=ind,ans[inner[i+1]]=ans[inner[i+3]]=ind+1;
        assert(int(boundary.size())%2==0);
        for (register int i=1;i<int(boundary.size())-1;i+=2,ind++)
            ans[boundary[i]]=ans[boundary[i+1]]=ind;
        free.clear();for (register int i=1;i<=n;i++) if (!ans[i]) free.pb(i);
        for (register int i=0;i<int(free.size());i+=2,ind++)
            ans[free[i]]=ans[free[i+1]]=ind;
        printf("Yes\n");
        for (register int i=1;i<=n;i++) printf("%d ",ans[i]);
        puts("");
    }
}

namespace two
{
    inline void solve()
    {
        int nonzero=0,ind=1;
        for (register int i=1;i<=N-1;i++)
            if ((i==1 && a[i]==1) || (a[i]==1 && a[i-1]==0))
                if (a[i+1]==1) nonzero++;
        if (nonzero<=1) {puts("No");return;}
        int pt1,pt2,pt3,last;
        for (register int i=1;i<=N-1;i++)
            if (((i==1 && a[i]==1) || (a[i]==1 && a[i-1]==0)) && a[i+1]==1) {pt1=i;break;}
        for (pt2=pt1+1;;pt2++)
            if ((a[pt2]==1 && a[pt2-1]==0) && a[pt2+1]==1) break;
        ans[id[pt1+1]]=ans[id[pt2+1]]=ind++;
        for (pt3=pt2;a[pt3] && pt3<=N;pt3++);
        ans[id[pt2]]=ans[id[pt3]]=ind++;
        for (register int i=pt1+1;i<pt2;i++)
        {
            if (a[i-1]==0 && a[i]==1) ans[last]=ans[id[i]]=ind++;
            if (a[i-1]==1 && a[i]==0) last=id[i];
        }
        boundary.clear();inner.clear();
        boundary.pb(id[1]);
        for (register int i=2;i<pt1;i++)
    }
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(n);n*=2;N=n-1;io.getstring(s+1);
    a[n]=1;for (register int i=1;i<=n-1;i++) a[i]=(s[i]=='1');
    int pt;for (pt=n;pt>=1 && a[pt]==1;pt--);
    if (!pt) {allone::solve();return 0;}
    for (register int i=pt;i>=1;i--) a[n-pt+i]=a[i];
    for (register int i=1;i<=n-pt;i++) a[i]=1;
    for (register int i=1;i<=n-pt;i++) id[i]=i+pt;for (register int i=n-pt+1,j=1;j<=pt;i++,j++) id[i]=j;
    boundary.clear();inner.clear();
    boundary.pb(id[1]);
    for (register int i=1;i<=N-1;i++)
    {
        if (a[i] && a[i+1]) {inner.pb(id[i+1]);continue;}
        if (a[i] || a[i+1]) {boundary.pb(id[i+1]);continue;}
    }
    boundary.pb(id[n]);
    int cnt=int(inner.size());
    if (cnt&1) {printf("No\n");return 0;}
    if (cnt%4==0) four::solve(); else two::solve();
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}
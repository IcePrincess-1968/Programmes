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
// #define LOCAL true

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

int k,n;
int a[MAXN+48];

struct node
{
    int val,from;
    inline bool operator < (const node &other) const {return val<other.val;}
}b[MAXN+48];

int pre[MAXN+48],pos[MAXN+48];
int dp[101][MAXN+48],maxn[101][MAXN+48],maxpos[101][MAXN+48],from[101][MAXN+48];

int List[MAXN+48],tot=0;
inline void getans(int r,int i)
{
    if (!i) return;
    List[++tot]=i;getans(r-1,from[r][i]);
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    freopen ("funny.in","r",stdin);
    freopen ("funny.out","w",stdout);
    while (scanf("%d%d",&n,&k) && n && k)
    {
        for (register int i=1;i<=n;i++) scanf("%d",a+i),b[i].val=a[i],b[i].from=i;
        sort(b+1,b+n+1);int itot=0;
        for (register int i=1;i<=n;i++)
        {
            if (i==1 || b[i].val!=b[i-1].val) itot++;
            a[b[i].from]=itot;
        }
        for (register int i=1;i<=itot;i++) pos[i]=0;
        for (register int i=1;i<=n;i++) pre[i]=pos[a[i]],pos[a[i]]=i;
        for (register int i=0;i<=k;i++)
            for (register int j=0;j<=n;j++)
                dp[i][j]=-INF,maxn[i][j]=-INF;
        for (register int i=0;i<=n;i++) dp[0][i]=0,from[0][i]=0,maxn[0][i]=1+(pre[i]?maxn[0][pre[i]]:0);
        for (register int r=1;r<=k;r++)
            for (register int i=r;i<=n;i++)
            {
                //ignore current
                if (i!=r) dp[r][i]=dp[r][i-1],from[r][i]=from[r][i-1];
                //choose current
                int curv=1+dp[r-1][i-1],curf=i-1;
                if (pre[i] && curv<maxn[r-1][pre[i]]+1)
                {
                    curv=maxn[r-1][pre[i]]+1;
                    curf=maxpos[r-1][pre[i]];
                }
                maxn[r][i]=curv;maxpos[r][i]=curf;
                if (curv>dp[r][i]) dp[r][i]=curv,from[r][i]=curf;
            }
        printf("%d\n",dp[k][n]);
        tot=0;getans(k,n);reverse(List+1,List+k+1);
        for (register int i=1;i<=k-1;i++) printf("%d ",List[i]);
        printf("\n");
    }
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}
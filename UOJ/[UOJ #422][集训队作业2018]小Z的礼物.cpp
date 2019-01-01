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
#define LOWBIT(x) (x & (-x))
// #define LOCAL true

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

int n,m;
char a[10][300];int Mp[300];
int popcount[1048],cnt[1048];
int dp[2][65][1548][2];

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    scanf("%d%d",&n,&m);
    for (register int i=1;i<=n;i++) scanf("%s",a[i]+1);
    for (register int j=1;j<=m;j++)
    {
        Mp[j]=0;
        for (register int i=1;i<=n;i++)
            if (a[i][j]=='*') Mp[j]|=(1<<(i-1));
    }
    for (register int Mask=1;Mask<=(1<<n)-1;Mask++) popcount[Mask]=popcount[Mask^LOWBIT(Mask)]+1;
    for (register int Mask=0;Mask<=(1<<n)-1;Mask++)
    {
        cnt[Mask]=popcount[Mask]*2;
        for (register int i=1;i<=n-1;i++) if ((Mask&(1<<(i-1))) && (Mask&(1<<i))) cnt[Mask]--;
        if (Mask&1) cnt[Mask]--;
        if (Mask&(1<<(n-1))) cnt[Mask]--;
    }
    int all=n*(m-1)+(n-1)*m,cur=0,nxt=1;
    for (register int Mask=Mp[1];;Mask=(Mask-1)&Mp[1])
    {
        Add(dp[cur][Mask][cnt[Mask]+popcount[Mask]][popcount[Mask]&1],1);
        if (!Mask) break;
    }
    for (register int i=1;i<=m-1;i++)
    {
        for (register int Mask=0;Mask<=(1<<n)-1;Mask++)
            for (register int num=0;num<=i*n*2;num++)
                for (register int op=0;op<=1;op++)
                    if (dp[cur][Mask][num][op])
                    {
                        for (register int toMask=Mp[i+1];;toMask=(toMask-1)&Mp[i+1])
                        {
                            int tonum=num+cnt[toMask]+(popcount[toMask]-popcount[Mask&toMask]);
                            if (i!=m-1) tonum+=popcount[toMask];
                            int toop=(op+popcount[toMask])&1;
                            Add(dp[nxt][toMask][tonum][toop],dp[cur][Mask][num][op]);
                            if (!toMask) break;
                        }
                        dp[cur][Mask][num][op]=0;
                    }
        cur^=1;nxt^=1;
    }
    int ans=0;
    for (register int Mask=0;Mask<=(1<<n)-1;Mask++)
        for (register int num=1;num<=all;num++)
        {
            if (dp[cur][Mask][num][0]) Sub(ans,1ll*dp[cur][Mask][num][0]*all%MOD*quick_pow(num,MOD-2)%MOD);
            if (dp[cur][Mask][num][1]) Add(ans,1ll*dp[cur][Mask][num][1]*all%MOD*quick_pow(num,MOD-2)%MOD);
        }
    printf("%d\n",ans);
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}
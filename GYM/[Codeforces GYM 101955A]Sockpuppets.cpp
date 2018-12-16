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

const int MAXN=24848;

int n,m,inv2;
char s[48];
int dp[MAXN+48][11][21],dp2[11][21];

/*------ Trie begin ------*/
int nxt[MAXN+48][27],type[MAXN+48],tot,root;
inline int Create() {++tot;type[tot]=0;memset(nxt[tot],0,sizeof(nxt[tot]));return tot;}
inline void init() {tot=0;root=Create();}
inline void insert(char s[],int t)
{
    int cur=root,len=strlen(s+1);
    for (register int i=1;i<=len;i++)
    {
        int w=s[i]-'a'+1;
        if (!nxt[cur][w]) nxt[cur][w]=Create();
        cur=nxt[cur][w];
    }
    type[cur]=t;
}
/*------ Trie end ------*/

inline void dfs(int cur)
{
    for (register int i=1;i<=26;i++)
        if (nxt[cur][i]) dfs(nxt[cur][i]);
    memset(dp[cur],0,sizeof(dp[cur]));dp[cur][0][0]=1;
    for (register int i=1;i<=26;i++)
        if (nxt[cur][i])
        {
            for (register int anum=0;anum<=10;anum++)
                for (register int bnum=0;bnum<=20;bnum++)
                    if (dp[cur][anum][bnum])
                        for (register int toanum=0;anum+toanum<=10;toanum++)
                            for (register int tobnum=0;bnum+tobnum<=20;tobnum++)
                                Add(dp2[anum+toanum][bnum+tobnum],1ll*dp[cur][anum][bnum]*dp[nxt[cur][i]][toanum][tobnum]%MOD);
            for (register int anum=0;anum<=10;anum++)
                for (register int bnum=0;bnum<=20;bnum++)
                    dp[cur][anum][bnum]=dp2[anum][bnum],dp2[anum][bnum]=0;
        }
    if (type[cur]==1)
    {
        for (register int anum=0;anum<=10;anum++)
            for (register int bnum=0;bnum<=20;bnum++)
                if (dp[cur][anum][bnum])
                {
                    //up: 0;down: 0;
                    Add(dp2[anum][bnum],dp[cur][anum][bnum]);
                    //up: 1;down: 0;
                    if (anum+1<=10) Add(dp2[anum+1][bnum],dp[cur][anum][bnum]);
                    //up: 2;down 0;
                    if (anum+2<=10) Add(dp2[anum+2][bnum],1ll*dp[cur][anum][bnum]*inv2%MOD);
                    //up: 0;down 1;
                    if (bnum-1>=0) Add(dp2[anum][bnum-1],1ll*dp[cur][anum][bnum]*bnum%MOD);
                    //up: 1;down 1;
                    if (anum+1<=10 && bnum-1>=0) Add(dp2[anum+1][bnum-1],1ll*dp[cur][anum][bnum]*bnum%MOD);
                    //up: 0;down 2;
                    if (bnum-2>=0) Add(dp2[anum][bnum-2],1ll*dp[cur][anum][bnum]*(bnum*(bnum-1)/2)%MOD);
                }
        for (register int anum=0;anum<=10;anum++)
            for (register int bnum=0;bnum<=20;bnum++)
                dp[cur][anum][bnum]=dp2[anum][bnum],dp2[anum][bnum]=0;
    }
    if (type[cur]==2)
    {
        for (register int anum=0;anum<=10;anum++)
            for (register int bnum=0;bnum<=10;bnum++)
                if (dp[cur][anum][bnum])
                {
                    //up: 0;down 0;
                    Add(dp2[anum][bnum],dp[cur][anum][bnum]);
                    //up: 1;down 0;
                    if (bnum+1<=20) Add(dp2[anum][bnum+1],dp[cur][anum][bnum]);
                    //up: 0;down 1;
                    if (anum-1>=0) Add(dp2[anum-1][bnum],1ll*dp[cur][anum][bnum]*anum%MOD);
                }
        for (register int anum=0;anum<=10;anum++)
            for (register int bnum=0;bnum<=20;bnum++)
                dp[cur][anum][bnum]=dp2[anum][bnum],dp2[anum][bnum]=0;
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
    int ca;scanf("%d",&ca);inv2=(MOD+1)>>1;
    for (register int casenum=1;casenum<=ca;casenum++)
    {
        scanf("%d%d",&n,&m);init();
        for (register int i=1;i<=n;i++)
        {
            scanf("%s",s+1);
            insert(s,1);
        }
        for (register int i=1;i<=m;i++)
        {
            scanf("%s",s+1);
            insert(s,2);
        }
        dfs(root);
        printf("Case #%d: %d\n",casenum,dp[root][0][0]);
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}
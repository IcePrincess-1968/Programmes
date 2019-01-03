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

const int MAXN=4e5;

int n;
Pair a[MAXN+48];
int val[MAXN*2+48],tot;

namespace SegmentTree
{
    LL minn[MAXN*8],lazy[MAXN*8];
    inline void pushdown(int cur)
    {
        if (lazy[cur])
        {
            lazy[cur<<1]+=lazy[cur];minn[cur<<1]+=lazy[cur];
            lazy[cur<<1|1]+=lazy[cur];minn[cur<<1|1]+=lazy[cur];
            lazy[cur]=0;
        }
    }
    inline void pushup(int cur) {minn[cur]=min(minn[cur<<1],minn[cur<<1|1]);}
    inline void build(int cur,int l,int r)
    {
        minn[cur]=lazy[cur]=0;
        if (l!=r)
        {
            int mid=(l+r)>>1;
            build(cur<<1,l,mid);build(cur<<1|1,mid+1,r);
        }
    }
    inline void modify(int cur,int left,int right,int delta,int l,int r)
    {
        if (left<=l && r<=right)
        {
            lazy[cur]+=delta;minn[cur]+=delta;
            return;
        }
        int mid=(l+r)>>1;pushdown(cur);
        if (left<=mid) modify(cur<<1,left,right,delta,l,mid);
        if (mid+1<=right) modify(cur<<1|1,left,right,delta,mid+1,r);
        pushup(cur);
    }
    inline LL query(int cur,int left,int right,int l,int r)
    {
        if (left<=l && r<=right) return minn[cur];
        int mid=(l+r)>>1;LL res=LINF;pushdown(cur);
        if (left<=mid) check_min(res,query(cur<<1,left,right,l,mid));
        if (mid+1<=right) check_min(res,query(cur<<1|1,left,right,mid+1,r));
        pushup(cur);return res;
    }
}

struct reg
{
    int l,r,y,delta;
    reg () {}
    inline reg(int _l,int _r,int _y,int _d) {l=_l;r=_r;y=_y;delta=_d;}
    inline bool operator <  (const reg &other) const
    {
        if (y!=other.y) return y<other.y;
        return delta>other.delta;
    }
}ele[MAXN*2+48];int etot;

inline bool check(int x)
{
    tot=etot=0;for (register int i=1;i<=n;i++) val[++tot]=a[i].x-x,val[++tot]=a[i].x+x,val[++tot]=a[i].x+x+1;
    val[++tot]=-x;val[++tot]=x;val[++tot]=x+1;
    sort(val+1,val+tot+1);tot=unique(val+1,val+tot+1)-(val+1);
    for (register int i=1;i<=n;i++)
    {
        int l=lower_bound(val+1,val+tot+1,a[i].x-x)-val,r=lower_bound(val+1,val+tot+1,a[i].x+x)-val;
        ele[++etot]=reg(l,r,a[i].y-x,1);ele[++etot]=reg(l,r,a[i].y+x+1,-1);
    }
    int l=lower_bound(val+1,val+tot+1,-x)-val,r=lower_bound(val+1,val+tot+1,x)-val;
    ele[++etot]=reg(l,r,-x,-100);ele[++etot]=reg(l,r,x+1,100);
    sort(ele+1,ele+etot+1);bool ok=false;SegmentTree::build(1,1,tot);
    /*
    if (x==1)
    for (register int i=1;i<=etot;i++)
        cerr<<ele[i].l<<' '<<ele[i].r<<' '<<ele[i].y<<' '<<ele[i].delta<<endl;
    */
    for (register int i=1;i<=etot;i++)
    {
        if (ele[i].delta==-100) ok=true;
        else if (ele[i].delta==100) break;
        else SegmentTree::modify(1,ele[i].l,ele[i].r,ele[i].delta,1,tot);
        if (i<etot && ele[i].y==ele[i+1].y) continue;
        if (ok && SegmentTree::query(1,l,r,1,tot)==0) return true;
    }
    return false;
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    int ca=0;
    while (scanf("%d",&n) && n!=-1)
    {
        printf("Case %d: ",++ca);
        if (!n) {puts("never");continue;}
        for (register int i=1;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y);
        if (check(1e7)) {puts("never");continue;}
        int l=1,r=1e7,mid,ans;
        while (l<=r)
        {
            mid=(l+r)>>1;
            if (check(mid)) l=mid+1; else ans=mid,r=mid-1;
        }
        printf("%d\n",ans);
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}
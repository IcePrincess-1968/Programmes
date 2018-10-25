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

const int MAXM=3e5;

int n,m;

struct node
{
    int l,r;LL sta,d;
    inline void input() {io.Get(l);io.Get(r);io.Get(d);io.Get(sta);}
}a[MAXM+48];

namespace sgt
{
    int root;
    int lson[MAXM*80+48],rson[MAXM*80+48],sum[MAXM*80+48],tot=0;
    inline int Create()
    {
        ++tot;lson[tot]=rson[tot]=sum[tot]=0;
        return tot;
    }
    inline void pushup(int cur) {sum[cur]=sum[lson[cur]]+sum[rson[cur]];}
    inline void update(int &cur,int pos,int val,int l,int r)
    {
        if (!cur) cur=Create();
        if (l==r) {sum[cur]+=val;return;}
        int mid=(l+r)>>1;
        if (pos<=mid) update(lson[cur],pos,val,l,mid); else update(rson[cur],pos,val,mid+1,r);
        pushup(cur);
    }
    inline int query(int cur,int left,int right,int l,int r)
    {
        if (!cur) return 0;
        if (left<=l && r<=right) return sum[cur];
        int res=0,mid=(l+r)>>1;
        if (left<=mid) res+=query(lson[cur],left,right,l,mid);
        if (mid+1<=right) res+=query(rson[cur],left,right,mid+1,r);
        return res;
    }
}

namespace SegmentTree
{
    int root;
    int lson[MAXM*80+48],rson[MAXM*80+48];LL sta[MAXM*80+48],d[MAXM*80+48];int tot=0;
    inline int Create ()
    {
        ++tot;lson[tot]=rson[tot]=sta[tot]=d[tot]=0;
        return tot;
    }
    inline void update(int &cur,int left,int right,LL st,LL dd,int l,int r)
    {
        if (!cur) cur=Create();
        if (left<=l && r<=right)
        {
            sta[cur]+=(st+1ll*(l-left)*dd);
            d[cur]+=dd;
            return;
        }
        int mid=(l+r)>>1;
        if (left<=mid) update(lson[cur],left,right,st,dd,l,mid);
        if (mid+1<=right) update(rson[cur],left,right,st,dd,mid+1,r);
    }
    inline LL query(int cur,int pos,int l,int r)
    {
        if (!cur) return 0;
        int mid=(l+r)>>1;LL res=sta[cur]+d[cur]*(pos-l);
        if (l==r) return res;
        if (pos<=mid) res+=query(lson[cur],pos,l,mid); else res+=query(rson[cur],pos,mid+1,r);
        return res;
    }
}

namespace LiChaoTree
{
    int root;
    int lson[MAXM*80+48],rson[MAXM*80+48],maxind[MAXM*80+48],tot=0;
    inline int Create()
    {
        ++tot;lson[tot]=rson[tot]=maxind[tot]=0;
        return tot;
    }
    inline LL query_val(int id,int pos)
    {
        if (!id) return -LINF;
        return a[id].sta+1ll*(pos-a[id].l)*a[id].d;
    }
    inline void update(int &cur,int left,int right,int id,int l,int r)
    {
        if (!cur) cur=Create();
        if (l==r)
        {
            if (query_val(id,l)>query_val(maxind[cur],l)) maxind[cur]=id;
            return;
        }
        int mid=(l+r)>>1;
        if (left<=l && r<=right)
        {
            if (!maxind[cur]) {maxind[cur]=id;return;}
            if (a[id].d>a[maxind[cur]].d)
            {
                if (query_val(id,mid)>=query_val(maxind[cur],mid))
                {
                    maxind[cur]=id;
                    update(lson[cur],left,right,id,l,mid);
                }
                else
                    update(rson[cur],left,right,id,mid+1,r);
            }
            else
            {
                if (query_val(id,mid)>=query_val(maxind[cur],mid))
                {
                    maxind[cur]=id;
                    update(rson[cur],left,right,id,mid+1,r);
                }
                else
                    update(lson[cur],left,right,id,l,mid);
            }
            return;
        }
        if (left<=mid) update(lson[cur],left,right,id,l,mid);
        if (mid+1<=right) update(rson[cur],left,right,id,mid+1,r);
    }
    inline LL query(int cur,int pos,int l,int r)
    {
        if (!cur) return -LINF;
        if (l==r) return query_val(maxind[cur],l);
        LL ans=query_val(maxind[cur],pos);
        int mid=(l+r)>>1;
        if (pos<=mid) check_max(ans,query(lson[cur],pos,l,mid)); else check_max(ans,query(rson[cur],pos,mid+1,r));
        return ans;
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
    io.Get(n);io.Get(m);int op;
    for (register int i=1;i<=m;i++)
    {
        io.Get(op);
        if (op<3) a[i].input();
        if (op==1)
        {
            LiChaoTree::update(LiChaoTree::root,a[i].l,a[i].r,i,1,n);
            sgt::update(sgt::root,a[i].l,1,1,n);
            if (a[i].r!=n) sgt::update(sgt::root,a[i].r+1,-1,1,n);
        }
        if (op==2)
            SegmentTree::update(SegmentTree::root,a[i].l,a[i].r,a[i].sta,a[i].d,1,n);
        if (op==3)
        {
            int x;io.Get(x);
            if (!sgt::query(sgt::root,1,x,1,n)) {printf("NA\n");continue;}
            printf("%lld\n",LiChaoTree::query(LiChaoTree::root,x,1,n)+SegmentTree::query(SegmentTree::root,x,1,n));
        }
    }
    // io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}
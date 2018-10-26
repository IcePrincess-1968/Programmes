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

int n,q;

int Root=0;
namespace Treap
{
    struct node
    {
        int left,right,priority;
        LL Set,sta,d,sum,val,sz;
    }tree[MAXN*2+48];int tot=0;
    inline void init() {tot=0;Root=0;}
    inline int Create(int left,int right,int val,int priority)
    {
        ++tot;
        tree[tot].left=left;tree[tot].right=right;tree[tot].val=val;tree[tot].priority=priority;
        tree[tot].sz=1;tree[tot].Set=-1;tree[tot].sta=0;tree[tot].d=0;tree[tot].sum=tree[tot].val;
        return tot;
    }
    inline void Mark_Set(int cur,LL val)
    {
        if (!cur) return;
        tree[cur].sta=0;tree[cur].d=0;tree[cur].Set=val;
        tree[cur].sum=tree[cur].sz*val;
    }
    inline void Mark_seq(int cur,LL sta,LL d)
    {
        if (!cur) return;
        tree[cur].sta+=sta;tree[cur].d+=d;
        tree[cur].sum+=tree[cur].sz*(sta+sta+(tree[cur].sz-1)*d)/2;
    }
    inline void pushdown(int cur)
    {
        if (tree[cur].Set!=-1)
        {
            tree[cur].val=tree[cur].Set;
            Mark_Set(tree[cur].left,tree[cur].Set);
            Mark_Set(tree[cur].right,tree[cur].Set);
            tree[cur].Set=-1;
        }
        if (tree[cur].d)
        {
            LL mid=tree[cur].sta+tree[tree[cur].left].sz*tree[cur].d;
            tree[cur].val+=mid;
            Mark_seq(tree[cur].left,tree[cur].sta,tree[cur].d);
            Mark_seq(tree[cur].right,mid+tree[cur].d,tree[cur].d);
            tree[cur].sta=0;tree[cur].d=0;
        }
    }
    inline void pushup(int cur)
    {
        tree[cur].sz=1+tree[tree[cur].left].sz+tree[tree[cur].right].sz;
        tree[cur].sum=tree[cur].val;
        if (tree[cur].left) tree[cur].sum+=tree[tree[cur].left].sum;
        if (tree[cur].right) tree[cur].sum+=tree[tree[cur].right].sum;
    }
    inline Pair split(int root,int k)
    {
        if (!root) return mp(0,0);
        int leftsz=tree[tree[root].left].sz+1;
        pushdown(root);
        if (k>=leftsz)
        {
            Pair splitted=split(tree[root].right,k-leftsz);
            tree[root].right=splitted.x;pushup(root);
            return mp(root,splitted.y);
        }
        else
        {
            Pair splitted=split(tree[root].left,k);
            tree[root].left=splitted.y;pushup(root);
            return mp(splitted.x,root);
        }
    }
    inline int merge(int root1,int root2)
    {
        if (!root1 || !root2) return root1^root2;
        if (tree[root1].priority<tree[root2].priority)
        {
            pushdown(root1);
            tree[root1].right=merge(tree[root1].right,root2);
            pushup(root1);return root1;
        }
        else
        {
            pushdown(root2);
            tree[root2].left=merge(root1,tree[root2].left);
            pushup(root2);return root2;
        }
    }
    inline void insert(int pos,int val)
    {
        Pair splitted=split(Root,pos-1);
        Root=merge(merge(splitted.x,Create(0,0,val,rand())),splitted.y);
    }
    inline void insert(int val)
    {
        Root=merge(Root,Create(0,0,val,rand()));
    }
    inline void Set(int left,int right,int val)
    {
        Pair splitted=split(Root,left-1),splitted2=split(splitted.y,right-left+1);
        Mark_Set(splitted2.x,val);
        Root=merge(merge(splitted.x,splitted2.x),splitted2.y);
    }
    inline void addseq(int left,int right,int sta,int d)
    {
        Pair splitted=split(Root,left-1),splitted2=split(splitted.y,right-left+1);
        Mark_seq(splitted2.x,sta,d);
        Root=merge(merge(splitted.x,splitted2.x),splitted2.y);
    }
    inline LL query(int left,int right)
    {
        Pair splitted=split(Root,left-1),splitted2=split(splitted.y,right-left+1);
        LL res=tree[splitted2.x].sum;
        Root=merge(merge(splitted.x,splitted2.x),splitted2.y);
        return res;
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
    while (scanf("%d%d",&n,&q)!=EOF)
    {
        Treap::init();
        int op,l,r,x;
        for (register int i=1;i<=n;i++) scanf("%d",&x),Treap::insert(x);
        while (q--)
        {
            scanf("%d",&op);
            if (op==1)
            {
                scanf("%d%d%d",&l,&r,&x);
                Treap::Set(l,r,x);
            }
            if (op==2)
            {
                scanf("%d%d%d",&l,&r,&x);
                Treap::addseq(l,r,x,x);
            }
            if (op==3)
            {
                scanf("%d%d",&l,&x);
                Treap::insert(l,x);
            }
            if (op==4)
            {
                scanf("%d%d",&l,&r);
                printf("%lld\n",Treap::query(l,r));
            }
        }
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}
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

int n,s;
int a[MAXN+48],sum[MAXN+48];
int ans[MAXN+48];

namespace SegmentTree
{
    int mark[MAXN*4];
    inline void build(int cur,int l,int r)
    {
        mark[cur]=-INF;
        if (l!=r)
        {
            int mid=(l+r)>>1;
            build(cur<<1,l,mid);build(cur<<1|1,mid+1,r);
        }
    }
    inline void update(int cur,int left,int right,int l,int r)
    {
        if (left<=l && r<=right) {check_max(mark[cur],right-r+1);return;}
        int mid=(l+r)>>1;
        if (left<=mid) update(cur<<1,left,right,l,mid);
        if (mid+1<=right) update(cur<<1|1,left,right,mid+1,r);
    }
    inline void dfs(int cur,int l,int r)
    {
        if (l==r) {ans[l]=mark[cur];return;}
        int mid=(l+r)>>1,rlen=r-mid;
        check_max(mark[cur<<1],mark[cur]+rlen);
        check_max(mark[cur<<1|1],mark[cur]);
        dfs(cur<<1,l,mid);dfs(cur<<1|1,mid+1,r);
    }
}

inline int query_pre(int x)
{
    if (sum[x]<=s) return x;
    int l=2,r=x,mid,ans;
    while (l<=r)
    {
        mid=(l+r)>>1;
        if (sum[x]-sum[mid-1]<=s) ans=mid,r=mid-1; else l=mid+1;
    }
    return x-ans+1;
}

inline int query_nxt(int x)
{
    if (sum[n]-sum[x-1]<=s) return n-x+1;
    int l=x,r=n-1,mid,ans;
    while (l<=r)
    {
        mid=(l+r)>>1;
        if (sum[mid]-sum[x-1]<=s) ans=mid,l=mid+1; else r=mid-1;
    }
    return ans-x+1;
} 

int main ()
{
    // freopen ("a.in","r",stdin);
    // freopen ("a.out","w",stdout);
    while (scanf("%d%d",&n,&s)!=EOF)
    {
        for (register int i=1;i<=n;i++) scanf("%d",a+i),sum[i]=sum[i-1]+a[i];
        SegmentTree::build(1,1,n);
        for (register int i=1;i<=n-1;i++)
        {
            if (a[i]>s || a[i+1]>s) continue;
            int num1=query_pre(i),num2=query_nxt(i+1);
            check_min(num1,num2);
            SegmentTree::update(1,i-num1+1,i,1,n);
        }
        SegmentTree::dfs(1,1,n);
        for (register int i=1;i<=n;i++) if (ans[i]>0) printf("%d\n",ans[i]*2); else printf("0\n");
    }
    return 0;
}
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

int n;
int a[MAXN+48],nxt[MAXN+48],sufgcd[MAXN+48];
int gt[MAXN+48][21];

inline void init_nxt()
{
	sufgcd[n-1]=a[n-1];
	for (register int i=n-2;i>=1;i--) sufgcd[i]=gcd(sufgcd[i+1],a[i]);
	for (register int i=1;i<=n;i++) gt[i][0]=a[i];
	for (register int j=1;j<=20;j++)
		for (register int i=1;i<=n;i++)
		{
			gt[i][j]=gt[i][j-1];
			if (i+(1<<(j-1))<=n) gt[i][j]=gcd(gt[i][j],gt[i+(1<<(j-1))][j-1]);
		}
	for (register int i=1;i<=n;i++)
	{
		if (gt[i][20]>1) {nxt[i]=n;continue;}
		int cur=-1,u=i;
		for (register int j=20;j>=0;j--)
			if ((cur==-1 && gt[u][j]>1) || (cur!=-1 && gcd(cur,gt[u][j])>1))
			{
				if (cur==-1) cur=gt[u][j]; else cur=gcd(cur,gt[u][j]);
				u+=(1<<j);
			}
		nxt[i]=u-1;
	}
}

int dp[MAXN+48],sum[MAXN+48];
inline void doit_dp(int lim)
{
	for (register int i=lim;i<=n-1;i++)
		if (nxt[i]==n && gcd(sufgcd[i],a[n])==1) nxt[i]=n-1;
	nxt[n]=n;
	memset(sum,0,sizeof(sum));
	sum[n+1]=1;
	for (register int i=n;i>=lim;i--)
	{
		//range: i+1~nxt[i]+1
		dp[i]=sub(sum[i+1]-sum[nxt[i]+2]);
		sum[i]=add(sum[i+1]+dp[i]);
	}
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("b.in","r",stdin);
	freopen ("b.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	io.Get(n);
	for (register int i=1;i<=n;i++) io.Get(a[i]);
	for (register int i=1;i<=n;i++) if (a[i]==1) {printf("0\n");return 0;}
	init_nxt();doit_dp(1);int ans=dp[1];
	for (register int i=1;i<=n-1;i++)
	{
		int tmp=a[n];a[n]=gcd(a[n],a[i]);
		if (a[n]==1) break;
		if (tmp!=a[n]) doit_dp(i+1);
		Add(ans,dp[i+1]);
	}
	if (a[n]>1) Sub(ans,n-1);
	io.Print(ans,'\n');
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}

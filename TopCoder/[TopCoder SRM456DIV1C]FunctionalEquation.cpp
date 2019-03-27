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

const int MAXN=1e4;

LL x[MAXN+48],y[MAXN+48],cost[48][48],dp[1000048];

class FunctionalEquation
{
	public:
		inline LL minAbsSum(int C, int N, int xzero, int xprod, int xadd, int xmod, int yzero, int yprod, int yadd, int ymod)
		{
			x[0]=xzero;y[0]=yzero;
			for (register int i=1;i<N;i++) x[i]=(x[i-1]*xprod+xadd)%xmod,y[i]=(y[i-1]*yprod+yadd)%ymod;
			for (register int i=0;i<C;i++)
				for (register int j=0;j<C;j++)
				{
					int cnt=0;vector<int> cur;cur.clear();
					for (register int k=0;k<N;k++)
						if (x[k]%(2*C)==2*i) cnt++,cur.pb(x[k]-y[k]+j-i);
						else if (x[k]%(2*C)==2*j+1) cnt++,cur.pb(y[k]-x[k]+j-i-C+1);
					if (!cnt) {cost[i][j]=0;continue;}
					sort(cur.begin(),cur.end());
					LL minn=cur[cnt/2]%C;if (minn<0) minn+=C;
					LL delta=minn-cur[cnt/2],sum1=0,sum2=0;
					for (register int k=0;k<cnt;k++) cur[k]+=delta,sum1+=myabs(cur[k]),cur[k]-=C,sum2+=myabs(cur[k]);
					cost[i][j]=min(sum1,sum2);
				}
			for (register int Mask=0;Mask<=(1<<C)-1;Mask++) dp[Mask]=LINF;dp[0]=0;
			for (register int Mask=1;Mask<=(1<<C)-1;Mask++)
			{
				int cnt=__builtin_popcount(Mask);
				for (register int i=0;i<C;i++) if (Mask&(1<<i)) check_min(dp[Mask],dp[Mask^(1<<i)]+cost[cnt-1][i]);
			}
			return dp[(1<<C)-1];
		}
};

#ifdef LOCAL
int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	cerr<<"Running..."<<endl;
#endif
	FunctionalEquation A;
	int C;int N; int xzero; int xprod; int xadd; int xmod; int yzero; int yprod; int yadd; int ymod;
	while (cin>>C>>N>>xzero>>xprod>>xadd>>xmod>>yzero>>yprod>>yadd>>ymod) cout<<A.minAbsSum(C,N,xzero,xprod,xadd,xmod,yzero,yprod,yadd,ymod)<<endl;
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
}
#endif

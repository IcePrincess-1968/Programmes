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

const int MAXN=2e6;

int n;
int a[48],b[48];
int preMask[48];

LL dp[MAXN+48];
int q[MAXN+48],head,tail;
bool inq[MAXN+48];

int main ()
{
	io.Get(n);
	for (register int i=1;i<=n;i++)
	{
		io.Get(a[i]),io.Get(b[i]);
		int x;io.Get(x);preMask[i]=0;
		for (register int j=1;j<=x;j++)
		{
			int y;io.Get(y);
			preMask[i]|=(1<<(y-1));
		}
	}
	int Mask;
	for (Mask=0;Mask<=(1<<n)-1;Mask++) dp[Mask]=-LINF;
	dp[0]=0;head=tail=1;q[1]=0;inq[0]=true;
	while (head<=tail)
	{
		Mask=q[head++];inq[Mask]=false;
		for (register int i=1;i<=n;i++)
			if (!(Mask&(1<<(i-1))) && (preMask[i]&Mask)==preMask[i])
			{
				if (dp[Mask|(1<<(i-1))]<dp[Mask]+1ll*(__builtin_popcount(Mask)+1)*a[i]+b[i])
				{
					dp[Mask|(1<<(i-1))]=dp[Mask]+1ll*(__builtin_popcount(Mask)+1)*a[i]+b[i];
					if (!inq[Mask|(1<<(i-1))])
					{
						inq[Mask|(1<<(i-1))]=true;
						q[++tail]=(Mask|(1<<(i-1)));
					}
				}
			}
	}
	LL ans=-LINF;
	for (Mask=0;Mask<=(1<<n)-1;Mask++) ans=max(ans,dp[Mask]);
	io.Print(ans,'\n');
	io.flush();return 0;
}

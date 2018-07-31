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

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
    bool f;char ch;int res;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

const int MAXN=200;

int P;

inline int add(int x) {if (x>=P) x-=P;return x;}

int mx[MAXN+48];
int dp[MAXN+48][MAXN*10+48];
int c[MAXN+48][MAXN+48];
int n,X;

struct Complex
{
	double r,i;
	Complex() {}
	inline Complex(double curr,double curi)
	{
		r=curr;i=curi;
	}
	inline Complex operator + (Complex x)
	{
		return Complex(r+x.r,i+x.i);
	}
	inline Complex operator - (Complex x)
	{
		return Complex(r-x.r,i-x.i);
	}
	inline Complex operator * (Complex x)
	{
		return Complex(r*x.r-i*x.i,r*x.i+i*x.r);
	}
	inline Complex operator / (double x)
	{
		return Complex(r/x,i/x);
	}
}a[300048],b[300048];

//fl=1表示DFT,fl=-1表示iDFT
void FFT(Complex c[],int len,int fl)
{
	int i,j,k,clen;
	for (i=(len>>1),j=1;j<len;j++)
	{
		if (i<j) swap(c[i],c[j]);
		for (k=(len>>1);i&k;k>>=1) i^=k;
		i^=k;
	}
	for (clen=2;clen<=len;clen<<=1)
	{
		Complex wn=Complex(cos(pi*2.0*fl/clen),sin(pi*2.0*fl/clen));
		for (j=0;j<len;j+=clen)
		{
			Complex w=Complex(1,0);
			for (k=j;k<j+(clen>>1);k++)
			{
				Complex tmp1=c[k],tmp2=c[k+(clen>>1)]*w;
				c[k]=tmp1+tmp2;c[k+(clen>>1)]=tmp1-tmp2;
				w=w*wn;
			}
		}
	}
	if (fl==-1)
		for (i=0;i<len;i++) c[i]=c[i]/len;
}

inline void poly_fft(Complex A[],Complex B[],int N,int M)
{
	int len=1;while (len<=N+M) len<<=1;
	for (register int i=N+1;i<len;i++) A[i]=Complex(0,0);
	for (register int i=M+1;i<len;i++) B[i]=Complex(0,0);
	FFT(A,len,1);FFT(B,len,1);
	for (register int i=0;i<len;i++) A[i]=A[i]*B[i];
	FFT(A,len,-1);
}

int main ()
{
	P=getint();
	c[0][0]=1;int i,j,k,m;
	for (i=1;i<=MAXN;i++)
	{
		c[i][0]=c[i][i]=1;
		for (j=1;j<=i-1;j++)
			c[i][j]=add(c[i-1][j-1]+c[i-1][j]);
	}
	memset(dp,0,sizeof(dp));
	dp[1][1]=1;mx[1]=1;
	for (i=2;i<=MAXN;i++)
	{
		cerr<<i<<endl;
		for (k=1;k<=i;k++)
		{
			int curval=min(k,i+1-k);
			for (j=1;j<=mx[k-1];j++) a[j]=Complex(dp[k-1][j],0);
			for (j=1;j<=mx[i-k];j++) b[j]=Complex(dp[i-k][j],0);
			poly_fft(a,b,mx[k-1],mx[i-k]);
			for (j=1;j<=mx[k-1]+mx[i-k];j++)
			{
				dp[i][j+curval]=add(dp[i][j+curval]+(1ll*c[i-1][k-1]*(((long long)(a[j].r+0.5))%MOD))%MOD);
				if (dp[i][j+curval]) mx[i]=max(mx[i],j+curval);
			}
		}
		/*for (j=i;j<=i*3.7;j++)
			for (k=1;k<=i;k++)	
			{
				int curval=min(k,i+1-k);
				for (m=1;m<=j-curval-1;m++)
					dp[i][j]=add(dp[i][j]+((1ll*c[i-1][k-1]*dp[k-1][m])%MOD*dp[i-k][j-curval-m])%MOD);
			}*/
	}
	while (scanf("%d%d",&n,&X)!=EOF)
		printf("%d\n",dp[n][X]);
	return 0;
}

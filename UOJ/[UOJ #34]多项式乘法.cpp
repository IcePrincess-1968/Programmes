#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=3.1415926535897932384626;

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

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

int n,m;

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

void calc_FFT()
{
	int i,l=1;
	while (l<=n+m) l<<=1;
	FFT(a,l,1);
	FFT(b,l,1);
	for (i=0;i<l;i++) a[i]=a[i]*b[i];
	FFT(a,l,-1);
}

int main ()
{
	int i;
	n=getint();m=getint();++n;++m;
	for (i=0;i<n;i++) a[i]=Complex(getint(),0);
	for (i=0;i<m;i++) b[i]=Complex(getint(),0);
	calc_FFT();
	for (i=0;i<n+m-1;i++) printf("%d ",int(a[i].r+0.5));
	printf("\n");
	return 0;
}

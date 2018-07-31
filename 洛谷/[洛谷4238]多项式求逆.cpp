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

const int MOD=998244353;
const LL LINF=2e16;
const int INF=1e9;
const int magic=348;
const double eps=1e-10;
const double pi=3.14159265;
const int G=3;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

inline LL mod(LL x) {while (x>=MOD) x-=MOD;while (x<0) x+=MOD;return x;}

inline LL quick_pow(LL x,LL y)
{
	x%=MOD;LL res=1;
	while (y)
	{
		if (y&1) res=(res*x)%MOD,y--;
		x=(x*x)%MOD;y>>=1;
	}
	return res;
}

LL wn_pos[300048],wn_neg[300048],invlen[300048];
inline void init_wn()
{
	for (register int clen=2;clen<=262144;clen<<=1)
	{
		wn_pos[clen]=quick_pow(G,(MOD-1)/clen);
		wn_neg[clen]=quick_pow(G,(MOD-1)-(MOD-1)/clen);
		invlen[clen]=quick_pow(clen,MOD-2);
	}
}

LL a[300048],b[300048];int n;

inline void NTT(LL c[],int len,int fl)
{
	int clen,i,j,k;
	for (i=(len>>1),j=1;j<len;j++)
	{
		if (i<j) swap(c[i],c[j]);
		for (k=(len>>1);i&k;k>>=1) i^=k;i^=k;
	}
	for (clen=2;clen<=len;clen<<=1)
	{
		LL wn=(fl==1?wn_pos[clen]:wn_neg[clen]);
		for (j=0;j<len;j+=clen)
		{
			LL w=1;
			for (k=j;k<j+(clen>>1);k++)
			{
				LL tmp1=c[k],tmp2=(c[k+(clen>>1)]*w)%MOD;
				c[k]=mod(tmp1+tmp2);c[k+(clen>>1)]=mod(tmp1-tmp2);
				w=(w*wn)%MOD;
			}
		}
	}
	if (fl==-1)
		for (i=0;i<len;i++) c[i]=(c[i]*invlen[len])%MOD;
}

inline void poly_inv(LL A[],LL B[],int len)
{
	if (len==1) {B[0]=quick_pow(A[0],MOD-2);return;}
	static LL tmp[300048];
	poly_inv(A,B,(len+1)>>1);
	int i,Len=1;while (Len<=len*2) Len<<=1;
	for (i=0;i<len;i++) tmp[i]=A[i];
	for (i=len;i<Len;i++) tmp[i]=0;
	NTT(tmp,Len,1);NTT(B,Len,1);
	for (i=0;i<Len;i++) B[i]=(B[i]*mod(2-(tmp[i]*B[i])%MOD))%MOD;
	NTT(B,Len,-1);
	for (i=len;i<Len;i++) B[i]=0;
}

int main ()
{
	int i;
	init_wn();
	n=getint();for (i=0;i<=n-1;i++) a[i]=getint();
	poly_inv(a,b,n);
	for (i=0;i<=n-1;i++) printf("%lld ",b[i]);
	puts("");return 0;
}

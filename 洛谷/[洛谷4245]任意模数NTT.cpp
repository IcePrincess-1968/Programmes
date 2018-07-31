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

const LL MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
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

LL M[]={998244353,1004535809,469762049};
int P;

inline LL mul(LL x,LL y,LL MO)
{
	x%=MO;LL res=0;
	while (y)
	{
		if (y&1) res=(res+x)%MO,y--;
		x=(x+x)%MO,y>>=1;
	}
	return res;
}

inline LL quick_pow(LL x,LL y,int MO)
{
	x%=MO;LL res=1;
	while (y)
	{
		if (y&1) res=(res*x)%MO,y--;
		x=(x*x)%MO;y>>=1;
	}
	return res;
}

LL res[3][600048];
LL A[600048],B[600048];int len;
LL a[600048],b[600048];
LL wn_pos[600048],wn_neg[600048];
int n,m;

inline void init_wn(int MO)
{
	int clen;
	for (clen=2;clen<=len;clen<<=1)
	{
		wn_pos[clen]=quick_pow(G,(MO-1)/clen,MO);
		wn_neg[clen]=quick_pow(G,(MO-1)-(MO-1)/clen,MO);
	}
}

inline LL mod(LL x,LL MO)
{
	while (x>=MO) x-=MO;
	while (x<0) x+=MO;
	return x;
}

inline void NTT(LL c[],int fl,int MO)
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
		LL wn=(fl==1?wn_pos[clen]:wn_neg[clen]);
		for (j=0;j<len;j+=clen)
		{
			LL w=1;
			for (k=j;k<j+(clen>>1);k++)
			{
				LL tmp1=c[k],tmp2=(c[k+(clen>>1)]*w)%MO;
				c[k]=mod(tmp1+tmp2,MO);c[k+(clen>>1)]=mod(tmp1-tmp2,MO);
				w=(w*wn)%MO;
			}
		}
	}
	if (fl==-1)
	{
		LL inv=quick_pow(len,MO-2,MO);
		for (i=0;i<len;i++) c[i]=(c[i]*inv)%MO;
	}
}

inline void calc_NTT(int ind)
{
	int i;
	for (i=0;i<len;i++) a[i]=A[i],b[i]=B[i];
	init_wn(M[ind]);
	NTT(a,1,M[ind]);NTT(b,1,M[ind]);
	for (i=0;i<len;i++) a[i]=(a[i]*b[i])%M[ind];
	NTT(a,-1,M[ind]);
	for (i=0;i<len;i++) res[ind][i]=a[i];
}

LL inv1,inv2,MM,Inv;
LL m1,m2,m3;
inline LL CRT(LL a1,LL a2,LL a3)
{
	LL A=(mul((a1*m2)%MM,inv1%MM,MM)+mul((a2*m1)%MM,inv2%MM,MM))%MM;
	LL k=((((a3-A)%m3+m3)%m3)*Inv)%m3;
	return (((k%P)*(MM%P))%P+A%P)%P;
}

int main ()
{
	int i;n=getint();m=getint();P=getint();
	for (i=0;i<=n;i++) A[i]=getint(),A[i]%=P;
	for (i=0;i<=m;i++) B[i]=getint(),B[i]%=P;
	len=1;while (len<=n+m) len<<=1;
	calc_NTT(0);calc_NTT(1);calc_NTT(2);
	MM=M[0]*M[1];m1=M[0];m2=M[1],m3=M[2];
	inv1=quick_pow(m2,m1-2,m1);inv2=quick_pow(m1,m2-2,m2);Inv=quick_pow(MM,m3-2,m3);
	for (i=0;i<=n+m;i++) printf("%lld ",CRT(res[0][i],res[1][i],res[2][i]));
	puts("");return 0;
}

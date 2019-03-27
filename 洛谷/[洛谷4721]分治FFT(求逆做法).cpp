#include <bits/stdc++.h>
using namespace std;

const int NTT_MAX=8e5;
const int MOD=998244353;
const int G=3;

template<typename T> inline T add(T x) {if (x>=MOD) x-=MOD;return x;}
template<typename T> inline T sub(T x) {if (x<0) x+=MOD;return x;}

inline int quick_pow(int x,int y)
{
	int res=1;
	while (y)
	{
		if (y&1) res=1ll*res*x%MOD;
		x=1ll*x*x%MOD;y>>=1;
	}
	return res;
}

namespace polynomial
{
	int wn_pos[NTT_MAX+48],wn_neg[NTT_MAX+48];bool isfirst=true;
	inline void poly_init()
	{
		for (register int clen=2;clen<=524288;clen<<=1)
			wn_pos[clen]=quick_pow(G,(MOD-1)/clen),wn_neg[clen]=quick_pow(G,(MOD-1)-(MOD-1)/clen);
	}
	inline void poly_ntt(int c[],int len,int fl)
	{
		if (isfirst) poly_init(),isfirst=false;
		for (register int i=(len>>1),j=1;j<len;j++)
		{
			if (i<j) swap(c[i],c[j]);
			int k;
			for (k=(len>>1);i&k;k>>=1) i^=k;i^=k;
		}
		for (register int clen=2;clen<=len;clen<<=1)
		{
			int wn=(fl==1?wn_pos[clen]:wn_neg[clen]);
			for (register int j=0;j<len;j+=clen)
			{
				int w=1;
				for (register int k=j;k<j+(clen>>1);k++)
				{
					int tmp1=c[k],tmp2=1ll*c[k+(clen>>1)]*w%MOD;
					c[k]=add(tmp1+tmp2);c[k+(clen>>1)]=sub(tmp1-tmp2);
					w=1ll*w*wn%MOD;
				}
			}
		}
		if (fl==-1)
		{
			int ilen=quick_pow(len,MOD-2);
			for (register int i=0;i<len;i++) c[i]=1ll*c[i]*ilen%MOD;
		}
	}
	inline void poly_inv(int A[],int B[],int N)
	{
		B[0]=quick_pow(A[0],MOD-2);int tmp[NTT_MAX+48];
		for (register int clen=2;(clen>>1)<N;clen<<=1)
		{
			int Len=min(N,clen);
			memcpy(tmp,A,Len<<2);memset(tmp+Len,0,((clen<<1)-Len)<<2);
			memset(B+(clen>>1),0,((clen<<1)-(clen>>1))<<2);
			poly_ntt(tmp,clen<<1,1);poly_ntt(B,clen<<1,1);
			for (register int i=0;i<(clen<<1);i++) B[i]=1ll*B[i]*sub(2-1ll*tmp[i]*B[i]%MOD)%MOD;
			poly_ntt(B,clen<<1,-1);
		}
	}
}

int n,f[NTT_MAX+48],g[NTT_MAX+48];

int main ()
{
	scanf("%d",&n);for (register int i=1;i<=n-1;i++) scanf("%d",g+i);
	g[0]=1;for (register int i=1;i<=n-1;i++) g[i]=sub(-g[i]);
	polynomial::poly_inv(g,f,n);
	for (register int i=0;i<n;i++) printf("%d ",f[i]);puts("");
	return 0;
}

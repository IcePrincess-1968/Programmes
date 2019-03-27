#include <bits/stdc++.h>
using namespace std;

const int NTT_MAX=8e5;
const int MOD=998244353;
const int G=3;

template<typename T> inline T add(T x) {if (x>=MOD) x-=MOD;return x;}
template<typename T> inline T sub(T x) {if (x<0) x+=MOD;return x;}
template<typename T> inline void Add(T &x,T y) {x=add(x+y);}
template<typename T> inline void Sub(T &x,T y) {x=sub(x-y);}

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
			int k;for (k=(len>>1);i&k;k>>=1) i^=k;i^=k;
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
	inline void poly_mul(int A[],int B[],int N,int M)
	{
		int len=1;while (len<=N+M) len<<=1;
		memset(A+N,0,(len-N)<<2);
		memset(B+M,0,(len-M)<<2);
		poly_ntt(A,len,1);poly_ntt(B,len,1);
		for (register int i=0;i<len;i++) A[i]=1ll*A[i]*B[i]%MOD;
		poly_ntt(A,len,-1);
	}
	inline void solve(int f[],int g[],int l,int r)
	{
		if (l==r) {if (l==0) f[l]=1;return;}
		int mid=(l+r)>>1;solve(f,g,l,mid);
		static int a[NTT_MAX+48],b[NTT_MAX+48];
		for (register int i=l;i<=mid;i++) a[i-l]=f[i];
		for (register int i=0;i<=r-l;i++) b[i]=g[i];
		int N=mid-l+1,M=r-l+1;
		poly_mul(a,b,N,M);
		for (register int i=mid+1;i<=r;i++) Add(f[i],a[i-l]);
		solve(f,g,mid+1,r);
	}
}

int n;
int f[NTT_MAX+48],g[NTT_MAX+48];

int main ()
{
	scanf("%d",&n);for (register int i=1;i<=n-1;i++) scanf("%d",g+i);
	polynomial::solve(f,g,0,n-1);
	for (register int i=0;i<n;i++) printf("%d ",f[i]);puts("");
	return 0;
}

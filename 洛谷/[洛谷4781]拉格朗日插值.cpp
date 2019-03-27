#include <bits/stdc++.h>
using namespace std;

const int MOD=998244353;
const int MAXN=2000;

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

int n,k;
int X[MAXN+48],Y[MAXN+48];

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

inline int Lagrange(int X[],int Y[],int k)
{
	int res=0;
	for (register int i=1;i<=n;i++)
	{
		int up=1,down=1;
		for (register int j=1;j<=n;j++)
			if (i!=j) up=1ll*up*sub(k-X[j])%MOD,down=1ll*down*sub(X[i]-X[j])%MOD;
		Add(res,1ll*up*quick_pow(down,MOD-2)%MOD*Y[i]%MOD);
	}
	return res;
}

int main ()
{
	scanf("%d%d",&n,&k);k%=MOD;
	for (register int i=1;i<=n;i++) scanf("%d%d",X+i,Y+i);
	printf("%d\n",Lagrange(X,Y,k));
	return 0;
}

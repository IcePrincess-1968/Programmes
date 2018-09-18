#include <bits/stdc++.h>
#define LL long long
#define LB long double
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=998244353;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int a[10],b[10],p[10];
int sign[10];

inline int calc_swap()
{
	int res=0,i,j;
	for (i=1;i<=3;i++)
		for (j=i+1;j<=4;j++)
			if (p[i]>p[j]) res++;
	return res;
}

inline int Calc(int x,int y,int ss)
{
	if (ss==1) return x+y;
	if (ss==2) return x-y;
	if (ss==3) return x*y;
	if (ss==4)
	{
		if (y==0) return -INF;
		if (x%y==0) return x/y; else return -INF;
	}
}

inline int query_type()
{
	int res=0;
	if (sign[1]>=3) res+=4;
	if (sign[2]>=3) res+=2;
	if (sign[3]>=3) res+=1;
	return res;
}

inline int calc(int type)
{
	if (type==6)
	{
		int res1=Calc(b[1],b[2],sign[1]);	
		if (res1==-INF) return -1;
		int res2=Calc(b[3],b[4],sign[3]);
		if (res2==-INF) return -1;
		int res=Calc(res1,res2,sign[2]);
		if (res==-INF) return -1;
		return res;
	}
	if (type==5)
	{
		int res1=Calc(b[3],b[4],sign[3]);
		if (res1==-INF) return -1;
		if (sign[1]<=2 && sign[2]>=3)
		{
			int res2=Calc(b[2],res1,sign[2]);
			if (res2==-INF) return -1;
			res2=Calc(b[1],res2,sign[1]);
			if (res2==-INF) return -1;
			return res2;
		}
		else
		{
			int res2=Calc(b[1],b[2],sign[1]);
			if (res2==-INF) return -1;
			res2=Calc(res2,res1,sign[2]);
			if (res2==-INF) return -1;
			return res2;
		}
	}
	if (type==4)
	{
		if (sign[2]<=2 && sign[3]>=3)
		{
			int res1=Calc(b[3],b[4],sign[3]);
			if (res1==-INF) return -1;
			res1=Calc(b[2],res1,sign[2]);
			if (res1==-INF) return -1;
			res1=Calc(b[1],res1,sign[1]);
			if (res1==-INF) return -1;
			return res1;
		}
		else
		{
			int res1=Calc(b[2],b[3],sign[2]);
			if (res1==-INF) return -1;
			res1=Calc(res1,b[4],sign[3]);
			if (res1==-INF) return -1;
			res1=Calc(b[1],res1,sign[1]);
			if (res1==-INF) return -1;
			return res1;
		}
	}
	if (type==3)
	{
		int res=Calc(b[2],b[3],sign[2]);
		if (res==-INF) return -1;
		if (sign[1]<=2 && sign[3]>=3)
		{
			res=Calc(res,b[4],sign[3]);
			if (res==-INF) return -1;
			res=Calc(b[1],res,sign[1]);
			if (res==-INF) return -1;
			return res;
		}
		else
		{
			res=Calc(b[1],res,sign[1]);
			if (res==-INF) return -1;
			res=Calc(res,b[4],sign[3]);
			if (res==-INF) return -1;
			return res;
		}
	}
	if (type==2)
	{
		if (sign[1]<=2 && sign[2]>=3)
		{
			int res=Calc(b[2],b[3],sign[2]);
			if (res==-INF) return -1;
			res=Calc(b[1],res,sign[1]);
			if (res==-INF) return -1;
			res=Calc(res,b[4],sign[3]);
			if (res==-INF) return -1;
			return res;
		}
		else
		{
			int res=Calc(b[1],b[2],sign[1]);
			if (res==-INF) return -1;
			res=Calc(res,b[3],sign[2]);
			if (res==-INF) return -1;
			res=Calc(res,b[4],sign[3]);
			if (res==-INF) return -1;
			return res;
		}
	}
	if (type==1)
	{
		int res=Calc(b[1],b[2],sign[1]);
		if (res==-INF) return -1;
		if (sign[2]<=2 && sign[3]>=3)
		{
			int res1=Calc(b[3],b[4],sign[3]);
			if (res1==-INF) return -1;
			res=Calc(res,res1,sign[2]);
			if (res==-INF) return -1;
			return res;
		}
		else
		{
			res=Calc(res,b[3],sign[2]);
			if (res==-INF) return -1;
			res=Calc(res,b[4],sign[3]);
			if (res==-INF) return -1;
			return res;
		}
	}
	int tt=query_type();
	if (tt==0 || tt==4 || tt==6 || tt==7)
	{
		int res=Calc(b[1],b[2],sign[1]);
		if (res==-INF) return -1;
		res=Calc(res,b[3],sign[2]);
		if (res==-INF) return -1;
		res=Calc(res,b[4],sign[3]);
		if (res==-INF) return -1;
		return res;
	}
	if (tt==1 || tt==5)
	{
		int res1=Calc(b[1],b[2],sign[1]);
		if (res1==-INF) return -1;
		int res2=Calc(b[3],b[4],sign[3]);
		if (res2==-INF) return -1;
		res1=Calc(res1,res2,sign[2]);
		if (res1==-INF) return -1;
		return res1;
	}
	int res=Calc(b[2],b[3],sign[2]);
	if (res==-INF) return -1;
	if (tt==2)
	{
		res=Calc(b[1],res,sign[1]);
		if (res==-INF) return -1;
		res=Calc(res,b[4],sign[3]);
		if (res==-INF) return -1;
		return res;
	}
	else
	{
		res=Calc(res,b[4],sign[3]);
		if (res==-INF) return -1;
		res=Calc(b[1],res,sign[1]);
		if (res==-INF) return -1;
		return res;
	}
}

int main ()
{
	int i,j,k,pp;
	for (i=1;i<=4;i++) a[i]=getint();
	for (i=1;i<=4;i++) p[i]=i;
	int ans=INF,curans;
	do
	{
		curans=calc_swap()*2;
		for (i=1;i<=4;i++) b[i]=a[p[i]];
		for (i=1;i<=4;i++)
			for (j=1;j<=4;j++)
				for (k=1;k<=4;k++)
				{
					sign[1]=i;sign[2]=j;sign[3]=k;
					for (pp=0;pp<=6;pp++)
						if (calc(pp)==24)
						{
							if (pp==0) ans=min(ans,curans);
							else if (pp==6) ans=min(ans,curans+2);
							else ans=min(ans,curans+1);
						}
				}
	}
	while (next_permutation(p+1,p+5));
	if (ans>=INF) printf("impossible\n"); else printf("%d\n",ans);
	return 0;
}

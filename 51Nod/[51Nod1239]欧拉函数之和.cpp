#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <map>
#include <stack>
#include <set>
#include <vector>
#include <queue>
#include <deque>
#include <sstream>
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LL long long
#define Pair pair<int,int>
#define LOWBIT(x) x & (-x)
using namespace std;

const LL MOD=1e9+7;
const LL INF=2e9;
const LL magic=348;
const LL LINF=2e16;
const double eps=1e-10;
const LL lim=4650000;
const LL mo=2333333;

inline LL getLL()
{
	char ch;
	while ((ch=getchar())<'0' || ch>'9') {}
	LL res=ch-'0';
	while ((ch=getchar())>='0' && ch<='9') res=res*10+ch-'0';
	return res;
}

inline LL mod(LL x)
{
	x%=MOD;
	while (x<0) x+=MOD;
	return x;
}

LL n;
LL phi[lim+48];
LL Phi[lim+48];
int prime[lim+48],tot=0;
bool isprime[lim+48];
int head[mo+48],nxt[mo+48];LL to[mo+48],f[mo+48],tt;

void init_phi()
{
	phi[1]=1;
	LL i,j;
	memset(isprime,true,sizeof(isprime));
	for (i=2;i<=lim;i++)
	{
		if (isprime[i])
		{
			prime[++tot]=i;
			phi[i]=i-1;
		}
		for (j=1;j<=tot && prime[j]*i<=lim;j++)
		{
			isprime[i*prime[j]]=false;
			if (i%prime[j]==0)
			{
				phi[i*prime[j]]=mod(phi[i]*prime[j]);
				break;
			}
			else
			{
				phi[i*prime[j]]=mod(phi[i]*(prime[j]-1));
			}
		}
	}
	for (i=2;i<=lim;i++) phi[i]=mod(phi[i]+phi[i-1]);
}

LL cnt=0;

inline void add(LL x,LL y,LL val)
{
	to[++tt]=y;nxt[tt]=head[x];head[x]=tt;f[tt]=val;
}

LL calc(LL cur)
{
	LL i,j,num,pre=1;
	if (cur<=lim) return phi[cur];
	num=cur%mo;
	for (i=head[num];i;i=nxt[i]) if (to[i]==cur) return f[i];
	LL res=mod(mod((1+cur))*mod(cur)/2);
	for (i=cur/2;i!=0;i=cur/(cur/i+1))
	{
		cnt++;
		num=mod((cur/i)-pre);
		res=mod(res-mod((LL)num*calc(i)));
		pre=cur/i;
	}
	add(cur%mo,cur,res);
	return mod(res);
}

int main ()
{
	LL i;
	n=getLL();
	init_phi(); 
	cout<<calc(n)<<endl;
	return 0;
}

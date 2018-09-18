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

LL l,r;

LL mu[lim+48];
bool isprime[lim+48];int prime[lim+48],tot=0;

void init_mu()
{
	LL i,j;
	memset(isprime,true,sizeof(isprime));
	for (i=2;i<=lim;i++)
	{
		if (isprime[i])
		{
			prime[++tot]=i;
			mu[i]=-1;
		}
		for (j=1;j<=tot && prime[j]*i<=lim;j++)
		{
			isprime[i*prime[j]]=false;
			if (i%prime[j]==0)
			{
				mu[i*prime[j]]=0;
				break;
			}
			else
			{
				mu[i*prime[j]]=-mu[i];
			}
		}
	}
	mu[1]=1;
	for (i=2;i<=lim;i++) mu[i]=mu[i]+mu[i-1];
}

LL head[mo+48],to[mo+48],nxt[mo+48],f[mo+48],tt;
inline void addedge(LL num,LL type,LL val)
{
	to[++tt]=num;nxt[tt]=head[type];head[type]=tt;f[tt]=val;
}

LL calc(LL cur)
{
	LL k=cur%mo;
	//if (cur==1) return 1;
	if (cur<=lim) return mu[cur];
	LL i,num,res=1,pre=1;
	for (i=head[k];i;i=nxt[i]) if (to[i]==cur) return f[i];
	for (i=cur/2;i;i=cur/(cur/i+1))
	{
		num=cur/i-pre;
		res=res-num*calc(i);
		pre=cur/i;
	}
	addedge(cur,k,res);
	return res;
}

int main ()
{
	l=getLL();r=getLL();
	init_mu();
	LL ans1=calc(l-1),ans2=calc(r);
	cout<<ans2-ans1<<endl;
	return 0;
}

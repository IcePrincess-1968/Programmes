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
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const long double pi=acos(-1);
const int G=3;

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

char ss[11000048],s[25000048];int len,pt;
int maxright,pos,ans=0,RL[25000048];

inline void solve()
{
	int i;maxright=pos=0;
	for (i=1;i<=len;i++)
	{
		if (i<maxright) RL[i]=min(maxright-i,RL[2*pos-i]); else RL[i]=1;
		while (i-RL[i]>=1 && i+RL[i]<=len && s[i+RL[i]]==s[i-RL[i]]) RL[i]++;
		ans=max(ans,RL[i]-1);
		if (i+RL[i]>maxright) maxright=i+RL[i],pos=i;
	}
}

int main ()
{
	scanf("%s",ss+1);len=strlen(ss+1);int i;
	for (i=1;i<=len;i++) s[++pt]='$',s[++pt]=ss[i];
	s[++pt]='$';len=pt;
	solve();printf("%d\n",ans);
	return 0;
}

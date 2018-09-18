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
const LB eps=1e-10;
const LB pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int cnt1[48],cnt2[48],cnt[48];
char s1[100048],s2[100048];int len1,len2;

LL fac[100048],finv[100048],inv[100048];
inline void init()
{
	fac[0]=fac[1]=inv[0]=inv[1]=finv[0]=finv[1]=1;
	int i;
	for (i=2;i<=100000;i++)
	{
		fac[i]=(fac[i-1]*i)%MOD;
		inv[i]=MOD-((long long)(MOD/i)*inv[MOD%i])%MOD;
		finv[i]=(finv[i-1]*inv[i])%MOD;
	}
}

inline LL C(int x,int y)
{
	if (x<y) return 0;
	LL res=fac[x];
	res=(res*finv[y])%MOD;
	res=(res*finv[x-y])%MOD;
	return res;
}

int main ()
{
	int ca,i;ca=getint();
	init();
	while (ca--)
	{
		scanf("%s",s1+1);len1=strlen(s1+1);
		scanf("%s",s2+1);len2=strlen(s2+1);
		memset(cnt1,0,sizeof(cnt1));memset(cnt2,0,sizeof(cnt2));
		for (i=1;i<=len1;i++) cnt1[s1[i]-'a'+1]++;
		for (i=1;i<=len2;i++) cnt2[s2[i]-'a'+1]++;
		for (i=1;i<=26;i++) cnt[i]=cnt1[i]-cnt2[i];
		bool f=true;
		for (i=1;i<=26;i++)
			if (cnt[i]<0) {f=false;break;}
		if (!f) {printf("0\n");continue;}
		LL ans=1;LL Le=len1-len2;
		for (i=1;i<=26;i++)
		{
			ans=(ans*C(Le,cnt[i]))%MOD;
			Le-=cnt[i];
		}
		ans=(ans*(len1-len2+1))%MOD;
		printf("%lld\n",ans);
	}
	return 0;
}

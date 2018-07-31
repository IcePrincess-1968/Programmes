#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <bitset>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline LL getLL()
{
	bool f;char ch;LL res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

char s[148];int len;
string ans;

inline bool check_valid()
{
	int i;
	for (i=1;i<=len-1;i++)
		if (s[i]=='_' && s[i+1]=='_') return false;
	bool C=false,Java=false;
	for (i=1;i<=len;i++)
	{
		if (s[i]=='_') C=true;
		if (isupper(s[i])) Java=true;
	}
	if (C && Java) return false;
	if (s[len]=='_') return false;
	if (isupper(s[1])) return false;
	if (s[1]=='_') return false;
	return true;
}

inline bool Java()
{
	int i;
	for (i=1;i<=len;i++) if (s[i]=='_') return false;
	return true;
}

inline void toC()
{
	ans="";
	for (register int i=1;i<=len;i++)
		if (isupper(s[i]))
		{
			ans+="_";
			ans+=string(1,s[i]+32);
		}
		else
			ans+=string(1,s[i]);
}

inline void toJava()
{
	ans="";
	for (register int i=1;i<=len;i++)
	{
		if (s[i]=='_') continue;
		if (i>1 && s[i-1]=='_') ans+=string(1,s[i]-32); else ans+=string(1,s[i]);
	}
}

int main ()
{
	freopen ("java_c.in","r",stdin);
	freopen ("java_c.out","w",stdout);
	scanf("%s",s+1);len=strlen(s+1);
	if (!check_valid()) {puts("Error!");return 0;}
	if (Java()) toC(); else toJava();
	cout<<ans<<endl;
	return 0;
}

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
const double eps=1e-10;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

bool state[1048];int result[1048];

int n,m,e;
vector<int> v[1048];

bool find (int cur)
{
	int i,y;
	for (i=0;i<v[cur].size();i++)
	{
		y=v[cur][i];
		if (!state[y])
		{
			state[y]=true;
			if (!result[y] || find(result[y]))
			{
				result[y]=cur;
				return true;
			}
		}
	}
	return false;
}

int main ()
{
	int i,x,y;
	n=getint();m=getint();e=getint();
	for (i=1;i<=e;i++)
	{
		x=getint();y=getint();
		if (y<=m) v[x].pb(y);
	}
	int ans=0;
	for (i=1;i<=n;i++)
	{
		memset(state,false,sizeof(state));
		if (find(i)) ans++;
	}
	printf("%d\n",ans);
	return 0;
}
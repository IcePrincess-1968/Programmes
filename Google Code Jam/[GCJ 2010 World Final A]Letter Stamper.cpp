#pragma GCC optimize ("O3")
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
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}
 
string table[10];
int dp[2][7048][8];
char s[7048];int len;
int tmp[7048],minn[7048],pt;

void init()
{
	table[1]="ABC";table[2]="ACB";
	table[3]="BAC";table[4]="BCA";
	table[5]="CAB";table[6]="CBA";
}

char query(int type,int pos)
{
	if (pos==0) return '#';
	pos=(pos-1)%3+1;
	return table[type][pos-1];
}

int main ()
{
	int i,j,jj,step,cur,ca,tt=0;
	ca=getint();
	init();
	while (ca--)
	{
		scanf("%s",s+1);len=strlen(s+1);
		for (i=0;i<=len;i++)
			for (j=1;j<=6;j++)
				dp[0][i][j]=i;
		for (step=1,cur=1;step<=len;step++,cur^=1)
		{
			for (j=1;j<=6;j++)
			{
				for (i=0;i<=len;i++)
					dp[cur][i][j]=INF;
				for (i=0;i<=len;i++)
					if (query(j,i)==s[step])
					{
						dp[cur][i][j]=min(dp[cur][i][j],dp[cur^1][i][j]+1);
						if (i) dp[cur][i][j]=min(dp[cur][i][j],dp[cur^1][i-1][j]+2);
						if (i<len) dp[cur][i][j]=min(dp[cur][i][j],dp[cur^1][i+1][j]+2);
					}
				for (i=1;i<=len;i++) dp[cur][i][j]=min(dp[cur][i][j],dp[cur][i-1][j]+1);
				for (i=len-1;i>=0;i--) dp[cur][i][j]=min(dp[cur][i][j],dp[cur][i+1][j]+1);
			}
			for (j=1;j<=6;j++)
				for (jj=1;jj<=6;jj++)
				{
					dp[cur][0][j]=min(dp[cur][0][j],dp[cur][0][jj]);
					if (query(j,1)==query(jj,1)) dp[cur][1][j]=min(dp[cur][1][j],dp[cur][1][jj]);
				}
		}
		int ans=INF;
		for (i=1;i<=6;i++) ans=min(ans,dp[cur^1][0][i]);
		printf("Case #%d: %d\n",++tt,ans);
	}
	return 0;
}
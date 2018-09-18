#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <list>
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

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
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

char s[48];
int len,n,budget;
LL dp[2][40][40][40][40];
pair<int,LL> a[48][5048],b[48][5048];int atot[48],btot[48];
LL suma[48][5048],sumb[48][5048];
int toa[48][48],tob[48][48];
int posl[48],posr[48];
int table[248],ind=0;

inline bool cmp(Pair x,Pair y) {return x.x>y.x;}

inline void update(int curlen,int left,int right,int tol,int tor,LL val)
{
	if (dp[curlen][left][right][tol][tor]==-1)
		dp[curlen][left][right][tol][tor]=val;
	else
		dp[curlen][left][right][tol][tor]=min(dp[curlen][left][right][tol][tor],val);
}

int main ()
{
	int i,j,k,l,r,curlen,tol,tor;LL c;len=getint();n=getint();budget=getint();
	scanf("%s",s+1);
	for (i=1;i<=len;i++) if (!table[s[i]]) table[s[i]]=++ind;
	memset(atot,0,sizeof(atot));memset(btot,0,sizeof(btot));
	for (i=1;i<=n;i++)
	{
		l=getint();r=getint();c=getLL();c=min(c,(long long)1e9);
		a[l][++atot[l]]=mp(r,c);b[r][++btot[r]]=mp(l,c);
	}
	for (i=1;i<=len;i++) sort(a[i]+1,a[i]+atot[i]+1),sort(b[i]+1,b[i]+btot[i]+1,cmp);
	for (i=1;i<=len;i++)
	{
		suma[i][0]=0;
		for (j=1;j<=atot[i];j++) suma[i][j]=suma[i][j-1]+a[i][j].y;
		sumb[i][0]=0;
		for (j=1;j<=btot[i];j++) sumb[i][j]=sumb[i][j-1]+b[i][j].y;
	}
	for (i=1;i<=len;i++)
	{
		k=0;
		for (j=i;j<=len;j++)
		{
			while (k<atot[i] && a[i][k+1].x<=j) k++;
			toa[i][j]=k;
		}
		k=0;
		for (j=i;j>=1;j--)
		{
			while (k<btot[i] && b[i][k+1].x>=j) k++;
			tob[i][j]=k;
		}
	}
	memset(dp[0],-1,sizeof(dp));
	for (i=1;i<=len-1;i++)
		for (j=i+1;j<=len;j++)
			if (s[i]==s[j])
				if (i+1<j)
					dp[0][i][j][i][j]=suma[i][toa[i][i]]+sumb[j][tob[j][j]];
				else
					dp[0][i][j][j][i]=suma[i][toa[i][j]]+sumb[i+1][tob[i+1][i+1]];
	int cur=0,nxt=1;int ans=0;
	for (curlen=2;curlen<=len;curlen+=2)
	{
		memset(dp[nxt],-1,sizeof(dp[nxt]));
		for (l=1;l<=len-1;l++)
			for (r=l+1;r<=len;r++)
				for (tol=l;tol<=r;tol++)
					for (tor=l;tor<=r;tor++)
						if (dp[cur][l][r][tol][tor]!=-1 && dp[cur][l][r][tol][tor]<=budget)
						{
							ans=max(ans,curlen);
							if (l>1 && r<len && s[l-1]==s[r+1])
							{
								if (tol==r && tor==l)
									update(nxt,l-1,r+1,r+1,l-1,dp[cur][l][r][tol][tor]+suma[l-1][toa[l-1][r+1]]+sumb[r+1][tob[r+1][l]]);
								else
									update(nxt,l-1,r+1,tol,tor,dp[cur][l][r][tol][tor]+suma[l-1][toa[l-1][tol]]+sumb[r+1][tob[r+1][tor]]);
							}
							if (l>1)
								for (i=r+2;i<=len;i++)
									if (s[l-1]==s[i])
									{
										update(nxt,l-1,i,tol,i,dp[cur][l][r][tol][tor]+suma[l-1][toa[l-1][tol]]+sumb[i][tob[i][i]]);
										break;
									}
							if (r<len)
								for (i=l-2;i>=1;i--)
									if (s[r+1]==s[i])
									{
										update(nxt,i,r+1,i,tor,dp[cur][l][r][tol][tor]+suma[i][toa[i][i]]+sumb[r+1][tob[r+1][tor]]);
										break;
									}
							/*for (i=1;i<=ind;i++) posl[i]=posr[i]=0;
							for (i=l-2;i>=1;i--)
								if (!posl[table[s[i]]]) posl[table[s[i]]]=i;
							for (i=r+2;i<=len;i++)
								if (!posr[table[s[i]]]) posr[table[s[i]]]=i;
							for (i=1;i<=ind;i++)
								if (posl[i] && posr[i])
									update(nxt,posl[i],posr[i],posl[i],posr[i],dp[cur][l][r][tol][tor]+suma[posl[i]][toa[posl[i]][posl[i]]]+sumb[posr[i]][tob[posr[i]][posr[i]]]);*/
							for (i=l-2;i>=1;i--)
								for (j=r+2;j<=len;j++)
									if (s[i]==s[j])
										update(nxt,i,j,i,j,dp[cur][l][r][tol][tor]+suma[i][toa[i][i]]+sumb[j][tob[j][j]]);
						}
		swap(nxt,cur);
	}
	printf("%d\n",ans);
	return 0;
}

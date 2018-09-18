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

vector<Pair> v[500048];
int n,len;
char type[5],s[500048];
Pair dp1[500048],dp2[500048];
Pair dp11[500048],dp22[500048];
bool ans_exist;Pair ans;

struct node
{
	int val;
	int ind;
	int from;
};

void dfs(int cur,int father)
{
	int i,y;
	if ((int(v[cur].size())==1 && father!=-1) || int(v[cur].size())==0)
	{
		dp1[cur]=dp2[cur]=mp(0,cur);
		return;
	}
	dp1[cur]=dp2[cur]=mp(-1,cur);
	for (i=0;i<int(v[cur].size());i++)
		if (v[cur][i].x!=father)
		{
			y=v[cur][i].x;
			dfs(y,cur);
			if (ans_exist) return;
			int tmp1=((s[dp1[y].x+1]-'a'+1==v[cur][i].y)?1:0),tmp2=((s[len-dp2[y].x]-'a'+1==v[cur][i].y)?1:0);
			if (dp1[y].x+tmp1>dp1[cur].x) dp1[cur]=mp(dp1[y].x+tmp1,dp1[y].y);
			if (dp2[y].x+tmp2>dp2[cur].x) dp2[cur]=mp(dp2[y].x+tmp2,dp2[y].y);
		}
	if ((v[cur].size()==2 && father!=-1) || (v[cur].size()==1 && father==-1))
	{
		if (dp1[cur].x>=len)
		{
			ans_exist=true;
			ans=mp(dp1[cur].y,cur);
			return;
		}
		if (dp2[cur].x>=len)
		{
			ans_exist=true;
			ans=mp(cur,dp2[cur].y);
			return;
		}
		return;
	}
	node fmax1,smax1,fmax2,smax2;
	fmax1.val=smax1.val=fmax2.val=smax2.val=-1;
	for (i=0;i<v[cur].size();i++)
		if (v[cur][i].x!=father)
		{
			y=v[cur][i].x;
			int tmp=(s[dp1[y].x+1]-'a'+1==v[cur][i].y?1:0);
			if (dp1[y].x+tmp>fmax1.val)
			{
				smax1=fmax1;
				fmax1.val=dp1[y].x+tmp;
				fmax1.ind=dp1[y].y;
				fmax1.from=y;
			}
			else
			{
				if (dp1[y].x+tmp>smax1.val)
				{
					smax1.val=dp1[y].x+tmp;
					smax1.ind=dp1[y].y;
					smax1.from=y;
				}
			}
			tmp=s[len-dp2[y].x]-'a'+1==v[cur][i].y?1:0;
			if (dp2[y].x+tmp>fmax2.val)
			{
				smax2=fmax2;
				fmax2.val=dp2[y].x+tmp;
				fmax2.ind=dp2[y].y;
				fmax2.from=y;
			}
			else
			{
				if (dp2[y].x+tmp>smax2.val)
				{
					smax2.val=dp2[y].x+tmp;
					smax2.ind=dp2[y].y;
					smax2.from=y;
				}
			}
		}
	if (fmax1.from!=fmax2.from)
	{
		if (fmax1.val+fmax2.val>=len)
		{
			ans_exist=true;
			ans=mp(fmax1.ind,fmax2.ind);
		}
		return;
	}
	if (fmax1.val+smax2.val>=len)
	{
		ans_exist=true;
		ans=mp(fmax1.ind,smax2.ind);
		return;
	}
	if (smax1.val+fmax2.val>=len)
	{
		ans_exist=true;
		ans=mp(smax1.ind,fmax2.ind);
		return;
	}
}

int main ()
{
	int i,x,y;
	n=getint();len=getint();
	for (i=1;i<=n-1;i++)
	{
		scanf("%d%d%s",&x,&y,type+1);
		v[x].pb(mp(y,type[1]-'a'+1));
		v[y].pb(mp(x,type[1]-'a'+1));
	}
	scanf("%s",s+1);
	ans_exist=false;ans=mp(-1,-1);dfs(1,-1);
	printf("%d %d\n",ans.x,ans.y);
	return 0;
}

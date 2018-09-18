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

const LL MOD=1e9+7;
const LL LINF=2e16;
const int INF=1e9;
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

char s[248];int len;
char ss[448][148];int slen[448];int n;
int val[448];
int DP[348][348],Dp[348];
int dp[51][10048];

struct node
{
	int nxt[30];
	vector<int> val;
	inline void init()
	{
		memset(nxt,0,sizeof(nxt));
		val.clear();
	}
}trie[300048];int tot=0;

inline void Insert(int ind)
{
	int i,w,clen=strlen(ss[ind]+1),cur=1;
	for (i=1;i<=clen;i++)
	{
		int w=ss[ind][i]-'a'+1;
		if (!trie[cur].nxt[w])
		{
			trie[cur].nxt[w]=++tot;
			trie[tot].init();
		}
		cur=trie[cur].nxt[w];
		if (i==clen) trie[cur].val.pb(val[ind]);
	}
}

queue<int> q;bool inq[51][10048];
inline int solve(int left,int right)
{
	int i,j,k,m,cur=1,pos;
	cur=trie[cur].nxt[s[left]-'a'+1];
	for (i=left;i<=right;i++)
		for (j=1;j<=tot;j++)
			dp[i][j]=-INF;
	memset(inq,false,sizeof(inq));
	dp[left][cur]=0;inq[left][cur]=true;
	q.push(left);q.push(cur);
	while (!q.empty())
	{
		pos=q.front();q.pop();cur=q.front();q.pop();
		inq[pos][cur]=false;
		for (i=0;i<int(trie[cur].val.size());i++)
			DP[left][right]=max(DP[left][right],dp[pos][cur]+trie[cur].val[i]+(pos+1<=right?DP[pos+1][right]:0));
		for (i=pos+1;i<=right;i++)
			if (trie[cur].nxt[s[i]-'a'+1])
			{
				if (dp[i][trie[cur].nxt[s[i]-'a'+1]]<dp[pos][cur]+(pos+1<=i-1?DP[pos+1][i-1]:0))
				{
					dp[i][trie[cur].nxt[s[i]-'a'+1]]=dp[pos][cur]+(pos+1<=i-1?DP[pos+1][i-1]:0);
					if (!inq[i][trie[cur].nxt[s[i]-'a'+1]])
					{
						inq[i][trie[cur].nxt[s[i]-'a'+1]]=true;
						q.push(i);q.push(trie[cur].nxt[s[i]-'a'+1]);
					}
				}
			}
	}
	return DP[left][right];
}

int main ()
{
	int i,j;
	scanf("%s",s+1);len=strlen(s+1);
	n=getint();tot=1;trie[1].init();
	for (i=1;i<=n*2-1;i+=2)
	{
		scanf("%s%d",ss[i]+1,&val[i]);
		slen[i]=strlen(ss[i]+1);
		Insert(i);
		slen[i+1]=slen[i];val[i+1]=val[i];
		for (j=slen[i+1];j;j--) ss[i+1][j]=ss[i][slen[i+1]-j+1];
		Insert(i+1);
	}
	n*=2;
	for (i=0;i<=len;i++)
		for (j=0;j<=len;j++)
			DP[i][j]=-INF;
	for (i=1;i<=len;i++)
		for (j=1;j<=len-i+1;j++)
			DP[j][j+i-1]=solve(j,j+i-1);
	Dp[0]=0;
	for (i=1;i<=len;i++)
	{
		Dp[i]=Dp[i-1];
		for (j=0;j<=i-1;j++)
			Dp[i]=max(Dp[i],Dp[j]+DP[j+1][i]);
	}
	printf("%d\n",Dp[len]);
	return 0;
}


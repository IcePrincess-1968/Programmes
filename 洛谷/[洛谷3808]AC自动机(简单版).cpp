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

struct node
{
	int next[27];
	int fail,ind;
	inline void clear()
	{
		fail=0;ind=0;
		for (register int i=1;i<=26;i++) next[i]=0;
	}
}trie[1000048];int tot=0;

int n;
char s[1000048];

inline void Insert()
{
	int len=strlen(s+1),i,cur=1,w;
	for (i=1;i<=len;i++)
	{
		w=s[i]-'a'+1;
		if (!trie[cur].next[w])
		{
			trie[cur].next[w]=++tot;
			trie[tot].clear();
		}
		cur=trie[cur].next[w];
		if (i==len) trie[cur].ind++;
	}
}

queue<int> q;
inline void construct_fail()
{
	int i,cur,tmp;q.push(1);
	while (!q.empty())
	{
		cur=q.front();q;q.pop();
		for (i=1;i<=26;i++)
			if (trie[cur].next[i])
			{
				tmp=trie[cur].fail;
				while (tmp && !trie[tmp].next[i]) tmp=trie[tmp].fail;
				trie[trie[cur].next[i]].fail=(tmp?trie[tmp].next[i]:1);
				q.push(trie[cur].next[i]);
			}
			else
				trie[cur].next[i]=(cur==1?1:trie[trie[cur].fail].next[i]);
	}
}

int ans=0;
inline void solve()
{
	int len=strlen(s+1),cur=1,tmp,i,j,w;
	for (i=1;i<=len;i++)
	{
		w=s[i]-'a'+1;
		cur=trie[cur].next[w];
		tmp=cur;
		while (tmp)
		{
			if (trie[tmp].ind==-1) break;
			ans+=trie[tmp].ind;
			trie[tmp].ind=-1;tmp=trie[tmp].fail;
		}
	}
}

int main ()
{
	int i;n=getint();
	tot=1;trie[tot].clear();
	for (i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		Insert();
	}
	construct_fail();
	memset(s,'\0',sizeof(s));
	scanf("%s",s+1);
	solve();printf("%d\n",ans);
	return 0;
}

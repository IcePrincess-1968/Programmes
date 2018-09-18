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

struct node
{
	int ind,fail;
	int next[48];
}trie[100048];
int tot;

char ss[248][101];

int slen[248],cnt[248];

int n;
char s[1000048];
vector<int> ans_ind;

void Clear()
{
	int i;
	tot=1;
	for (i=1;i<=26;i++) trie[1].next[i]=0;
	trie[1].ind=trie[1].fail=0;
	for (i=1;i<=n;i++) cnt[i]=0;
}

void Insert(int ind,int len)
{
	int i,j,cur=1;
	for (i=1;i<=len;i++)
	{
		if (!trie[cur].next[s[i]-'a'+1])
		{
			trie[cur].next[s[i]-'a'+1]=++tot;
			trie[tot].fail=trie[tot].ind=0;
			for (j=1;j<=26;j++) trie[tot].next[j]=0;
		}
		cur=trie[cur].next[s[i]-'a'+1];
		if (i==len) trie[cur].ind=ind;
	}
}

queue<int> q;
void construct_fail()
{
	int i,cur;q.push(1);
	while (!q.empty())
	{
		cur=q.front();q.pop();
		for (i=1;i<=26;i++)
			if (trie[cur].next[i])
			{
				int tmp=trie[cur].fail;
				while (tmp && !trie[tmp].next[i]) tmp=trie[tmp].fail;
				trie[trie[cur].next[i]].fail=tmp?trie[tmp].next[i]:1;
				q.push(trie[cur].next[i]);
			}
			else
				trie[cur].next[i]=cur==1?1:trie[trie[cur].fail].next[i];
	}
}

int len;
void query()
{
	int i,cur=1,tmp;
	for (i=1;i<=len;i++)
	{
		cur=trie[cur].next[s[i]-'a'+1];
		tmp=cur;
		while (tmp)
		{
			if (trie[tmp].ind) cnt[trie[tmp].ind]++;
			tmp=trie[tmp].fail;
		}
	}
}

int main ()
{
	int i,j,max_cnt;
	while (scanf("%d",&n) && n)
	{
		Clear();
		for (i=1;i<=n;i++)
		{
			scanf("%s",s+1);
			slen[i]=strlen(s+1);
			memset(ss[i],'\0',sizeof(ss[i]));
			for (j=1;j<=slen[i];j++) ss[i][j]=s[j];
			Insert(i,slen[i]);
		}
		construct_fail();
		scanf("%s",s+1);len=strlen(s+1);
		query();
		max_cnt=0;ans_ind.clear();
		for (i=1;i<=n;i++)
			if (cnt[i]>max_cnt)
			{
				max_cnt=cnt[i];
				ans_ind.clear();ans_ind.pb(i);
			}
			else if (cnt[i]==max_cnt) ans_ind.pb(i);
		printf("%d\n",max_cnt);
		sort(ans_ind.begin(),ans_ind.end());
		for (i=0;i<int(ans_ind.size());i++) printf("%s\n",ss[ans_ind[i]]+1);
	}
	return 0;
}
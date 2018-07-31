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

int n,q,tot=0;
int root[200048];
struct node
{
	int num;
	int val;
	int nv;
}a[200048];
int table[200048],ind;

bool cmp_val(node x,node y)
{
	return x.val<y.val;
}
bool cmp_num(node x,node y)
{
	return x.num<y.num;
}

struct Tree
{
	int left,right;
	int lson,rson;
	int cnt;
}tree[4000048];

inline void pushup(int cur)
{
	tree[cur].cnt=tree[tree[cur].lson].cnt+tree[tree[cur].rson].cnt;
}

void build(int cur,int left,int right)
{
	tree[cur].left=left;tree[cur].right=right;tree[cur].cnt=0;
	if (left!=right)
	{
		int mid=(left+right)>>1;
		tree[cur].lson=++tot;
		build(tree[cur].lson,left,mid);
		tree[cur].rson=++tot;
		build(tree[cur].rson,mid+1,right);
	}
}

void Insert(int last,int cur,int pos)
{
	tree[cur]=tree[last];
	if (tree[cur].left==tree[cur].right)
	{
		tree[cur].cnt++;
		return;
	}
	int mid=(tree[cur].left+tree[cur].right)>>1;
	if (pos<=mid)
	{
		tree[cur].lson=++tot;
		Insert(tree[last].lson,tree[cur].lson,pos);
		pushup(cur);
	}
	else
	{
		tree[cur].rson=++tot;
		Insert(tree[last].rson,tree[cur].rson,pos);
		pushup(cur);
	}
}

int query(int left,int right,int k)
{
	if (tree[left].left==tree[left].right) return tree[left].left;
	int left_cnt=tree[tree[right].lson].cnt-tree[tree[left].lson].cnt;
	if (left_cnt<k) 
		return query(tree[left].rson,tree[right].rson,k-left_cnt);
	else
		return query(tree[left].lson,tree[right].lson,k);
}

int main ()
{
	int i,l,r,k;
	n=getint();q=getint();
	for (i=1;i<=n;i++)
	{
		a[i].num=i;
		a[i].val=getint();
	}
	sort(a+1,a+n+1,cmp_val);
	a[1].nv=1;table[1]=a[1].val;
	for (i=2;i<=n;i++)
	{
		a[i].nv=a[i-1].nv+(a[i].val==a[i-1].val?0:1);
		table[a[i].nv]=a[i].val;
	}
	ind=a[n].nv;sort(a+1,a+n+1,cmp_num);
	root[0]=++tot;build(root[0],1,ind);
	for (i=1;i<=n;i++)
	{
		root[i]=++tot;
		Insert(root[i-1],root[i],a[i].nv);
	}
	while (q--)
	{
		l=getint();r=getint();k=getint();
		printf("%d\n",table[query(root[l-1],root[r],k)]);
	}
	return 0;
}

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
#define DEBUG(...) 
using namespace std;

const int MOD=1e9+7;
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

int n,m;
Pair a[200048];

namespace SegmentTree
{
	struct node
	{
		int left,right,sz;
		int minval;
	}tree[1000048];
	inline void build(int cur,int left,int right)
	{
		tree[cur].left=left;tree[cur].right=right;tree[cur].sz=0;
		tree[cur].minval=INF;
		if (left!=right)
		{
			int mid=(left+right)>>1;
			build(cur<<1,left,mid);build(cur<<1|1,mid+1,right);
		}
	}
	inline int pushup(int val1,int sz,int val2) {return min(val1,val2-sz);}
	inline void Insert(int cur,int pos)
	{
		if (tree[cur].left==tree[cur].right)
		{
			tree[cur].sz++;tree[cur].minval=pos-tree[cur].sz;
			return;
		}
		int mid=(tree[cur].left+tree[cur].right)>>1;
		if (pos<=mid) Insert(cur<<1,pos); else Insert(cur<<1|1,pos);
		tree[cur].minval=pushup(tree[cur<<1].minval,tree[cur<<1].sz,tree[cur<<1|1].minval);
		tree[cur].sz=tree[cur<<1].sz+tree[cur<<1|1].sz;
	}
	inline int query_rank(int cur,int pos)
	{
		if (tree[cur].left==tree[cur].right) return tree[cur].sz;
		int mid=(tree[cur].left+tree[cur].right)>>1;
		if (pos<=mid) return query_rank(cur<<1,pos); else return query_rank(cur<<1|1,pos)+tree[cur<<1].sz;
	}
	inline Pair query_min(int cur,int left,int right)
	{
		if (left>right) return mp(INF,0);
		if (left<=tree[cur].left && tree[cur].right<=right) return mp(tree[cur].minval,tree[cur].sz);
		Pair res1=mp(INF,0),res2=mp(INF,0);int mid=(tree[cur].left+tree[cur].right)>>1;
		if (left<=mid) res1=query_min(cur<<1,left,right);
		if (mid+1<=right) res2=query_min(cur<<1|1,left,right);
		Pair res;res.x=pushup(res1.x,res1.y,res2.x);res.y=res1.y+res2.y;
		return res;
	}
	inline int query_max(int cur)
	{
		if (tree[cur].left==tree[cur].right) return tree[cur].left;
		if (tree[cur<<1|1].sz) return query_max(cur<<1|1); else return query_max(cur<<1);
	}
}

int main ()
{
	int i;n=getint();m=getint();
	for (i=1;i<=n;i++) a[i].x=getint(),a[i].y=getint();
	sort(a+1,a+n+1);
	SegmentTree::build(1,0,m);
	int ans=0,curans;
	for (i=1;i<=n;i++)
	{
		SegmentTree::Insert(1,m+1-a[i].y);
		if (a[i].x+1>=a[i].y) ans=max(ans,i-m);
		int ck=SegmentTree::query_rank(1,m+1-a[i].y);
		curans=a[i].x+(m+1-a[i].y)-ck;
		Pair res=SegmentTree::query_min(1,m+1-a[i].y+1,m+1-a[i].x-2);
		curans=min(curans,a[i].x+res.x-ck);
		ans=max(ans,-curans);
		ans=max(ans,i-min(a[i].x+SegmentTree::query_max(1),m));
	}
	printf("%d\n",ans);
	return 0;
}

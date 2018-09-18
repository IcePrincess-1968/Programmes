#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <map>
#include <stack>
#include <set>
#include <vector>
#include <queue>
#include <deque>
#include <sstream>
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LL long long
#define LB long double
#define Pair pair<int,int>
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const double eps=1e-10;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;

inline int getint()
{
	char ch;bool f;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	f=(ch=='-')?true:false;
	res=(ch=='-')?0:ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?-res:res;
}

int n;
struct node
{
	int val;
	int num;
	int nv;
}ori[100048];
int a[100048],top;
int cur[100048],last_pos[100048];
int ans[100048];
int cnt[100048],cur_ans;
bool exist[100048];

int c[100048];
inline int query(int x)
{
	int res=0;
	while (x>0)
	{
		res+=c[x];
		x-=LOWBIT(x);
	}
	return res;
}
inline int calc(int left,int right)
{
	return query(right)-query(left-1);
}
inline void update(int x)
{
	while (x<=top)
	{
		c[x]++;
		x+=LOWBIT(x);
	}
}

bool cmp_val(node x,node y)
{
	return x.val<y.val;
}

bool cmp_num(node x,node y)
{
	return x.num<y.num;
}

struct Query
{
	int left,right;
	int num;
}q[100048];
int q_top=0;

bool cmp(Query x,Query y)
{
	if (x.left/magic!=y.left/magic) return x.left/magic<y.left/magic;
	return x.right<y.right;
}

int main ()
{
	freopen ("mtf.in","r",stdin);
	freopen ("mtf.out","w",stdout);
	int i,j,cur_left,cur_right;
	n=getint();
	for (i=1;i<=n;i++)
	{
		ori[i].val=getint();
		ori[i].num=i;
	}
	sort(ori+1,ori+n+1,cmp_val);
	top=1;
	for (i=1;i<=n;i++)
	{
		if (i!=1 && ori[i].val!=ori[i-1].val) ++top;
		ori[i].nv=top;
	}
	sort(ori+1,ori+n+1,cmp_num);
	for (i=1;i<=n;i++) a[i]=ori[i].nv;
	for (i=1;i<=top;i++) cur[i]=-1;
	for (i=1;i<=n;i++) last_pos[i]=cur[a[i]],cur[a[i]]=i;
	for (i=1;i<=n;i++)
	{
		if (last_pos[i]==-1) ans[i]=ori[i].val+calc(a[i]+1,top);
		if (!exist[a[i]]) update(a[i]),exist[a[i]]=true;		
	}
	for (i=1;i<=n;i++)
		if (last_pos[i]!=-1)
		{
			q[++q_top].left=last_pos[i]+1;
			q[q_top].right=i-1;
			q[q_top].num=i;
		}
	sort(q+1,q+q_top+1,cmp);
	memset(cnt,0,sizeof(cnt));cur_ans=0;
	for (i=q[1].left;i<=q[1].right;i++)
	{
		cnt[a[i]]++;
		if (cnt[a[i]]==1) cur_ans++;
	}
	ans[q[1].num]=cur_ans+1;
	cur_left=q[1].left;cur_right=q[1].right;
	for (i=2;i<=q_top;i++)
	{
		if (q[i].left<cur_left)
			for (j=cur_left-1;j>=q[i].left;j--)
			{
				cnt[a[j]]++;
				if (cnt[a[j]]==1) cur_ans++;
			}
		if (q[i].left>cur_left)
			for (j=cur_left;j<=q[i].left-1;j++)
			{
				cnt[a[j]]--;
				if (!cnt[a[j]]) cur_ans--;
			}
		if (q[i].right<cur_right)
			for (j=cur_right;j>=q[i].right+1;j--)
			{
				cnt[a[j]]--;
				if (!cnt[a[j]]) cur_ans--;
			}
		if (q[i].right>cur_right)
			for (j=cur_right+1;j<=q[i].right;j++)
			{
				cnt[a[j]]++;
				if (cnt[a[j]]==1) cur_ans++;
			}
		ans[q[i].num]=cur_ans+1;
		cur_left=q[i].left;cur_right=q[i].right;
	}
	for (i=1;i<=n;i++) printf("%d ",ans[i]);
	printf("\n");
	return 0;
}

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

const int MOD=1e9+9;
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

int n,k;
int a[100048];

struct Up
{
	int left,right,h;
}up[100048];int utot;

int L[100048],R[100048];
bool visited[100048];

struct Down
{
	int left,right,h;
}down[100048];int dtot;

priority_queue<pair<Pair,int> > q;
int ver[100048];

struct DSU
{
	int pre[100048];
	inline void init() {for (register int i=0;i<=utot+1;i++) pre[i]=i;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;}
}Left,Right;


int main ()
{
	int i,ca;ca=getint();int k1,k2;
	while (ca--)
	{
		n=getint();k=getint();
		for (i=2;i<=n+1;i++) a[i]=getint();
		utot=dtot=0;
		while (!q.empty()) q.pop();
		a[1]=a[n+2]=0;n+=2;k1=2;
		while (k1<=n)
		{
			if (k1==n) break;
			k2=k1;
			while (a[k2]==a[k1]) k2++;
			if (a[k1-1]<a[k1] && a[k2]<a[k2-1]) up[++utot]=Up{k1,k2-1,a[k1]};
			k1=k2;
		}
		k1=2;down[++dtot]=Down{1,1,0};
		while (k1<=n)
		{
			if (k1==n) break;
			k2=k1;
			while (a[k2]==a[k1]) k2++;
			if (a[k1-1]>a[k1] && a[k2]>a[k2-1]) down[++dtot]=Down{k1,k2-1,a[k1]};
			k1=k2;
		}
		down[++dtot]=Down{n,n,0};
		int pt=1;
		for (i=1;i<=utot;i++)
		{
			while (down[pt].left<=up[i].right) pt++;
			R[i]=pt;
		}
		pt=dtot;
		for (i=utot;i>=1;i--)
		{
			while (down[pt].right>=up[i].left) pt--;
			L[i]=pt;
		}
		int need=utot-k;
		if (need<=0) {puts("0");continue;}
		for (i=1;i<=utot;i++)
		{
			int nei=max(down[R[i]].h,down[L[i]].h);
			q.push(mp(mp(-up[i].h+nei,i),1));
			ver[i]=1;
		}
		LL ans=0;int cnt=0;
		Left.init();Right.init();
		while (cnt<need)
		{
			int ind=q.top().x.y,add=-q.top().x.x;int vnum=q.top().y;q.pop();
			if (vnum!=ver[ind]) continue;
			cnt++;ans+=add;
			int lefth=down[L[ind]].h,righth=down[R[ind]].h;
			int lind=Left.find_anc(ind-1),rind=Right.find_anc(ind+1);
			if (lefth>righth)
				if (lind)
				{
					R[lind]=R[ind];
					int nei=max(down[R[lind]].h,down[L[lind]].h);
					ver[lind]++;
					q.push(mp(mp(-up[lind].h+nei,lind),ver[lind]));
				}
			if (lefth<righth)
				if (rind!=utot+1)
				{
					L[rind]=L[ind];
					int nei=max(down[R[rind]].h,down[L[rind]].h);
					ver[rind]++;
					q.push(mp(mp(-up[rind].h+nei,rind),ver[rind]));
				}
			Left.update(ind,lind);Right.update(ind,rind);
		}
		printf("%lld\n",ans);
	}
	return 0;
}

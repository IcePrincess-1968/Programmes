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
const LB eps=1e-10;
const LB pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n;
int t1,t2;
int a[100048],b[100048];

inline bool check1()
{
	int i;
	for (i=1;i<=n;i++)
		if (a[i]!=b[i]) return false;
	return true;
}

int pre[100048];
inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
inline void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;}

inline int check2()
{
	int i,res=0;
	for (i=1;i<=100000;i++) pre[i]=i;
	for (i=1;i<=100000;i++)
	{
		int x=a[i],y=b[i];
		if (find_anc(x)!=find_anc(y)) res++;
		update(x,y);
	}
	return res;
}

int d[100048];
vector<int> v[100048];
int anc[100048][21];
bool exist[100048];
bool hascir[100048];int num;
bool visited[100048];
queue<int> q;

inline int check12()
{
	int i,cur,nn=0;
	memset(exist,false,sizeof(exist));
	for (i=1;i<=100000;i++) pre[i]=i;
	for (i=1;i<=n;i++) if (a[i]!=b[i]) update(a[i],b[i]),exist[a[i]]=true,exist[b[i]]=true;
	for (i=1;i<=100000;i++) if (exist[i]) nn++;
	memset(hascir,false,sizeof(hascir));
	for (i=1;i<=100000;i++)
		if (exist[i] && i==find_anc(i)) num++;
	for (i=1;i<=n;i++) if (a[i]!=b[i]) v[a[i]].pb(b[i]),d[b[i]]++;
	memset(visited,false,sizeof(visited));
	for (i=1;i<=100000;i++) if (exist[i] && !d[i]) q.push(i);
	while (!q.empty())
	{
		cur=q.front();q.pop();
		visited[cur]++;
		for (i=0;i<int(v[cur].size());i++)
		{
			d[v[cur][i]]--;
			if (!d[v[cur][i]]) q.push(v[cur][i]);
		}
	}
	for (i=1;i<=100000;i++) if (exist[i] && !visited[i]) hascir[find_anc(i)]=true;
	int res=nn-num;
	for (i=1;i<=100000;i++) if (hascir[i]) res++;
	return res;
}

int main ()
{
	int i;
	n=getint();char type[48];
	scanf("%s",type+1);t1=(type[1]=='C'?1:2);
	for (i=1;i<=n;i++) a[i]=getint();
	scanf("%s",type+1);t2=(type[1]=='C'?1:2);
	for (i=1;i<=n;i++) b[i]=getint();
	if (t1==1 && t2==1)
	{
		if (check1()) printf("0\n"); else printf("-1\n");
		return 0;
	}
	if (t1==2 && t2==2)
	{
		printf("%d\n",check2());
		return 0;
	}
	if (t1==1 && t2==2) for (i=1;i<=n;i++) swap(a[i],b[i]);
	printf("%d\n",check12());
	return 0;
}

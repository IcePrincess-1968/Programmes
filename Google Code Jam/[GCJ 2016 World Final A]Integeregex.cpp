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

inline LL getLL()
{
	char ch;LL res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

LL A,B;
LL dp[30][5048],tans[30],DP[30][5048][2];
int num[30];
char s[48],ss[48];
int len;

struct NFAnode
{
	vector<int> v[18];
}a[148];int tot=0;

struct DFAnode
{
	int v[18];
	bool isaccepted;
}b[100048];int Dtot=0;
int in[100048],starter;

void doit()
{
	int i,cc=1;
	ss[1]=s[1];
	for (i=2;i<=len;i++)
		if (!(s[i]==s[i-1] && s[i]=='*'))
			ss[++cc]=s[i];
	for (i=1;i<=cc;i++) s[i]=ss[i];
	len=strlen(s+1);
}

Pair add_star(int st,int ed)
{
	a[ed].v[10].pb(st);
	++tot;a[tot].v[10].pb(st);
	++tot;a[ed].v[10].pb(tot);
	a[tot-1].v[10].pb(tot);
	return mp(tot-1,tot);
}

Pair add_connect(int st1,int ed1,int st2,int ed2)
{
	a[ed1]=a[st2];
	return mp(st1,ed2);
}

Pair add_u(int st1,int ed1,int st2,int ed2)
{
	++tot;
	a[tot].v[10].pb(st1);a[tot].v[10].pb(st2);
	++tot;
	a[ed1].v[10].pb(tot);a[ed2].v[10].pb(tot);
	return mp(tot-1,tot);
}

Pair construct_NFA(int left,int right)
{
	if (left==right)
	{
		++tot;a[tot].v[s[left]-'0'].pb(tot+1);
		++tot;return mp(tot-1,tot);
	}
	int i,cnt;Pair res1,res2;
	cnt=0;
	for (i=left;i<=right;i++)
	{
		if (s[i]=='(') cnt++;
		if (s[i]==')') cnt--;
		if (!cnt) break;
	}
	if (i==right)
	{
		int ll=left+1,cnt=0;Pair res=mp(-1,-1);
		for (i=left+1;i<=right-1;i++)
		{
			if (s[i]=='(') cnt++;
			if (s[i]==')') cnt--;
			if (s[i]=='|' && !cnt)
			{
				res1=construct_NFA(ll,i-1);
				if (res.x==-1) res=res1; else res=add_u(res.x,res.y,res1.x,res1.y);
				ll=i+1;
			}
		}
		res1=construct_NFA(ll,right-1);
		if (res.x==-1) res=res1; else res=add_u(res.x,res.y,res1.x,res1.y);
		return res;
	}
	if (s[left]=='(')
	{
		cnt=1;
		for (i=left+1;i<=right;i++)
		{
			if (s[i]=='(') cnt++;
			if (s[i]==')') cnt--;
			if (!cnt) break;
		}
		if (s[i+1]=='*')
			res1=construct_NFA(left+1,i-1);
		else
			res1=construct_NFA(left,i);
		if (s[i+1]=='*')
		{
			res1=add_star(res1.x,res1.y);++i;
			if (i==right) return res1;
		}
	}
	else
	{
		res1=construct_NFA(left,left);
		i=left;
	}
	res2=construct_NFA(i+1,right);
	return add_connect(res1.x,res1.y,res2.x,res2.y);
}

typedef pair<LL,LL> pLL;
typedef bitset<100> bs;
map<pair<pLL,int>,bs> Dtrans;
map<pLL,int> mark,inq;
map<pLL,int> ind;

inline pLL bs_to_pLL(bs cur)
{
	pLL res=mp(0,0);
	for (int i=0;i<=99;i++)
		if (cur[i])
		{
			if (i<=62) res.x|=(1ll<<i); else res.y|=(1ll<<(i-63));
		}
	return res;
}

inline bs pLL_to_bs(pLL cur)
{
	int i;bs res=0;
	for (i=0;i<=62;i++)
		if (cur.x&(1ll<<i)) res[i]=1;
	for (i=0;i<=26;i++)
		if (cur.y&(1ll<<i)) res[i+63]=1;
	return res;
}

stack<int> sta;
bs e_closure(bs cur)
{
	bs res=cur;
	int i,cc;
	for (i=1;i<=tot;i++)
		if (cur[i]) sta.push(i);
	while (!sta.empty())
	{
		cc=sta.top();sta.pop();
		for (i=0;i<int(a[cc].v[10].size());i++)
			if (!res[a[cc].v[10][i]])
			{
				res[a[cc].v[10][i]]=1;
				sta.push(a[cc].v[10][i]);
			}
	}
	return res;
}

bs Move(bs cur,int type)
{
	bs res=0;
	int i,j,cc;
	for (i=1;i<=tot;i++)
		if (cur[i]) sta.push(i);
	for (i=1;i<=tot;i++)
		if (cur[i])
			for (j=0;j<int(a[i].v[type].size());j++)
				if (!res[a[i].v[type][j]]) res[a[i].v[type][j]]=1;
	return res;
}

stack<bs> stac;
void construct_DFAtable(int st,int ed)
{
	bs cur=0,to;cur[st]=1;cur=e_closure(cur);
	mark.clear();inq.clear();
	stac.push(cur);inq[bs_to_pLL(cur)]=1;
	Dtrans.clear();
	int type;
	while (!stac.empty())
	{
		cur=stac.top();stac.pop();
		mark[bs_to_pLL(cur)]=1;
		for (type=0;type<=9;type++)
		{
			to=e_closure(Move(cur,type));
			if (!inq[bs_to_pLL(to)])
			{
				inq[bs_to_pLL(to)]=1;
				stac.push(to);
			}
			Dtrans[mp(bs_to_pLL(cur),type)]=to;
		}
	}
}

void add_node(bs cur,int ed)
{
	ind[bs_to_pLL(cur)]=++Dtot;
	if (cur[ed]) b[Dtot].isaccepted=true; else b[Dtot].isaccepted=false;
}

void addedge(int s,int t,int type)
{
	b[s].v[type]=t;
	in[t]++;
}

void construct_DFA(int ed)
{
	Dtot=0;ind.clear();
	map<pair<pLL,int>,bs>::iterator iter;
	for (iter=Dtrans.begin();iter!=Dtrans.end();iter++)
	{
		if (!ind[iter->x.x]) add_node(pLL_to_bs(iter->x.x),ed);
		if (!ind[bs_to_pLL(iter->y)]) add_node(iter->y,ed);
		addedge(ind[iter->x.x],ind[bs_to_pLL(iter->y)],iter->x.y);
	}
}

inline int Next(int cur,int path)
{
	if (!b[cur].v[path]) return -1; else return b[cur].v[path];
}

void init_dp()
{
	int i,j,cdigit,to;
	memset(dp,0,sizeof(dp));
	dp[0][starter]=1;
	for (i=0;i<=19;i++)
		for (j=1;j<=Dtot;j++)
			if (dp[i][j])
				for (i==0?cdigit=1:cdigit=0;cdigit<=9;cdigit++)
				{
					to=Next(j,cdigit);
					if (to!=-1) dp[i+1][to]+=dp[i][j];
				}
	for (i=1;i<=20;i++)
	{
		tans[i]=0;
		for (j=1;j<=Dtot;j++)
			if (b[j].isaccepted)
				tans[i]+=dp[i][j];
	}
}

int ToDigit(LL number)
{
	memset(num,0,sizeof(num));
	int i,pos=20;
	while (number)
	{
		num[pos--]=number%10;
		number/=10;
	}
	for (i=pos+1;i<=20;i++)
		num[i-pos]=num[i];
	return 20-pos;
}

LL solve(LL number)
{
	if (number==0) return 0;
	int i,j,to,cdigit,Len=ToDigit(number);
	LL res=0;
	for (i=1;i<=Len-1;i++) res+=tans[i];
	memset(DP,0,sizeof(DP));
	DP[0][starter][1]=1;
	for (i=0;i<=Len-1;i++)
		for (j=1;j<=Dtot;j++)
			if (DP[i][j][0] || DP[i][j][1])
			{
				to=Next(j,num[i+1]);
				if (to!=-1) DP[i+1][to][1]+=DP[i][j][1];
				for (i==0?cdigit=1:cdigit=0;cdigit<=num[i+1]-1;cdigit++)
				{
					to=Next(j,cdigit);
					if (to!=-1) DP[i+1][to][0]+=DP[i][j][1];
				}
				for (i==0?cdigit=1:cdigit=0;cdigit<=9;cdigit++)
				{
					to=Next(j,cdigit);
					if (to!=-1) DP[i+1][to][0]+=DP[i][j][0];
				}
			}
	for (i=1;i<=Dtot;i++)
		if (b[i].isaccepted) res+=DP[Len][i][0]+DP[Len][i][1];
	return res;
}

void Clear()
{
	int i,j;
	//clear NFAnodes
	for (i=1;i<=tot;i++)
		for (j=0;j<=10;j++)
			a[i].v[j].clear();
	tot=0;
	//clear DFAnodes
	for (i=1;i<=Dtot;i++)
		for (j=0;j<=10;j++)
			b[i].v[j]=0,b[i].isaccepted=false;
	Dtot=0;
	//clear in
	memset(in,0,sizeof(in));
}

int main ()
{
	int i,tt=0;
	int ca=getint();
	while (ca--)
	{
		A=getLL();B=getLL();
		scanf("%s",s+1);len=strlen(s+1);
		doit();
		Clear();
		Pair res=construct_NFA(1,len);
		construct_DFAtable(res.x,res.y);
		construct_DFA(res.y);
		for (i=1;i<=Dtot;i++)
			if (!in[i])
			{
				starter=i;
				break;
			}
		init_dp();
		printf("Case #%d: %lld\n",++tt,solve(B)-solve(A-1));
	}
	return 0;
}
/*
8
1 1000
(0)*1(0)*
379009 379009
379009
1 10000
(12)*(34)*
4 5
45
1 100
((0|1))*
1 50
(01|23|45|67|23)
1 1000000000000000000
((0|1|2|3|4|5|6|7|8|9))*
1 1000
1(56|(((7|8))*9)*)
*/

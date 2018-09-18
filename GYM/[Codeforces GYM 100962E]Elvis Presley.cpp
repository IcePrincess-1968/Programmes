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
#include <ctime>
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

int A,B;
map<Pair,bool> danger;
int num1[48],num2[48],len1,len2;
vector<int> ans;
queue<Pair> q;

bool issuf(int x,int y)
{
	memset(num1,0,sizeof(num1));
	memset(num2,0,sizeof(num2));
	int i;
	for (i=0;i<=30;i++) if (x&(1<<i)) num1[i]=1,len1=i;
	for (i=0;i<=30;i++) if (y&(1<<i)) num2[i]=1,len2=i;
	reverse(num1,num1+len1+1);
	reverse(num2,num2+len2+1);
	for (i=0;i<=len1;i++) if (num1[i]!=num2[i]) return false;
	return true;
}

inline void Add(int cur,int len)
{
	int i;
	memset(num1,0,sizeof(num1));
	for (i=0;i<=len;i++) if (cur&(1<<i)) num1[i]=1;
	reverse(num1,num1+len+1);
	cur=0;
	for (i=0;i<=len;i++) if (num1[i]) cur|=(1<<i);
	ans.pb(cur);
}

int main ()
{
	int i;
	A=getint();B=getint();
	if (A>B) swap(A,B);
	if (issuf(A,B))
	{
		printf("-1\n");
		return 0;
	}
	ans.pb(A);ans.pb(B);
	danger.clear();
	int cur=0,len;
	for (i=0;i<=len1;i++) 
	{
		if (num1[i]) cur|=(1<<i);
		danger[mp(cur,i)]=true;
	}
	cur=0;
	for (i=0;i<=len2;i++)
	{
		if (num2[i]) cur|=(1<<i);
		danger[mp(cur,i)]=true;
	}
	A=0;for (i=0;i<=len1;i++) if (num1[i]) A|=(1<<i);
	B=0;for (i=0;i<=len2;i++) if (num2[i]) B|=(1<<i);
	q.push(mp(1,0));
	while (!q.empty())
	{
		cur=q.front().x;len=q.front().y;q.pop();
		if (!danger[mp(cur,len)])
		{
			Add(cur,len);
		}
		else
		{
			if (!(len==len1 && cur==A) && !(len==len2 && cur==B))
			{
				q.push(mp(cur,len+1));
				q.push(mp(cur|(1<<(len+1)),len+1));
			}
		}
	}
	sort(ans.begin(),ans.end());
	for (i=0;i<ans.size();i++) printf("%d ",ans[i]);
	printf("\n");
	return 0;
}

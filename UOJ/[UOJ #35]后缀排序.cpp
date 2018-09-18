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

char s[100048];int len,k;
int sa[100048],rnk[100048],tmp[100048],lcp[100048];

inline bool compare_sa(int x,int y)
{
	if (rnk[x]!=rnk[y]) return rnk[x]<rnk[y];
	int tmp1=(x+k<=len?rnk[x+k]:-1),tmp2=(y+k<=len?rnk[y+k]:-1);
	return tmp1<tmp2;
}

inline void construct_sa()
{
	int i;
	for (i=1;i<=len;i++) sa[i]=i,rnk[i]=s[i];
	for (k=0;k<=len;k==0?k++:k<<=1)
	{
		sort(sa+1,sa+len+1,compare_sa);
		tmp[sa[1]]=1;int cnt=0;
		for (i=2;i<=len;i++)
		{
			tmp[sa[i]]=tmp[sa[i-1]]+(compare_sa(sa[i-1],sa[i])?1:0);
			cnt+=(tmp[sa[i-1]]!=tmp[sa[i]]);
		}
		for (i=1;i<=len;i++) rnk[i]=tmp[i];
		if (cnt>=len-1) break;
	}
}

inline void construct_lcp()
{
	int i,j,h=0;
	for (i=1;i<=len;i++) rnk[sa[i]]=i;
	for (i=1;i<=len;i++)
	{
		j=sa[rnk[i]-1];
		if (h) h--;
		while (i+h<=len && j+h<=len && s[i+h]==s[j+h]) h++;
		lcp[rnk[i]-1]=h;
	}
}

int main ()
{
	scanf("%s",s+1);len=strlen(s+1);
	construct_sa();construct_lcp();
	for (register int i=1;i<=len;i++) printf("%d ",sa[i]);printf("\n");
	for (register int i=1;i<=len-1;i++) printf("%d ",lcp[i]);printf("\n");
	return 0;
}

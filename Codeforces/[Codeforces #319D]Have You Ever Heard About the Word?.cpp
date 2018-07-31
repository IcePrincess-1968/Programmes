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

const int MOD=10007;
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

char s[50048];int len;
char tmp[50048];int pt,tot;

const LL p1=998244353,p2=19260817;
const LL m1=1e9+7,m2=1e9+9;

LL pw1[50048],pw2[50048],hsh1[50048],hsh2[50048];
inline LL mod1(LL x) {while (x>=m1) x-=m1;while (x<0) x+=m1;return x;}
inline LL mod2(LL x) {while (x>=m2) x-=m2;while (x<0) x+=m2;return x;}
inline LL gethash1(int left,int right) {return mod1(hsh1[right]-(hsh1[left-1]*pw1[right-left+1])%m1);}
inline LL gethash2(int left,int right) {return mod2(hsh2[right]-(hsh2[left-1]*pw2[right-left+1])%m2);}

inline void init_pw()
{
	pw1[0]=pw2[0]=1;
	for (register int i=1;i<=len;i++) pw1[i]=(pw1[i-1]*p1)%m1,pw2[i]=(pw2[i-1]*p2)%m2;
}

inline void init()
{
	hsh1[0]=hsh2[0]=0;
	for (register int i=1;i<=len;i++) hsh1[i]=(hsh1[i-1]*p1+s[i])%m1,hsh2[i]=(hsh2[i-1]*p2+s[i])%m2;
}

inline int query_lcp(int pos1,int pos2)
{
	int l=1,r=len,mid,res=0;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (pos2+mid-1<=len && gethash1(pos1,pos1+mid-1)==gethash1(pos2,pos2+mid-1) && gethash2(pos1,pos1+mid-1)==gethash2(pos2,pos2+mid-1))
			res=mid,l=mid+1;
		else
			r=mid-1;
	}
	return res;
}

inline int query_lcs(int pos1,int pos2)
{
	int l=1,r=len,mid,res=0;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (pos1-mid+1>=1 && gethash1(pos1-mid+1,pos1)==gethash1(pos2-mid+1,pos2) && gethash2(pos1-mid+1,pos1)==gethash2(pos2-mid+1,pos2))
			res=mid,l=mid+1;
		else
			r=mid-1;
	}
	return res;
}

inline bool exist(int curlen)
{
	int i;
	for (i=1;i<=len;i+=curlen/2)
		if (i+curlen/2<=len && query_lcp(i,i+curlen/2)+query_lcs(i,i+curlen/2)>=curlen/2) return true;
	return false;
}

int main ()
{
	scanf("%s",s+1);len=strlen(s+1);int i,curlen;
	init_pw();init();
	for (curlen=2;curlen<=len;curlen+=2)
	{
		if (!exist(curlen)) continue;
		pt=1;tot=curlen/2;hsh1[0]=hsh2[0]=0;int sl=0;
		for (i=1;i<=curlen/2;i++) tmp[i]=s[i];
		for (i=curlen/2+1;i<=len;i++)
		{
			tmp[++tot]=s[i];if (tmp[tot]==tmp[tot-curlen/2]) sl++; else sl=0;
			if (sl==curlen/2) tot-=curlen/2,sl=0;
		}
		for (i=curlen/2+1;i<=tot;i++) s[i]=tmp[i];
		len=tot;
		init();
	}
	for (i=1;i<=len;i++) printf("%c",s[i]);
	puts("");
	return 0;
}

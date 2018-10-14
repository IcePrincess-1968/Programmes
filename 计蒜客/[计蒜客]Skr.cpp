#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

struct fastio
{
	static const int S=1e7;
	char rbuf[S+48],wbuf[S+48];int rpos,wpos,len;
	fastio() {rpos=len=wpos=0;}
	inline char Getchar()
	{
		if (rpos==len) rpos=0,len=fread(rbuf,1,S,stdin);
		if (!len) return EOF;
		return rbuf[rpos++];
	}
	template <class T> inline void Get(T &x)
	{
		char ch;bool f;T res;
		while (!isdigit(ch=Getchar()) && ch!='-') {}
		if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
		while (isdigit(ch=Getchar())) res=res*10+ch-'0';
		x=(f?res:-res);
	}
	inline void getstring(char *s)
	{
		char ch;
		while ((ch=Getchar())<=32) {}
		for (;ch>32;ch=Getchar()) *s++=ch;
		*s='\0';
	}
	inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
	inline void Writechar(char ch)
	{
		if (wpos==S) flush();
		wbuf[wpos++]=ch;
	}
	template <class T> inline void Print(T x,char ch)
	{
		char s[20];int pt=0;
		if (x==0) s[++pt]='0';
		else
		{
			if (x<0) Writechar('-'),x=-x;
			while (x) s[++pt]='0'+x%10,x/=10;
		}
		while (pt) Writechar(s[pt--]);
		Writechar(ch);
	}
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

const int MAXN=2e6;

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

int Val[MAXN+48];

char s[MAXN+48];int len;
int ans;

namespace PanTree
{
	struct node
	{
		int nxt[11];
		int len,fail,val;
	}tree[MAXN*2];int tot,last;
	inline void init()
	{
		tree[0].fail=1;tree[1].len=-1;tot=1;last=0;
	}
	inline void insert(int pos)
	{
		int w=s[pos]-'0';
		while (s[pos-tree[last].len-1]!=s[pos]) last=tree[last].fail;
		if (!tree[last].nxt[w])
		{
			++tot;
			tree[tot].len=tree[last].len+2;
			if (tree[tot].len==1)
				tree[tot].val=w;
			else
				tree[tot].val=add(add(1ll*tree[last].val*10%MOD+1ll*w*Val[tree[tot].len]%MOD)+w);
			ans=add(ans+tree[tot].val);
			int tmp=tree[last].fail;
			while (s[pos-tree[tmp].len-1]!=s[pos]) tmp=tree[tmp].fail;
			tree[tot].fail=tree[tmp].nxt[w];
			tree[last].nxt[w]=tot;
			last=tot;
		}
		else
			last=tree[last].nxt[w];
	}
}

int main ()
{
	Val[1]=1;
	for (register int i=2;i<=MAXN;i++) Val[i]=(1ll*Val[i-1]*10)%MOD;
	io.getstring(s+1);len=strlen(s+1);s[0]='$';
	PanTree::init();
	for (register int i=1;i<=len;i++) PanTree::insert(i);
	io.Print(ans,'\n');
	io.flush();return 0;
}

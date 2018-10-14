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
const int MOD=998244353;
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
	/*inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}*/
	inline void printstring(string s)
	{
		int len=int(s.size());
		for (register int i=0;i<len;i++) Writechar(s[i]);
	}
}io;

const int MAXN=4e5;

int n,m,pt;
int card[MAXN+48];

int hand[248][48],cnt[248];
int table[256];

inline void getcard(int ind)
{
	if (pt<=m) hand[ind][table[card[pt]]]++,pt++,cnt[ind]++;
}

inline int putcard(int ind,int last)
{
	if (last==-1)
	{
		for (register int i=1;i<=13;i++)
			if (hand[ind][i]) {hand[ind][i]--;cnt[ind]--;return i;}
	}
	if (last==13) return -1;
	if (hand[ind][last+1]) {hand[ind][last+1]--;cnt[ind]--;return last+1;}
	if (hand[ind][13]) {hand[ind][13]--;cnt[ind]--;return 13;}
	return -1;
}

inline int calc(int ind)
{
	int res=0;
	for (register int i=1;i<=11;i++) res+=hand[ind][i]*(i+2);
	res+=hand[ind][12];res+=hand[ind][13]*2;
	return res;
}

int main ()
{
	int ca;io.Get(ca);int cc=0;
	for (register int i=3;i<=13;i++) table[i]=i-2;
	table[1]=12;table[2]=13;
	while (ca--)
	{
		io.Get(n);io.Get(m);
		for (register int i=1;i<=m;i++) io.Get(card[i]);
		memset(hand,0,sizeof(hand));memset(cnt,0,sizeof(cnt));
		pt=1;
		for (register int i=1;i<=n;i++)
			for (register int j=1;j<=5;j++)
				getcard(i);
		int cur=1,last=-1,lastpos=0;
		for (;;)
		{
			if (cur==lastpos)
			{
				if (pt<=m)
				{
					getcard(cur);
					for (register int i=cur%n+1;i!=cur;i=i%n+1) getcard(i);
				}
				last=-1;
			}
			int res=putcard(cur,last);
			if (res!=-1) last=res,lastpos=cur;
			if (!cnt[cur]) break;
			cur=cur%n+1;
		}
		io.printstring("Case #");io.Print(++cc,':');io.Writechar('\n');
		for (register int i=1;i<=n;i++)
			if (!cnt[i])
			{
				io.printstring("Winner");
				io.Writechar('\n');
			}
			else
			{
				io.Print(calc(i),'\n');
			}
	}
	io.flush();return 0;
}

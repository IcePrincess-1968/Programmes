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
#define LOCAL true

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

const int MAXN=50;

int n,m;
int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
int Mp[MAXN+48][MAXN+48];
bool visited[MAXN+48][MAXN+48];

struct Fragment
{
	int depth[2];int type[2];
}L[MAXN+48],R[MAXN+48],cross[MAXN+48];
int lnum,rnum,cnum;

class Tunnels
{
	inline bool allx(int id) {for (register int j=1;j<=m;j++) if (!Mp[id][j]) return false;return true;}
	inline Pair find_ed(int x,int y)
	{
		visited[x][y]=true;
		for (register int dir=0;dir<4;dir++)
	}
	public:
		inline int minimumTunnels(vector<string> Map)
		{
			n=int(Map.size());m=int(Map[0].size());
			for (register int i=1;i<=n;i++)
				for (register int j=1;j<=m;j++)
					Mp[i][j]=(Map[i-1][j-1]=='X');
			for (register int i=1;i<=n;i++)
				if (allx(i))
				{
					cnum++;int rr;
					for (rr=i;rr>=1 && Mp[rr][1];visited[rr--][1]=true);rr++;
					if (rr<i) cross[cnum].type[0]=0,cross[cnum].depth[0]=rr;
					else
					{
						for (rr=i;rr<=n && Mp[rr][1];visited[rr++][1]=true);rr--;
						if (rr>i) cross[cnum].type[0]=1,cross[cnum].depth[0]=rr;
						else cross[cnum].type[0]=2,cross[cnum].depth[0]=i;
					}
					for (rr=i;rr>=1 && Mp[rr][m];visited[rr--][m]=true);rr++;
					if (rr<i) cross[cnum].type[1]=0;cross[cnum].depth[1]=rr;
					else
					{
						for (rr=i;rr<=n && Mp[rr][m];visited[rr++][m]=true);rr--;
						if (rr>i) cross[cnum].type[1]=1,cross[cnum].depth[1]=rr;
						else cross[cnum].type[1]=2,cross[cnum].depth[1]=i;
					}
				}
			for (register int i=1;i<=n;i++)
				if (Mp[i][1] && !visited[i][1])
				{
					Pair ed=find_ed(i,1);
		}
};

#ifdef LOCAL
int main ()
{
#ifdef LOCAL
	double t=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	int nn;vector<string> ss;string s;
	Tunnels A;
	while (cin>>nn)
	{
		ss.clear();
		for (register int i=1;i<=n;i++) cin>>s,ss.pb(s);
		cout<<A.minimumTunnels(ss)<<endl;
	}
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-t)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
#endif
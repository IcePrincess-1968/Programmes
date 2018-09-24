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
#define LOWBIT(x) x & (-x)
// #define LOCAL true

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
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

template <typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template <typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template <typename T> inline T myabs(T x) {return x>=0?x:-x;}

int n,m,w;

Pair ball[48],hole[48];
int holeind[48][48];
bool rwall[48][48],cwall[48][48];

inline int getind(int x,int y) {return (x-1)*n+y;}
inline int Get(ull Mask,int pos) {return Mask>>((pos-1)<<2)&15;}
inline void Set(ull &Mask,int pos,int nv) {Mask&=(Mask^((ull)15<<((pos-1)<<2)));Mask|=((ull)nv<<((pos-1)<<2));}
inline bool isball(int x) {return 1<=x && x<=8;}

map<ull,int> Mp;

int a[48][48];
bool superf;

inline void getmap(ull Mask)
{
	for (register int i=1;i<=n;i++)
		for (register int j=1;j<=n;j++)
			a[i][j]=Get(Mask,getind(i,j));
}

inline ull getMask()
{
	ull Mask=0;
	for (register int i=1;i<=n;i++)
		for (register int j=1;j<=n;j++)
			Set(Mask,getind(i,j),a[i][j]);
	return Mask;
}

inline Pair toleft(int x,int y) {if (y==1 || a[x][y]==9 || cwall[x][y-1] || isball(a[x][y-1])) return mp(x,y);return toleft(x,y-1);}
inline Pair toright(int x,int y) {if (y==n || a[x][y]==9 || cwall[x][y] || isball(a[x][y+1])) return mp(x,y);return toright(x,y+1);}
inline Pair toup(int x,int y) {if (x==1 || a[x][y]==9 || rwall[x-1][y] || isball(a[x-1][y])) return mp(x,y);return toup(x-1,y);}
inline Pair todown(int x,int y) {if (x==n || a[x][y]==9 || rwall[x][y] || isball(a[x+1][y])) return mp(x,y);return todown(x+1,y);}

inline ull getleft(ull Mask)
{
	getmap(Mask);
	for (register int i=1;i<=n;i++)
		for (register int j=1;j<=n;j++)
			if (1<=a[i][j] && a[i][j]<=8)
			{
				Pair pos=toleft(i,j);int ind=a[i][j];a[i][j]=0;
				if (a[pos.x][pos.y]==9 && ind!=holeind[pos.x][pos.y]) {superf=false;return 0;}
				if (a[pos.x][pos.y]==9) a[pos.x][pos.y]=0; else a[pos.x][pos.y]=ind;
			}
	return getMask();
}

inline ull getright(ull Mask)
{
	getmap(Mask);
	for (register int i=1;i<=n;i++)
		for (register int j=n;j>=1;j--)
			if (1<=a[i][j] && a[i][j]<=8)
			{
				Pair pos=toright(i,j);int ind=a[i][j];a[i][j]=0;
				if (a[pos.x][pos.y]==9 && ind!=holeind[pos.x][pos.y]) {superf=false;return 0;}
				if (a[pos.x][pos.y]==9) a[pos.x][pos.y]=0; else a[pos.x][pos.y]=ind;
			}
	return getMask();
}

inline ull getup(ull Mask)
{
	getmap(Mask);
	for (register int j=1;j<=n;j++)
		for (register int i=1;i<=n;i++)
			if (1<=a[i][j] && a[i][j]<=8)
			{
				Pair pos=toup(i,j);int ind=a[i][j];a[i][j]=0;
				if (a[pos.x][pos.y]==9 && ind!=holeind[pos.x][pos.y]) {superf=false;return 0;}
				if (a[pos.x][pos.y]==9) a[pos.x][pos.y]=0; else a[pos.x][pos.y]=ind;
			}
	return getMask();
}

inline ull getdown(ull Mask)
{
	getmap(Mask);
	for (register int j=1;j<=n;j++)
		for (register int i=n;i>=1;i--)
			if (1<=a[i][j] && a[i][j]<=8)
			{
				Pair pos=todown(i,j);int ind=a[i][j];a[i][j]=0;
				if (a[pos.x][pos.y]==9 && ind!=holeind[pos.x][pos.y]) {superf=false;return 0;}
				if (a[pos.x][pos.y]==9) a[pos.x][pos.y]=0; else a[pos.x][pos.y]=ind;
			}
	return getMask();
}

ull q[10000048];int head,tail;

inline int solve(ull Mask)
{
	head=1;tail=2;q[1]=Mask;q[2]=0;
	Mp[Mask]=0;int step;ull toMask;
	while (head<=tail)
	{
		Mask=q[head++];step=q[head++];
		if (Mask==0) return step;
		superf=true;toMask=getleft(Mask);if (superf && Mp.find(toMask)==Mp.end()) Mp[toMask]=step+1,q[++tail]=toMask,q[++tail]=step+1;
		superf=true;toMask=getright(Mask);if (superf && Mp.find(toMask)==Mp.end()) Mp[toMask]=step+1,q[++tail]=toMask,q[++tail]=step+1;
		superf=true;toMask=getup(Mask);if (superf && Mp.find(toMask)==Mp.end()) Mp[toMask]=step+1,q[++tail]=toMask,q[++tail]=step+1;
		superf=true;toMask=getdown(Mask);if (superf && Mp.find(toMask)==Mp.end()) Mp[toMask]=step+1,q[++tail]=toMask,q[++tail]=step+1;
	}
	return INF;
}

inline void Clear()
{
	memset(rwall,false,sizeof(rwall));
	memset(cwall,false,sizeof(cwall));
	memset(holeind,0,sizeof(holeind));
	Mp.clear();
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	int cnt=0,x1,y1,x2,y2;
	while (scanf("%d%d%d",&n,&m,&w) && m)
	{
		Clear();
		for (register int i=1;i<=m;i++) scanf("%d%d",&ball[i].x,&ball[i].y),ball[i].x++,ball[i].y++;
		for (register int i=1;i<=m;i++) scanf("%d%d",&hole[i].x,&hole[i].y),hole[i].x++,hole[i].y++,holeind[hole[i].x][hole[i].y]=i;
		for (register int i=1;i<=w;i++)
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);x1++;y1++;x2++;y2++;
			if (x1==x2) cwall[x1][min(y1,y2)]=true; else rwall[min(x1,x2)][y1]=true;
		}
		ull st=0;
		for (register int i=1;i<=m;i++) Set(st,getind(ball[i].x,ball[i].y),i);
		for (register int i=1;i<=m;i++) Set(st,getind(hole[i].x,hole[i].y),9);
		printf("Case %d: ",++cnt);
		int ans=solve(st);
		if (ans>=INF) printf("impossible\n"); else printf("%d moves\n",ans);
		printf("\n");
	}
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
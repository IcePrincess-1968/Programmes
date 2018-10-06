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

template<typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template<typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template<typename T> inline T myabs(T x) {return x>=0?x:-x;}
template<typename T> inline T gcd(T x,T y) {return y==0?x:gcd(y,x%y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int add(int x,int MO) {if (x>=MO) x-=MO;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline int sub(int x,int MO) {if (x<0) x+=MO;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Add(int &x,int y,int MO) {x=add(x+y,MO);}
inline void Sub(int &x,int y) {x=sub(x-y);}
inline void Sub(int &x,int y,int MO) {x=sub(x-y,MO);}
inline int quick_pow(int x,int y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
inline int quick_pow(int x,int y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

struct Matrix
{
	int b[4][4];
	Matrix () {memset(b,0,sizeof(b));}
	inline void clear() {memset(b,0,sizeof(b));}
	inline Matrix (int x,int y,int z) {memset(b,0,sizeof(b));b[1][1]=x;b[1][2]=y;b[1][3]=z;}
	inline void init_I() {for (register int i=1;i<=3;i++) b[i][i]=1;}
	inline bool operator < (const Matrix &other) const
	{
		if (b[1][3]!=other.b[1][3]) return b[1][3]<other.b[1][3];
		if (b[1][1]!=other.b[1][1]) return b[1][1]<other.b[1][1];
		return b[1][2]<other.b[1][2];
	}
	inline bool operator == (const Matrix &other) const
	{
		for (register int i=1;i<=3;i++)
			for (register int j=1;j<=3;j++)
				if (b[i][j]!=other.b[i][j]) return false;
		return true;
	}
	inline Matrix operator + (Matrix ma)
	{
		Matrix res;res.clear();
		for (register int i=1;i<=3;i++)
			for (register int j=1;j<=3;j++)
				res.b[i][j]=b[i][j]+ma.b[i][j];
		return res;
	}
	inline Matrix operator - (Matrix ma)
	{
		Matrix res;res.clear();
		for (register int i=1;i<=3;i++)
			for (register int j=1;j<=3;j++)
				res.b[i][j]=b[i][j]-ma.b[i][j];
		return res;
	}
	inline Matrix operator * (Matrix ma)
	{
		Matrix res;res.clear();
		for (register int i=1;i<=3;i++)
			for (register int j=1;j<=3;j++)
				for (register int k=1;k<=3;k++)
					res.b[i][j]+=b[i][k]*ma.b[k][j];
		return res;
	}
	inline void print() {cerr<<b[1][1]<<','<<b[1][2]<<','<<b[1][3]<<endl;}
}rx,ry,rz;

inline Matrix quick_pow(Matrix x,int y)
{
	Matrix res;res.clear();res.init_I();
	while (y)
	{
		if (y&1) res=res*x;
		x=x*x;y>>=1;
	}
	return res;
}


typedef pair<int,pair<int,int> > P;
typedef vector<Matrix> soma;

inline bool operator < (const P &x,const P &y)
{
	if (x.y.y!=y.y.y) return x.y.y<y.y.y;
	if (x.x!=y.x) return x.x<y.x;
	return x.y.x<y.y.x;
}

inline P Matrix_to_P(Matrix ma) {return mp(ma.b[1][1],mp(ma.b[1][2],ma.b[1][3]));}

soma base[48];
vector<soma> candidate[48];

inline soma Move(soma ori,Matrix pos,P topos)
{
	Matrix delta;delta.clear();
	for (register int i=1;i<=3;i++) delta.b[1][i]=-pos.b[1][i];
	delta.b[1][1]+=topos.x;delta.b[1][2]+=topos.y.x;delta.b[1][3]+=topos.y.y;
	for (register int i=0;i<int(ori.size());i++) ori[i]=ori[i]+delta;
	return ori;
}

inline soma getsoma(soma ori,int dx,int dy,int dz)
{
	for (register int k=0;k<int(ori.size());k++)
	for (register int i=2;i<=3;i++)
		for (register int j=1;j<=3;j++)
			assert(ori[k].b[i][j]==0);
	for (register int i=0;i<int(ori.size());i++)
	{
		ori[i]=ori[i]*quick_pow(rx,dx);
		ori[i]=ori[i]*quick_pow(ry,dy);
		ori[i]=ori[i]*quick_pow(rz,dz);
	}
	sort(ori.begin(),ori.end());
	return ori;
}

inline bool issame(soma x,soma y)
{
	Matrix cmp=x[0]-y[0];
	/*for (register int i=2;i<=3;i++)
		for (register int j=1;j<=3;j++)
			assert(cmp.b[i][j]==0);
	*/
	for (register int i=1;i<int(x.size());i++)
		if (!(x[i]-y[i]==cmp)) return false;
	return true;
}

inline void init_soma()
{
	for (register int i=1;i<=7;i++) base[i].clear(),candidate[i].clear();
	
	base[1].pb(Matrix(1,1,1));base[1].pb(Matrix(2,1,1));base[1].pb(Matrix(3,1,1));base[1].pb(Matrix(1,2,1));
	base[2].pb(Matrix(1,1,1));base[2].pb(Matrix(2,1,1));base[2].pb(Matrix(3,1,1));base[2].pb(Matrix(2,2,1));
	base[3].pb(Matrix(2,1,1));base[3].pb(Matrix(3,1,1));base[3].pb(Matrix(1,2,1));base[3].pb(Matrix(2,2,1));
	base[4].pb(Matrix(1,1,1));base[4].pb(Matrix(2,1,1));base[4].pb(Matrix(1,2,1));
	base[5].pb(Matrix(2,1,1));base[5].pb(Matrix(2,1,2));base[5].pb(Matrix(1,2,1));base[5].pb(Matrix(2,2,1));
	base[6].pb(Matrix(1,1,1));base[6].pb(Matrix(1,1,2));base[6].pb(Matrix(1,2,1));base[6].pb(Matrix(2,2,1));
	base[7].pb(Matrix(1,1,1));base[7].pb(Matrix(2,1,1));base[7].pb(Matrix(2,1,2));base[7].pb(Matrix(2,2,1));

	rx.clear();ry.clear();rz.clear();
	rx.b[1][1]=1;rx.b[2][3]=1;rx.b[3][2]=-1;
	ry.b[1][3]=-1;ry.b[2][2]=1;ry.b[3][1]=1;
	rz.b[1][2]=1;rz.b[2][1]=-1;rz.b[3][3]=1;
	
	for (register int i=1;i<=7;i++) sort(base[i].begin(),base[i].end());
	for (register int i=1;i<=7;i++)
		for (register int dx=0;dx<=3;dx++)
			for (register int dy=0;dy<=3;dy++)
				for (register int dz=0;dz<=3;dz++)
				{
					soma ns=getsoma(base[i],dx,dy,dz);bool f=true;
					for (register int j=0;j<int(candidate[i].size());j++)
						if (issame(candidate[i][j],ns)) {f=false;break;}
					if (f) candidate[i].pb(ns);
				}
}

set<P> ss;
int dx[]={0,1,0,-1,0,0},dy[]={-1,0,1,0,0,0},dz[]={0,0,0,0,1,-1};

inline int dfs(P cur)
{
	int res=1,x,y,z;
	ss.erase(cur);
	for (register int dir=0;dir<=5;dir++)
	{
		x=cur.x+dx[dir];y=cur.y.x+dy[dir];z=cur.y.y+dz[dir];
		if (ss.find(mp(x,mp(y,z)))!=ss.end()) res+=dfs(mp(x,mp(y,z)));
	}
	return res;
}

inline bool check_valid(set<P> s,bool three)
{	
	ss=s;int ccc=0;
	while (!ss.empty())
	{
		int cnt=dfs(*ss.begin());
		if (cnt<3) return false;
		if (!three && cnt%4) return false;
		if (three && cnt%4!=0 && cnt%4!=3) return false;
		if (cnt%4==3) ccc++;
		if (ccc>1) return false;
		// cerr<<cnt<<endl;
	}
	return true;
}

class Soma
{
	int n,m,ans;
	int a[48][48];
	inline int dfs(set<P> s,vector<bool> used)
	{
		//int res=MMp[mp(s,used)];
		//if (res) return res;
		//cerr<<s.size()<<endl;
		//for (register int i=1;i<=7;i++) cerr<<used[i]<<' ';
		//cerr<<endl;
		int res=0;
		if (s.empty()) {return 1;}
		//P pos=(*s.begin());
		P pos;pos.y.y=INF;
		for (set<P>::iterator iter=s.begin();iter!=s.end();iter++)
			if (iter->y.y<pos.y.y) pos=(*iter);
		for (register int i=1;i<=7;i++)
			if (!used[i])
			{
				for (register int j=0;j<int(candidate[i].size());j++)
					for (register int k=0;k<int(candidate[i][j].size());k++)
					{
						soma cur=Move(candidate[i][j],candidate[i][j][k],pos);
						bool valid=true;
						for (register int p=0;p<int(cur.size());p++)
							if (s.find(Matrix_to_P(cur[p]))==s.end()) {valid=false;break;}
						if (valid)
						{
							for (register int p=0;p<int(cur.size());p++)
								s.erase(Matrix_to_P(cur[p]));
							used[i]=true;
							if (check_valid(s,~used[4])) res+=dfs(s,used);
							for (register int p=0;p<int(cur.size());p++)
								s.insert(Matrix_to_P(cur[p]));
							used[i]=false;
						}
					}
			}
		return res;
	}
	public:
		inline int letMeCountTheWays(vector<string> pattern)
		{
			double T=clock();
			n=int(pattern.size());m=int(pattern[0].size());
			for (register int i=1;i<=n;i++)
				for (register int j=1;j<=m;j++)
					a[i][j]=pattern[i-1][j-1]-'0';
			init_soma();
			vector<bool> used;used.clear();used.resize(10);
			for (register int i=1;i<=7;i++) used[i]=false;
			set<P> s;
			for (register int i=1;i<=n;i++)
				for (register int j=1;j<=m;j++)
					if (a[i][j])
						for (register int k=1;k<=a[i][j];k++)
							s.insert(mp(i,mp(j,k)));
			// for (set<P>::iterator iter=s.begin();iter!=s.end();iter++)
				// cerr<<iter->x<<' '<<iter->y.x<<' '<<iter->y.y<<endl;
			int aa=dfs(s,used);
			cerr<<"TIME:"<<(clock()-T)/CLOCKS_PER_SEC<<endl;
			return aa;
		}
};

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	int nn;vector<string> vv;string ss;
	Soma A;
	while (cin>>nn)
	{
		vv.clear();
		for (register int i=1;i<=nn;i++) cin>>ss,vv.pb(ss);
		cout<<A.letMeCountTheWays(vv)<<endl;
	}
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
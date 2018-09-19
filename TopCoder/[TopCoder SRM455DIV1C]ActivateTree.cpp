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

template <typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template <typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}

vector<int> v[48];
vector<int> valid[48][10];bool visited[48][10][48];
int ind[48][48],itot;
int cost[48],type[48];
int dp[48][100048],need[48];

class ActivateTree
{
	int n,m;
	inline void doit_target(string s)
	{	
		int len=int(s.size()),pt;
		pt=0;bool f;int num,cnt=0;n=0;
		do
		{
			while (pt<=len-1 && s[pt]==' ') pt++;
			if (pt>=len) break;
			if (s[pt]=='-') f=false,num=0; else f=true,num=s[pt]-'0';
			pt++;cnt++;
			while (pt<=len-1 && isdigit(s[pt])) num=num*10+s[pt]-'0',pt++;
			if (!f) num=-num;
			num++;if (f) v[num].pb(cnt);
		}
		while (pt<=len-1);
		n=cnt;
		itot=0;
		for (register int i=1;i<=n;i++)
			for (register int j=0;j<int(v[i].size());j++)
				ind[i][v[i][j]]=++itot;
	}
	int depth[10],fa[10],cc[10];
	inline int solve(int x) {if (depth[x]!=-1) return depth[x]; else return depth[x]=solve(fa[x])+1;}
	inline int judge_type()
	{
		if (cc[2]==1 && cc[3]==0 && cc[4]==0) return 1;
		if (cc[2]==1 && cc[3]==1 && cc[4]==0) return 2;
		if (cc[2]==2 && cc[3]==0 && cc[4]==0) return 3;
		if (cc[2]==1 && cc[3]==1 && cc[4]==1) return 4;
		if (cc[2]==2 && cc[3]==1 && cc[4]==0) return 5;
		if (cc[2]==1 && cc[3]==2 && cc[4]==0) return 6;
		if (cc[2]==3) return 7;
		return -1;
	}
	inline void doit_tree(string s,int id)
	{
		memset(depth,-1,sizeof(depth));
		int pt=0,len=int(s.size());int num,cnt=0;bool f;
		memset(cc,0,sizeof(cc));
		do
		{
			while (pt<=len-1 && s[pt]==' ') pt++;
			if (pt>=len) break;
			if (s[pt]=='-') f=false,num=0; else f=true,num=s[pt]-'0';
			pt++;cnt++;
			while (pt<=len-1 && isdigit(s[pt])) num=num*10+s[pt]-'0',pt++;
			if (!f) num=-num;
			num++;fa[cnt]=num;
		}
		while (pt<=len-1);
		depth[0]=0;for (register int i=1;i<=cnt;i++) depth[i]=solve(i),cc[depth[i]]++;
		for (register int i=1;i<=cnt;i++) cerr<<depth[i]<<' ';
		cerr<<endl;
		type[id]=judge_type();
	}
	inline void doit_valid(int x)
	{
		//type 1
		for (register int i=0;i<int(v[x].size());i++) valid[x][1].pb(1<<(ind[x][v[x][i]]-1));
		//type 2
		for (register int i=0;i<int(v[x].size());i++)
		{
			register int y=v[x][i];
			for (register int j=0;j<int(v[y].size());j++)
			{
				register int z=v[y][j];
				valid[x][2].pb((1<<(ind[x][y]-1))|(1<<(ind[y][z]-1)));
			}
		}
		//type 3
		for (register int i=0;i<int(v[x].size())-1;i++)
			for (register int j=i+1;j<int(v[x].size());j++)
			{
				register int y=v[x][i],z=v[x][j];
				valid[x][3].pb((1<<(ind[x][y]-1))|(1<<(ind[x][z]-1)));
			}
		//type 4
		for (register int i=0;i<int(v[x].size());i++)
		{
			register int y=v[x][i];
			for (register int j=0;j<int(v[y].size());j++)
			{
				register int z=v[y][j];
				for (register int k=0;k<int(v[z].size());k++)
				{
					register int zz=v[z][k];
					valid[x][4].pb((1<<(ind[x][y]-1))|(1<<(ind[y][z]-1))|(1<<(ind[z][zz]-1)));
				}
			}
		}
		//type 5
		for (register int i=0;i<int(v[x].size())-1;i++)
			for (register int j=i+1;j<int(v[x].size());j++)
			{
				register int y=v[x][i],z=v[x][j];
				for (register int k=0;k<int(v[y].size());k++)
				{
					register int zz=v[y][k];
					valid[x][5].pb((1<<(ind[x][y]-1))|(1<<(ind[x][z]-1))|(1<<(ind[y][zz]-1)));
				}
				for (register int k=0;k<int(v[z].size());k++)
				{
					register int zz=v[z][k];
					valid[x][5].pb((1<<(ind[x][y]-1))|(1<<(ind[x][z]-1))|(1<<(ind[z][zz]-1)));
				}
			}
		//type 6
		for (register int i=0;i<int(v[x].size());i++)
		{
			register int y=v[x][i];
			for (register int j=0;j<int(v[y].size())-1;j++)
				for (register int k=j+1;k<int(v[y].size());k++)
				{
					register int z=v[y][j],zz=v[y][k];
					valid[x][6].pb((1<<(ind[x][y]-1))|(1<<(ind[y][z]-1))|(1<<(ind[y][zz]-1)));
				}
		}
		//type 7
		for (register int i=0;i<int(v[x].size())-2;i++)
			for (register int j=i+1;j<int(v[x].size())-1;j++)
				for (register int k=j+1;k<int(v[x].size());k++)
				{
					register int y=v[x][i],z=v[x][j],zz=v[x][k];
					valid[x][7].pb((1<<(ind[x][y]-1))|(1<<(ind[x][z]-1))|(1<<(ind[x][zz]-1)));
				}
	}
	int q[48],head,tail,seq[48];
	inline void bfs()
	{
		head=tail=1;q[1]=1;int pt=0;
		while (head<=tail)
		{
			register int x=q[head++];seq[++pt]=x;
			for (register int i=0;i<int(v[x].size());i++) q[++tail]=v[x][i];
		}
	}
	inline void dfs(int cur,int i,int curMask,int val)
	{
		if (cur==m+1) {check_min(dp[i][curMask],val);return;}
		dfs(cur+1,i,curMask,val);
		for (register int j=0;j<int(valid[seq[i]][type[cur]].size());j++)
			if (!visited[seq[i]][type[cur]][j])
			{
				visited[seq[i]][type[cur]][j]=true;
				dfs(cur+1,i,curMask^valid[seq[i]][type[cur]][j],val+cost[cur]);
				visited[seq[i]][type[cur]][j]=false;
			}
	}
	inline void Clear()
	{
		for (register int i=1;i<=48;i++) v[i].clear();itot=0;
		for (register int i=1;i<=48;i++)
			for (register int j=1;j<=7;j++)
				valid[i][j].clear();
	}
	public:
		inline int minCost(vector<string> trees,string target,vector<int> Cost)
		{
			Clear();
			doit_target(target);
			m=int(Cost.size());
			for (register int i=1;i<=m;i++) cost[i]=Cost[i-1];
			for (register int i=1;i<=m;i++) doit_tree(trees[i-1],i);
			cerr<<type[1]<<"*"<<endl;
			cerr<<"----"<<endl;
			for (register int i=1;i<=n;i++) doit_valid(i);
			for (register int i=1;i<=7;i++)
				for (register int j=0;j<int(valid[1][i].size());j++)
					cerr<<i<<' '<<valid[1][i][j]<<endl;
			cerr<<"----"<<endl;
			for (register int i=1;i<=7;i++)
				for (register int j=0;j<int(valid[2][i].size());j++)
					cerr<<i<<' '<<valid[2][i][j]<<endl;
			cerr<<"----"<<endl;
			bfs();
			need[1]=0;
			for (register int i=2;i<=n;i++)
			{
				need[i]=need[i-1];
				for (register int j=0;j<int(v[seq[i-1]].size());j++)
				{
					register int y=v[seq[i-1]][j];
					need[i]|=(1<<(ind[seq[i-1]][y]-1));
				}
			}
			for (register int i=1;i<=4;i++) cerr<<need[i]<<"!!"<<endl;
			int full=(1<<(n-1))-1;
			cerr<<n<<"$"<<endl;
			for (register int i=0;i<=n;i++)
				for (register int Mask=0;Mask<=full;Mask++)
					dp[i][Mask]=INF;
			// for (register int i=1;i<=n;i++) cerr<<seq[i]<<' ';
			// cerr<<endl;
			dp[0][0]=0;
			for (register int i=1;i<=n;i++)
				for (register int Mask=0;Mask<=full;Mask++)
					if ((Mask&need[i])==need[i] && dp[i-1][Mask]<INF)
					{
						dfs(1,i,Mask,dp[i-1][Mask]);
						if (i==3 && Mask==3) cerr<<dp[i-1][Mask]<<"*()"<<endl;
					}
			if (dp[n][full]>=INF) return -1; else return dp[n][full];
		}
};

#ifdef LOCAL
int main ()
{
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	int nn;vector<string> ss;string s;string tt;vector<int> cc;int x;
	ActivateTree A;
	while (cin>>nn)
	{
		ss.clear();cc.clear();
		getchar();
		for (register int i=1;i<=nn;i++) getline(cin,s),ss.pb(s);
		for (register int i=1;i<=nn;i++) cin>>x,cc.pb(x);
		getchar();
		getline(cin,tt);
		cout<<A.minCost(ss,tt,cc)<<endl;
	}
	return 0;
}
#endif
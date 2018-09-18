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
const int INF=1e9;
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

struct Bigint
{
	int b[30],len;
	inline void clear() {memset(b,0,sizeof(b));len=1;}
	inline void read(int x) {clear();for (len=0;x;x/=1000) b[++len]=x%1000;if (!len) len=1;}
	inline void print()
	{
		for (register int i=len;i;i--)
		{
			if (i==len) {printf("%d",b[i]);continue;}
			int cnt=0,tt=100;
			while (b[i]<tt) cnt++,tt/=10;
			while (cnt--) printf("0");
			if (b[i]) printf("%d",b[i]);
		}
	}
	inline bool operator < (const Bigint &x) const
	{
		if (len!=x.len) return len<x.len;
		for (register int i=len;i>=1;i--)
			if (b[i]!=x.b[i]) return b[i]<x.b[i];
		return true;
	}
	inline bool operator > (const Bigint &x) const
	{
		if (len!=x.len) return len>x.len;
		for (register int i=len;i>=1;i--)
			if (b[i]!=x.b[i]) return b[i]>x.b[i];
		return true;
	}
	inline Bigint operator + (const Bigint x)
	{
		Bigint res;res.clear();
		for (register int i=1;i<=max(len,x.len);i++)
		{
			res.b[i]+=b[i]+x.b[i];
			res.b[i+1]+=res.b[i]/1000;res.b[i]%=1000;
		}
		res.len=max(len,x.len);if (res.b[res.len+1]) res.len++;
		return res;
	}
	inline Bigint operator * (const Bigint x)
	{
		Bigint res;res.clear();int i,j;
		for (i=1;i<=len;i++)
			for (j=1;j<=x.len;j++)
				res.b[i+j-1]+=b[i]*x.b[j];
		for (i=1;i<=len+x.len-1;i++) res.b[i+1]+=res.b[i]/1000,res.b[i]%=1000;
		res.len=len+x.len-1;if (res.b[res.len+1]) res.len++;
		return res;
	}
};

int n,m,k;
int a[10048];
Bigint pos[10048],neg[10048];int ptot,ntot;
Bigint res[71048];int rtot;

inline int myabs(int x) {return x>=0?x:-x;}
inline bool cmp_big(Bigint x,Bigint y) {return x>y;}
inline bool cmp_small(Bigint x,Bigint y) {return x<y;}

struct node_pos
{
	Bigint val;
	short pnum,nnum,npos[20],ppos[20];
	bool cur;int cpos;
	inline bool operator < (const node_pos &x) const {return val<x.val;}
};

priority_queue<node_pos> qpos;
inline void Getpos(short pnum,short nnum)
{
	int i,j,cnt;node_pos ins,cur;
	ins.pnum=pnum;ins.nnum=nnum;ins.val.clear();ins.val.b[1]=1;ins.val.len=1;
	for (i=1;i<=pnum;i++) ins.ppos[i]=i,ins.val=ins.val*pos[i];
	for (i=1;i<=nnum;i++) ins.npos[i]=i,ins.val=ins.val*neg[i];
	ins.cur=false;ins.cpos=pnum;
	while (!qpos.empty()) qpos.pop();
	qpos.push(ins);cnt=0;
	while (!qpos.empty() && cnt<k)
	{
		cur=qpos.top();qpos.pop();
		cnt++;res[++rtot]=cur.val;
		if (!cur.cur)
		{
			for (i=1;i<=cur.cpos;i++)
				if (cur.ppos[i]<ptot && (i==pnum || cur.ppos[i+1]!=cur.ppos[i]+1))
				{
					ins.cpos=i;ins.cur=false;
					for (j=1;j<=pnum;j++) ins.ppos[j]=cur.ppos[j];
					for (j=1;j<=nnum;j++) ins.npos[j]=cur.npos[j];
					ins.ppos[i]++;ins.val.clear();ins.val.len=1;ins.val.b[1]=1;
					for (j=1;j<=pnum;j++) ins.val=ins.val*pos[ins.ppos[j]];
					for (j=1;j<=nnum;j++) ins.val=ins.val*neg[ins.npos[j]];
					qpos.push(ins);
				}
			for (i=nnum;i<=nnum && i;i++)
				if (cur.npos[i]<ntot && (i==nnum || cur.npos[i+1]!=cur.npos[i]+1))
				{
					ins.cpos=i;ins.cur=true;
					for (j=1;j<=pnum;j++) ins.ppos[j]=cur.ppos[j];
					for (j=1;j<=nnum;j++) ins.npos[j]=cur.npos[j];
					ins.npos[i]++;ins.val.clear();ins.val.len=1;ins.val.b[1]=1;
					for (j=1;j<=pnum;j++) ins.val=ins.val*(pos[ins.ppos[j]]);
					for (j=1;j<=nnum;j++) ins.val=ins.val*(neg[ins.npos[j]]);
					qpos.push(ins);
				}
		}
		else
		{
			for (i=1;i<=cur.cpos;i++)
				if (cur.npos[i]<ntot && (i==nnum || cur.npos[i+1]!=cur.npos[i]+1))
				{
					ins.cpos=i;ins.cur=true;
					for (j=1;j<=pnum;j++) ins.ppos[j]=cur.ppos[j];
					for (j=1;j<=nnum;j++) ins.npos[j]=cur.npos[j];
					ins.npos[i]++;ins.val.clear();ins.val.len=1;ins.val.b[1]=1;
					for (j=1;j<=pnum;j++) ins.val=ins.val*(pos[ins.ppos[j]]);
					for (j=1;j<=nnum;j++) ins.val=ins.val*(neg[ins.npos[j]]);
					qpos.push(ins);
				}
		}	
	}
}

struct node_neg
{
	Bigint val;
	short pnum,nnum,ppos[20],npos[20];
	bool cur;int cpos;
	inline bool operator < (const node_neg &x) const {return val>x.val;}
};

priority_queue<node_neg> qneg;
inline void Getneg(short pnum,short nnum)
{
	int i,j,cnt;node_neg ins,cur;
	ins.pnum=pnum;ins.nnum=nnum;ins.val.clear();ins.val.b[1]=1;ins.val.len=1;
	for (i=1;i<=pnum;i++) ins.ppos[i]=i,ins.val=ins.val*pos[i];
	for (i=1;i<=nnum;i++) ins.npos[i]=i,ins.val=ins.val*neg[i];
	ins.cur=false;ins.cpos=pnum;
	while (!qneg.empty()) qneg.pop();
	qneg.push(ins);cnt=0;
	while (!qneg.empty() && cnt<k)
	{
		cur=qneg.top();qneg.pop();
		cnt++;res[++rtot]=cur.val;
		if (!cur.cur)
		{
			for (i=1;i<=cur.cpos;i++)
				if (cur.ppos[i]<ptot && (i==pnum || cur.ppos[i+1]!=cur.ppos[i]+1))
				{
					ins.cpos=i;ins.cur=false;
					for (j=1;j<=pnum;j++) ins.ppos[j]=cur.ppos[j];
					for (j=1;j<=nnum;j++) ins.npos[j]=cur.npos[j];
					ins.ppos[i]++;ins.val.clear();ins.val.len=1;ins.val.b[1]=1;
					for (j=1;j<=pnum;j++) ins.val=ins.val*pos[ins.ppos[j]];
					for (j=1;j<=nnum;j++) ins.val=ins.val*neg[ins.npos[j]];
					qneg.push(ins);
				}
			for (i=nnum;i<=nnum && i;i++)
				if (cur.npos[i]<ntot && (i==nnum || cur.npos[i+1]!=cur.npos[i]+1))
				{
					ins.cpos=i;ins.cur=true;
					for (j=1;j<=pnum;j++) ins.ppos[j]=cur.ppos[j];
					for (j=1;j<=nnum;j++) ins.npos[j]=cur.npos[j];
					ins.npos[i]++;ins.val.clear();ins.val.len=1;ins.val.b[1]=1;
					for (j=1;j<=pnum;j++) ins.val=ins.val*(pos[ins.ppos[j]]);
					for (j=1;j<=nnum;j++) ins.val=ins.val*(neg[ins.npos[j]]);
					qneg.push(ins);
				}
		}
		else
		{
			for (i=1;i<=cur.cpos;i++)
				if (cur.npos[i]<ntot && (i==nnum || cur.npos[i+1]!=cur.npos[i]+1))
				{
					ins.cpos=i;ins.cur=true;
					for (j=1;j<=pnum;j++) ins.ppos[j]=cur.ppos[j];
					for (j=1;j<=nnum;j++) ins.npos[j]=cur.npos[j];
					ins.npos[i]++;ins.val.clear();ins.val.len=1;ins.val.b[1]=1;
					for (j=1;j<=pnum;j++) ins.val=ins.val*(pos[ins.ppos[j]]);
					for (j=1;j<=nnum;j++) ins.val=ins.val*(neg[ins.npos[j]]);
					qneg.push(ins);
				}
		}
	}
}

Bigint tmp[400048];int fl;
inline void merge_sort(int left,int right)
{
	if (left>=right) return;
	int mid=(left+right)>>1,k1,k2,pt;
	merge_sort(left,mid);merge_sort(mid+1,right);
	for (k1=left,k2=mid+1,pt=left;k1<=mid && k2<=right;)
		if (fl==1)
		{
			if (res[k1]<res[k2]) tmp[pt++]=res[k1++]; else tmp[pt++]=res[k2++];
		}
		else
		{
			if (res[k1]>res[k2]) tmp[pt++]=res[k1++]; else tmp[pt++]=res[k2++];
		}
	for (;k1<=mid;) tmp[pt++]=res[k1++];
	for (;k2<=right;) tmp[pt++]=res[k2++];
	for (pt=left;pt<=right;pt++) res[pt]=tmp[pt];
}

int main ()
{
	int i,j;
	n=getint();m=getint();k=getint();
	for (i=1;i<=n;i++)
	{
		a[i]=getint();
		if (a[i]>=0) pos[++ptot].read(a[i]); else neg[++ntot].read(-a[i]);
	}
	for (i=1;i<=ptot;i++) res[i]=pos[i];
	fl=0;merge_sort(1,ptot);
	for (i=1;i<=ptot;i++) pos[i]=res[i];
	for (i=1;i<=ntot;i++) res[i]=neg[i];
	fl=0;merge_sort(1,ntot);
	for (i=1;i<=ntot;i++) neg[i]=res[i];
		rtot=0;
		for (i=0;i<=m;i+=2)
		{
			if (ptot<m-i || ntot<i) continue;
			Getpos(m-i,i);
		}
		if (rtot>=k)
		{
			fl=0;merge_sort(1,rtot);
			res[k].print();
			return 0;
		}
		k-=rtot;
		rtot=0;reverse(pos+1,pos+ptot+1);reverse(neg+1,neg+ntot+1);
		for (i=1;i<=m;i+=2)
		{
			if (ptot<m-i || ntot<i) continue;
			Getneg(m-i,i);
		}
		fl=1;merge_sort(1,rtot);
		printf("-");res[k].print();
	return 0;
}

/* --- author: dxm --- */
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;

#define INF 1e9
#define Inf 1e18
#define rep(i,n) for(int (i)=0;(i)<n;i++)
#define REP(i,n) for(int (i)=1;(i)<=n;i++)
#define mp make_pair
#define pb push_back
#define fst first
#define snd second
typedef long long ll;
typedef double db;
typedef long double ldb;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<long long,long long> pll;

void qread(int &x){
	int neg=1;x=0;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')neg=-1;c=getchar();}
	while(c>='0'&&c<='9')x=10*x+c-'0',c=getchar();
	x*=neg;
}

const int maxn=100005;
const int mlog=20;
const int mod=998244353;
int n,m,ans;
vector<pii>edge[maxn];
vector<int>pos[maxn];
int a[maxn],rt[maxn],num[maxn][2];

namespace Segtree{
	int tot;
	int ls[maxn*mlog],rs[maxn*mlog];
	int sum[maxn*mlog],pre[maxn*mlog][2][2],suf[maxn*mlog][2][2],val[maxn*mlog];
	int getpre(int v,int l,int r,int f1,int f2){
		if(v)return pre[v][f1][f2];
		return f1?0:(r-l+1+f2)/2;
	}
	int getsuf(int v,int l,int r,int f1,int f2){
		if(v)return suf[v][f1][f2];
		return f1?0:(r-l+1+f2)/2;
	}
	void pushup(int v,int l,int r){
		sum[v]=sum[ls[v]]+sum[rs[v]];
		val[v]=(val[ls[v]]+val[rs[v]])%mod;	
		int mid=(l+r)>>1;
		rep(f1,2)rep(f2,2)
			val[v]=(val[v]+1LL*getsuf(ls[v],l,mid,f1,f2)*getpre(rs[v],mid+1,r,f1^1,f2)%mod)%mod;
		rep(f1,2)rep(f2,2){
			pre[v][f1][f2]=(getpre(ls[v],l,mid,f1,f2)+getpre(rs[v],mid+1,r,f1^(sum[ls[v]]&1),f2^((mid-l+1)&1)))%mod;
			suf[v][f1][f2]=(getsuf(rs[v],mid+1,r,f1,f2)+getsuf(ls[v],l,mid,f1^(sum[rs[v]]&1),f2^((r-mid)&1)))%mod;
		}
	}
	void update(int &rt,int l,int r,int k){
		if(!rt)rt=++tot;
		if(l==r){
			sum[rt]=1;
			pre[rt][1][1]=suf[rt][1][1]=1;
			return;
		}
		int mid=(l+r)>>1;
		if(k<=mid)update(ls[rt],l,mid,k);
		else update(rs[rt],mid+1,r,k);
		pushup(rt,l,r);
	}
	int merge(int rt1,int rt2,int l,int r){
		if(!rt1||!rt2)return rt1+rt2;
		if(l==r)return rt1;
		int mid=(l+r)>>1;
		ls[rt1]=merge(ls[rt1],ls[rt2],l,mid);
		rs[rt1]=merge(rs[rt1],rs[rt2],mid+1,r);
		pushup(rt1,l,r);
		return rt1;
	}
} 

void dfs(int x,int p,int e){
	rep(i,edge[x].size()){
		pii y=edge[x][i];
		if(y.fst==p)continue;
		dfs(y.fst,x,y.snd);
		rt[x]=Segtree::merge(rt[x],rt[y.fst],1,m);
	}
	rep(i,pos[x].size())Segtree::update(rt[x],1,m,pos[x][i]);
	ans=(ans+1LL*e*Segtree::val[rt[x]]%mod)%mod;
}

int main(){
#ifdef FILE
	freopen("FILE.in","r",stdin);
	freopen("FILE.out","w",stdout);
#endif
	qread(n);qread(m);
	REP(i,n-1){
		int u,v,c;
		qread(u);qread(v);qread(c);
		edge[u].pb(mp(v,c));
		edge[v].pb(mp(u,c));
	}
	REP(i,m)qread(a[i]),pos[a[i]].pb(i);
	dfs(1,0,0);
	printf("%d\n",ans);
#ifdef TIME
	printf("Running Time = %d ms\n",int(clock()*1000.0/CLOCKS_PER_SEC));
#endif
	return 0;
}

/*
Input:
-----------------
Output:
*/


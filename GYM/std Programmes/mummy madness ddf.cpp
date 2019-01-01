#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,a,n) for (int i=a;i<int(n);i++)
#define mp make_pair
#define fi first
#define se second
#define per(i,a,n) for (int i=int(n)-1;i>=(a);i--)
#define pb push_back
using namespace std;

int n;


const int N=333333;
int seg[N*4],tag[N*4];
int l1,r1,v;

void pd(int x){
	seg[x<<1]+=tag[x];
	seg[x<<1|1]+=tag[x];
	tag[x<<1]+=tag[x];
	tag[x<<1|1]+=tag[x];
	tag[x]=0;
}
void upd(int l,int r,int x){
	if(l1<=l && r<=r1){
		seg[x]+=v;
		tag[x]+=v;
	}else{
		if(tag[x])pd(x);
		int mid=l+r>>1;
		if(l1<=mid)upd(l,mid,x<<1);
		if(r1>mid)upd(mid+1,r,x<<1|1);
		seg[x]=min(seg[x<<1],seg[x<<1|1]);
	}
}
void que(int l,int r,int x){
	if(l1<=l && r<=r1){
		v=min(v,seg[x]);
	}else{
		if(tag[x])pd(x);
		int mid=l+r>>1;
		if(l1<=mid)que(l,mid,x<<1);
		if(r1>mid)que(mid+1,r,x<<1|1);
	}
}
void init(int l,int r,int x){
	seg[x]=tag[x]=0;
	if(l!=r){
		int mid=l+r>>1;
		init(l,mid,x<<1);
		init(mid+1,r,x<<1|1);
	}
}

int x[111111],y[111111];


struct eve{
	int y,l,r;
	int sg;
}es[555555];int etot;
int operator<(const eve&a,const eve&b){
	if(a.y==b.y)return a.sg<b.sg;
	return a.y<b.y;
}

map<int,int> lisan;
int xtot;
bool check(int d){
	lisan.clear();
	etot=0;

	rep(i,0,n+1){
		int l=x[i]-d,r=x[i]+d;
		lisan[l];
		lisan[r+1];
	}
	xtot=0;
	for (auto it=lisan.begin();it!=lisan.end();it++)
		it->se=++xtot;


	int myl=x[0]-d,myr=x[0]+d;
	myl=lisan[myl];
	myr=lisan[myr+1]-1;
	rep(i,0,n+1){
		int l=x[i]-d,r=x[i]+d;
		l=lisan[l];
		r=lisan[r+1]-1;
		es[++etot]=(eve){y[i]-d,l,r,i?1:100};
		es[++etot]=(eve){y[i]+d+1,l,r,i?-1:-100};
	}
	sort(es+1,es+1+etot);

	int ok=0;

	init(1,xtot,1);
	rep(i,1,etot+1){
		if(abs(es[i].sg)==100){
			if(es[i].sg==100)ok=1;
			else break;
		}else{
			l1= es[i].l, r1=es[i].r,v=es[i].sg;
			upd(1,xtot,1);
		}
		if(i!=etot && es[i].y==es[i+1].y)continue;
		if(ok){
			l1=myl,r1=myr,v=0x3f3f3f3f;
			que(1,xtot,1);
			if(v==0)return 1;
		}
	}
	return 0;
}
int main(){
	int te=0;
	while(scanf("%d",&n),n!=-1){
		printf("Case %d: ",++te);
		if(n==0){
			printf("never\n");
			continue;
		}
		rep(i,1,n+1)scanf("%d%d",&x[i],&y[i]);

		x[0]=y[0]=0;

		int l=1,r=1e7;
		while(l<=r){
			int mid=l+r>>1;
			if(check(mid))l=mid+1;
			else r=mid-1;
		}
		if(l>1e7-2)printf("never\n");
		else printf("%d\n",l);
	}
	return 0;
}


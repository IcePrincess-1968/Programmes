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

const int MOD=1e9+7;
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

struct Treap
{
	Treap *left,*right;
	int val,priority;
	int sz;
	void update()
	{
		sz=1;
		if (left!=NULL) sz+=left->sz;
		if (right!=NULL) sz+=right->sz;
	}
}*root[500048];
typedef pair<Treap*,Treap*> pii;
int tot=0,pp=0,c1=0,c2=0;

Treap* Create(int val,int priority,Treap *left,Treap *right)
{
	Treap *tmp=new Treap;
	tmp->val=val;tmp->priority=priority;tmp->left=left;tmp->right=right;
	tmp->update();
	return tmp;
}

void cop(Treap *&a,Treap *b)
{
	if (b==NULL) a=NULL; else a=Create(0,rand(),NULL,NULL),*a=*b;
}

int LeftSize(Treap *root)
{
	int res=1;
	if (root->left!=NULL) res+=root->left->sz;
	return res;
}

void split(Treap *root,Treap *&a,Treap *&b,int key)
{
	if (root==NULL)
	{
		a=NULL;b=NULL;
		return;
	}
	if (root->val>=key)
	{
		cop(b,root);
		split(root->left,a,b->left,key);
		b->update();
	}
	else
	{
		cop(a,root);
		split(root->right,a->right,b,key);
		a->update();
	}
}

void split2(Treap *root,Treap *&a,Treap *&b,int key)
{
	if (root==NULL)
	{
		a=NULL;b=NULL;
		return;
	}
	if (root->val<=key)
	{
		cop(a,root);
		split2(root->right,a->right,b,key);
		a->update();
	}
	else
	{
		cop(b,root);
		split2(root->left,a,b->left,key);
		b->update();
	}
}

void split3(Treap *root,Treap *&a,Treap *&b,int key)
{
	if (root==NULL)
	{
		a=NULL;b=NULL;
		return;
	}
	//cout<<root->val<<' '<<LeftSize(root)<<endl;
	if (LeftSize(root)>key)
	{
		cop(b,root);
		split3(root->left,a,b->left,key);
		b->update();
	}
	else
	{
		cop(a,root);
		split3(root->right,a->right,b,key-LeftSize(root));
		a->update();
	}
}

void merge(Treap *root1,Treap *root2,Treap *&res)
{
	if (root1==NULL) {res=root2;return;}
	if (root2==NULL) {res=root1;return;}
	if (root1->priority<=root2->priority)
	{
		cop(res,root1);
		merge(root1->right,root2,res->right);
	}
	else
	{
		cop(res,root2);
		merge(root1,root2->left,res->left);
	}
	res->update();
}

void print(Treap *root)
{
	if (root->left!=NULL) print(root->left);
	printf("%d ",root->val);
	if (root->right!=NULL) print(root->right);
}

void Treap_insert(int rt,int val)
{
	pii splitted;split(root[rt],splitted.x,splitted.y,val);
	Treap *tmp=NULL;
	merge(splitted.x,Create(val,rand(),NULL,NULL),tmp);
	merge(tmp,splitted.y,root[++tot]);
}

void Treap_delete(int rt,int val)
{
	pii splitted;split(root[rt],splitted.x,splitted.y,val);
	pii splitted2;split3(splitted.y,splitted2.x,splitted2.y,1);
	if (splitted2.x==NULL || splitted2.x->val==val)
		merge(splitted.x,splitted2.y,root[++tot]);
	else
		cop(root[++tot],root[rt]);
}

void Treap_xrank(int rt,int val)
{
	pii splitted;split(root[rt],splitted.x,splitted.y,val);
	printf("%d\n",1+(splitted.x==NULL?0:splitted.x->sz));
	cop(root[++tot],root[rt]);
}

void Treap_rankx(int rt,int key)
{
	//if (pp==185) cout<<c1<<' '<<c2<<endl,print(root[rt]),cout<<endl;
	//for (int i=1;i<=tot;i++) print(root[i]),cout<<endl;
	pii splitted;split3(root[rt],splitted.x,splitted.y,key-1);
	//cout<<"*"<<' '<<(splitted.x==NULL)<<' '<<(splitted.y==NULL)<<endl;
	pii splitted2;split3(splitted.y,splitted2.x,splitted2.y,1);
	//cout<<"*"<<' '<<(splitted2.x==NULL)<<' '<<(splitted2.y==NULL)<<endl;
	printf("%d\n",splitted2.x->val);
	cop(root[++tot],root[rt]);
}

void Treap_prev(int rt,int val)
{
	pii splitted;split(root[rt],splitted.x,splitted.y,val);
	if (splitted.x==NULL)
	{
		printf("-2147483647\n");
		cop(root[++tot],root[rt]);
		return;
	}
	pii splitted2;split3(splitted.x,splitted2.x,splitted2.y,splitted.x->sz-1);
	printf("%d\n",splitted2.y->val);
	cop(root[++tot],root[rt]);
}

void Treap_next(int rt,int val)
{
	pii splitted;split2(root[rt],splitted.x,splitted.y,val);
	if (splitted.y==NULL)
	{
		printf("2147483647\n");
		cop(root[++tot],root[rt]);
		return;
	}
	pii splitted2;split3(splitted.y,splitted2.x,splitted2.y,1);
	printf("%d\n",splitted2.x->val);
	cop(root[++tot],root[rt]);
}

int main ()
{
	//freopen ("testdata.in","r",stdin);
	//freopen ("ans.out","w",stdout);
	int q,type,rt,x;
	q=getint();
	root[0]=NULL;
	while (q--)
	{
		++pp;
		rt=getint();type=getint();x=getint();
		if (type==1) Treap_insert(rt,x);
		if (type==2) Treap_delete(rt,x);
		if (type==3) Treap_xrank(rt,x);
		if (type==4) Treap_rankx(rt,x);
		if (type==5) Treap_prev(rt,x);
		if (type==6) Treap_next(rt,x);
	}
	return 0;
}
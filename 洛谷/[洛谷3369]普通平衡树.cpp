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
}*Root,*res;
typedef pair<Treap*,Treap*> pii;

void print(Treap *root)
{
	if (root->left!=NULL) print(root->left);
	printf("%d ",root->val);
	if (root->right!=NULL) print(root->right);
}

Treap* Create(int val,int priority,Treap *left,Treap *right)
{
	res=new Treap;
	res->left=left;res->right=right;res->val=val;res->priority=priority;
	res->update();
	return res;
}

int LeftSize(Treap *root)
{
	int res=1;
	if (root->left!=NULL) res+=root->left->sz;
	return res;
}

pii split(Treap *root,int key)
{
	if (root==NULL) return make_pair<Treap*,Treap*>(NULL,NULL);
	if (root->val>=key)
	{
		pii splitted=split(root->left,key);
		root->left=splitted.y;
		root->update();
		return mp(splitted.x,root);
	}
	else
	{
		pii splitted=split(root->right,key);
		root->right=splitted.x;
		root->update();
		return mp(root,splitted.y);
	}
}

pii split2(Treap *root,int key)
{
	if (root==NULL) return make_pair<Treap*,Treap*>(NULL,NULL);
	if (root->val<=key)
	{
		pii splitted=split2(root->right,key);
		root->right=splitted.x;
		root->update();
		return mp(root,splitted.y);
	}
	else
	{
		pii splitted=split2(root->left,key);
		root->left=splitted.y;
		root->update();
		return mp(splitted.x,root);
	}
}

pii split3(Treap *root,int key)
{
	if (root==NULL) return make_pair<Treap*,Treap*>(NULL,NULL);
	if (LeftSize(root)>key)
	{
		pii splitted=split3(root->left,key);
		root->left=splitted.y;
		root->update();
		return mp(splitted.x,root);
	}
	else
	{
		pii splitted=split3(root->right,key-LeftSize(root));
		root->right=splitted.x;
		root->update();
		return mp(root,splitted.y);
	}
}

Treap* merge(Treap *root1,Treap *root2)
{
	if (root1==NULL) return root2;
	if (root2==NULL) return root1;
	if (root1->priority<=root2->priority)
	{
		root1->right=merge(root1->right,root2);
		root1->update();
		return root1;
	}
	else
	{
		root2->left=merge(root1,root2->left);
		root2->update();
		return root2;
	}
}

void Treap_insert(int val)
{
	pii splitted=split(Root,val);
	Root=merge(merge(splitted.x,Create(val,rand(),NULL,NULL)),splitted.y);
}

void Treap_delete(int val)
{
	pii splitted=split(Root,val);
	pii splitted2=split(splitted.y,val+1);
	if (splitted2.x==NULL)
		Root=merge(splitted.x,splitted2.y);
	else
		Root=merge(merge(merge(splitted.x,splitted2.x->left),splitted2.x->right),splitted2.y);
}

void Treap_xrank(int val)
{
	pii splitted=split(Root,val);
	printf("%d\n",1+(splitted.x==NULL?0:splitted.x->sz));
	Root=merge(splitted.x,splitted.y);
}

void Treap_rankx(int x)
{
	print(Root);cout<<endl;
	pii splitted=split3(Root,x-1);
	pii splitted2=split3(splitted.y,1);
	printf("%d\n",splitted2.x->val);
	Root=merge(merge(splitted.x,splitted2.x),splitted2.y);
}

void Treap_prev(int val)
{
	pii splitted=split(Root,val);
	if (splitted.x==NULL)
	{
		printf("-2147483647\n");
		Root=merge(splitted.x,splitted.y);
		return;
	}
	pii splitted2=split3(splitted.x,splitted.x->sz-1);
	printf("%d\n",splitted2.y->val);
	Root=merge(merge(splitted2.x,splitted2.y),splitted.y);
}

void Treap_next(int val)
{
	pii splitted=split2(Root,val);
	if (splitted.y==NULL)
	{
		printf("2147483647\n");
		Root=merge(splitted.x,splitted.y);
		return;
	}
	pii splitted2=split3(splitted.y,1);
	printf("%d\n",splitted2.x->val);
	Root=merge(merge(splitted.x,splitted2.x),splitted2.y);
}

int main ()
{
	int q,type,x;
	q=getint();
	while (q--)
	{
		type=getint();x=getint();
		if (type==1) Treap_insert(x);
		if (type==2) Treap_delete(x);
		if (type==3) Treap_xrank(x);
		if (type==4) Treap_rankx(x);
		if (type==5) Treap_prev(x);
		if (type==6) Treap_next(x);
	}
	return 0;
}
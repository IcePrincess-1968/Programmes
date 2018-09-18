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

inline LL getint()
{
    char ch;LL res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,q,root,p;
int depth[100048],sz[100048],son[100048],fa[100048];
int tind[100048],eind[100048],ind=0,Left[100048],Right[100048],top[100048];
int weight[100048];
vector<int> v[100048];

struct node
{
    int left,right,len;
    LL sum,delta;
}tree[300048];

inline LL mod(LL x)
{
    while (x>=p) x-=p;
    return x;
}

void dfs1(int cur,int father)
{
    sz[cur]=1;son[cur]=0;
    int i,y,max_size=0;
    for (i=0;i<int(v[cur].size());i++)
    {
        y=v[cur][i];
        if (y!=father)
        {
            depth[y]=depth[cur]+1;fa[y]=cur;
            dfs1(y,cur);
            sz[cur]+=sz[y];
            if (sz[y]>max_size)
            {
                max_size=sz[y];
                son[cur]=y;
            }
        }
    }
}

void dfs2(int cur,int tp)
{
    top[cur]=tp;tind[cur]=++ind;eind[ind]=cur;Left[cur]=ind;
    if (son[cur]) dfs2(son[cur],tp);
    int i,y;
    for (i=0;i<int(v[cur].size());i++)
    {
        y=v[cur][i];
        if (y!=son[cur] && y!=fa[cur]) dfs2(y,y);
    }
    Right[cur]=ind;
}

void pushdown(int cur)
{
    tree[cur<<1].delta=mod(tree[cur<<1].delta+tree[cur].delta);
    tree[cur<<1|1].delta=mod(tree[cur<<1|1].delta+tree[cur].delta);
    tree[cur].delta=0;
}

void pushup(int cur)
{
    tree[cur].sum=mod(tree[cur<<1].sum+tree[cur<<1].delta*tree[cur<<1].len+tree[cur<<1|1].sum+tree[cur<<1|1].delta*tree[cur<<1|1].len);
}

void build(int cur,int left,int right)
{
    tree[cur].left=left;tree[cur].right=right;tree[cur].len=right-left+1;
    tree[cur].delta=0;
    if (left!=right)
    {
        int mid=(left+right)>>1;
        build(cur<<1,left,mid);
        build(cur<<1|1,mid+1,right);
        pushup(cur);
    }
    else
        tree[cur].sum=weight[eind[left]];
}

void update(int cur,int left,int right,LL delta)
{
    if (left<=tree[cur].left && tree[cur].right<=right)
    {
        tree[cur].delta=mod(tree[cur].delta+delta);
        return;
    }
    pushdown(cur);
    int mid=(tree[cur].left+tree[cur].right)>>1;
    if (left<=mid) update(cur<<1,left,right,delta);
    if (mid+1<=right) update(cur<<1|1,left,right,delta);
    pushup(cur);
}

int query(int cur,int left,int right)
{
    if (left<=tree[cur].left && tree[cur].right<=right) 
        return int(mod(tree[cur].sum+tree[cur].delta*tree[cur].len));
    pushdown(cur);
    int mid=(tree[cur].left+tree[cur].right)>>1;LL res=0;
    if (left<=mid) res=query(cur<<1,left,right);
    if (mid+1<=right) res=mod(res+query(cur<<1|1,left,right));
    pushup(cur);
    return int(res);
}

void update_sum(int u,int v,LL delta)
{
    int tp1=top[u],tp2=top[v];
    while (tp1!=tp2)
    {
        if (depth[tp1]<depth[tp2])
        {
            swap(u,v);
            swap(tp1,tp2);
        }
        update(1,tind[tp1],tind[u],delta);
        u=fa[tp1];tp1=top[u];
    }
    if (depth[u]<depth[v]) swap(u,v);
    update(1,tind[v],tind[u],delta);
}

int calc_sum(int u,int v)
{
    LL res=0;
    int tp1=top[u],tp2=top[v];
    while (tp1!=tp2)
    {
        if (depth[tp1]<depth[tp2])
        {
            swap(u,v);
            swap(tp1,tp2);
        }
        res=mod(res+query(1,tind[tp1],tind[u]));
        u=fa[tp1];tp1=top[u];
    }
    if (depth[u]<depth[v]) swap(u,v);
    res=mod(res+query(1,tind[v],tind[u]));
    return int(res);
}

int main ()
{
    int i,type,x,y,z;
    n=getint();q=getint();root=getint();p=getint();
    for (i=1;i<=n;i++) weight[i]=int(mod(getint()));
    for (i=1;i<=n-1;i++)
    {
        x=getint();y=getint();
        v[x].pb(y);v[y].pb(x);
    }
    fa[root]=0;depth[root]=1;dfs1(root,0);dfs2(root,root);
    build(1,1,ind);
    while (q--)
    {
        type=getint();
        if (type==1)
        {
            x=getint();y=getint();z=mod(getint());
            update_sum(x,y,z);
        }
        if (type==2)
        {
            x=getint();y=getint();
            printf("%d\n",calc_sum(x,y));
        }
        if (type==3)
        {
            x=getint();z=mod(getint());
            update(1,Left[x],Right[x],z);
        }
        if (type==4)
        {
            x=getint();
            printf("%d\n",query(1,Left[x],Right[x]));
        }
    }
    return 0;
}
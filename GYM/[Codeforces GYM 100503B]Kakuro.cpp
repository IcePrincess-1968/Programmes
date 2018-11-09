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
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

int n,m;
int type[48][48],lim_down[48],lim_right[48];
char s[48];
Pair seq[48];int tot;
Pair bel[48];

inline int getind(int x,int y) {return (x-1)*m+y;}

bool can[7][1048][148];int canMask[7][1048][148],used_down[48],used_right[48];
int cnt_down[48],cnt_right[48];

inline void init_can()
{
    for (register int Mask=0;Mask<=(1<<9)-1;Mask++)
        for (register int i=0;i<=60;i++)
        {
            int sum=0;
            for (register int j=1;j<=9;j++) if (Mask&(1<<(j-1))) sum+=j;
            can[0][Mask][i]=(sum==i);
        }
    for (register int i=1;i<=6;i++)
        for (register int Mask=0;Mask<=(1<<9)-1;Mask++)
            for (register int j=0;j<=60;j++)
                for (register int nw=1;nw<=9;nw++)
                    if ((!(Mask&(1<<(nw-1)))) && can[i-1][Mask|(1<<(nw-1))][j])
                    {
                        can[i][Mask][j]=true;
                        canMask[i][Mask][j]|=(1<<(nw-1));
                    }
}

int ans[48][48];
inline void print()
{
    for (register int i=1;i<=n;i++)
    {
        for (register int j=1;j<=m;j++)
            if (type[i][j]!=2) printf("_ "); else printf("%d ",ans[i][j]);
        printf("\n");
    }
}

int popcount[5048];
inline void init_popcount()
{
    for (register int Mask=0;Mask<=(1<<9)-1;Mask++)
    {
        popcount[Mask]=0;
        for (register int cur=Mask;cur;cur^=LOWBIT(cur)) popcount[Mask]++;
    }
}

inline bool cmp(Pair x,Pair y)
{
    int pos=getind(x.x,x.y);
    int down_id=bel[pos].x,right_id=bel[pos].y;
    int valid=canMask[cnt_down[down_id]][used_down[down_id]][lim_down[down_id]]&canMask[cnt_right[right_id]][used_right[right_id]][lim_right[right_id]];
    int num1=popcount[valid];
    pos=getind(y.x,y.y);
    down_id=bel[pos].x,right_id=bel[pos].y;
    valid=canMask[cnt_down[down_id]][used_down[down_id]][lim_down[down_id]]&canMask[cnt_right[right_id]][used_right[right_id]][lim_right[right_id]];
    int num2=popcount[valid];
    return num1<num2;
}

inline void dfs(int step)
{
    if (step==tot+1) {print();exit(0);}
    int pos=getind(seq[step].x,seq[step].y);
    int down_id=bel[pos].x,right_id=bel[pos].y;
    int valid=canMask[cnt_down[down_id]][used_down[down_id]][lim_down[down_id]]&canMask[cnt_right[right_id]][used_right[right_id]][lim_right[right_id]];
    for (register int i=1;i<=9;i++)
        if (valid&(1<<(i-1)))
        {
            used_down[down_id]|=(1<<(i-1));used_right[right_id]|=(1<<(i-1));
            cnt_down[down_id]--;cnt_right[right_id]--;
            ans[seq[step].x][seq[step].y]=i;
            sort(seq+step+1,seq+tot+1,cmp);
            dfs(step+1);
            used_down[down_id]^=(1<<(i-1));used_right[right_id]^=(1<<(i-1));
            cnt_down[down_id]++;cnt_right[right_id]++;
        }
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    freopen ("input.txt","r",stdin);
    freopen ("output.txt","w",stdout);
    scanf("%d%d",&n,&m);
    for (register int i=1;i<=n;i++)
        for (register int j=1;j<=m;j++)
        {
            scanf("%s",s+1);
            if (s[3]=='X') type[i][j]=1;
            else if (s[1]=='.') type[i][j]=2,seq[++tot]=mp(i,j);
            else
            {
                type[i][j]=3;int id=getind(i,j);
                lim_down[id]=lim_right[id]=-1;
                if (s[1]!='X') {lim_down[id]=0;for (register int j=1;j<=2;j++) lim_down[id]=lim_down[id]*10+s[j]-'0';}
                if (s[4]!='X') {lim_right[id]=0;for (register int j=4;j<=5;j++) lim_right[id]=lim_right[id]*10+s[j]-'0';}
            }
        }
    for (register int i=1;i<=n;i++)
        for (register int j=1;j<=m;j++)
            if (type[i][j]==3)
            {
                int id=getind(i,j);
                if (lim_down[id]!=-1) for (register int k=i+1;k<=n && type[k][j]==2;k++) bel[getind(k,j)].x=id,cnt_down[id]++;
                if (lim_right[id]!=-1) for (register int k=j+1;k<=m && type[i][k]==2;k++) bel[getind(i,k)].y=id,cnt_right[id]++;
            }
    init_can();init_popcount();sort(seq+1,seq+tot+1,cmp);dfs(1);
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}
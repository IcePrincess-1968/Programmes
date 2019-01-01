//Relive your past life.
//Face your demons.
//The past is never dead,it is not even past.
//The memories are not only the key to the past but...also to the future.
//coded in Rusty Lake
#include<cmath>
#include<math.h>
#include<ctype.h>
#include<algorithm>
#include<bitset>
#include<cassert>
#include<cctype>
#include<cerrno>
#include<cfloat>
#include<ciso646>
#include<climits>
#include<clocale>
#include<complex>
#include<csetjmp>
#include<csignal>
#include<cstdarg>
#include<cstddef>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cwchar>
#include<cwctype>
#include<deque>
#include<exception>
#include<fstream>
#include<functional>
#include<iomanip>
#include<ios>
#include<iosfwd>
#include<iostream>
#include<istream>
#include<iterator>
#include<limits>
#include<list>
#include<locale>
#include<map>
#include<memory>
#include<new>
#include<numeric>
#include<ostream>
#include<queue>
#include<set>
#include<sstream>
#include<stack>
#include<stdexcept>
#include<streambuf>
#include<string>
#include<typeinfo>
#include<utility>
#include<valarray>
#include<vector>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define orz  1000000007
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
int n,a[100005],b[100005],t1[2000010],t2[2000010],t3[2000010],t4[2000010];
int get(){
    char c=getchar();
    int x=0,o=1;
    while(c<'-')c=getchar();
    if(c=='-')o=-1,c=getchar();
    while(c>47)x=x*10+c-48,c=getchar();
    return x*o;
}
int ab(int x){
    return x<0?-x:x;
}
void umn(int &x,int y){
    if(y<x)x=y;
}
void umx(int &x,int y){
    if(y>x)x=y;
}
int mn(int x,int y){
    if(x<y) return x;
    return y;
}
int mx(int x,int y){
    if(x>y) return x;
    return y;
}
bool ok(int k){
    for(int A=-1;A<=1;A+=2){
        for(int B=-1;B<=1;B+=2){
            for(int i=0;i<=k;++i)t1[i]=t3[i]=k+1,t2[i]=t4[i]=-1;
            for(int i=1;i<=n;++i){
                int Aa=A*a[i],Bb=B*b[i];
                int ak=ab(a[i])-k,bk=ab(b[i])-k;
                if(Aa>=0&&Bb>=0){
                    if(ak<0)ak=0;
                    if(ak<=k)umn(t1[ak],bk);
                }
                else if(Aa>=0){
                    if(ak<0)ak=0;
                    if(ak<=k)umx(t2[ak],-bk);
                }
                else if(Bb>=0){
                    if(ak<-k)ak=-k;
                    if(ak<=0)umn(t3[-ak],bk);
                }
                else{
                    if(ak<-k)ak=-k;
                    if(ak<=0)umx(t4[-ak],-bk);
                }
            }
            for(int i=1;i<=k;++i)umn(t1[i],t1[i-1]),umx(t2[i],t2[i-1]);
            for(int i=k-1;i>=0;--i)umn(t3[i],t3[i+1]),umx(t4[i],t4[i+1]);
            for(int i=0;i<=k;++i){
                if(mn(t1[i],t3[i])-mx(t2[i],t4[i])>1){
                    return 1;
                }
            }
        }
    }
    return 0;
}
int main(){
    for(int _=1;1;++_){
        n=get();
        if(n==-1) break;
        for(int i=1;i<=n;++i){
            a[i]=get();
            b[i]=get();
        }
        printf("Case %d: ",_);
        if(ok(2000005)){
            printf("never\n");
            continue;
        }
        int o=0;
        for(int i=20;i>=0;--i)if(ok(o+(1<<i)))o+=(1<<i);
        printf("%d\n",o+1);
    }
	system("pause");
	return 0;
}

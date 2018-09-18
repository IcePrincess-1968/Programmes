/*
ID: IcePrincess_1968
TASK: ride
LANG: C++
*/
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

string s;
int a,b;

int main ()
{
	freopen ("ride.in","r",stdin);
	freopen ("ride.out","w",stdout);
	cin>>s;a=1;
	for (int i=0;i<s.size();i++) a=a*(s[i]-'A'+1)%47;
	cin>>s;b=1;
	for (int i=0;i<s.size();i++) b=b*(s[i]-'A'+1)%47;
	if (a==b) printf("GO\n"); else printf("STAY\n");
	return 0;
}
/*
ID: IcePrincess_1968
TASK: friday
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

int day[48];

bool isleap(int x)
{
	if (x%4==0 && x%100!=0) return true;
	if (x%400==0) return true;
	return false;
}

int y,m,n;
int dd=0;
int ans[48];

int main ()
{
	freopen ("friday.in","r",stdin);
	freopen ("friday.out","w",stdout);
	day[1]=day[3]=day[5]=day[7]=day[8]=day[10]=day[12]=31;
	day[4]=day[6]=day[9]=day[11]=30;
	n=getint();
	for (y=1900;y<=1900+n-1;y++)
		for (m=1;m<=12;m++)
		{
			dd+=13;
			ans[(dd-1)%7+1]++;
			dd-=13;
			if (m!=2) dd+=day[m]; else dd+=(isleap(y)?29:28);
		}
	for (int i=1;i<=7;i++)
	{
		printf("%d",ans[(i+4)%7+1]);
		if (i==7) printf("\n"); else printf(" ");
	}
	return 0;
}
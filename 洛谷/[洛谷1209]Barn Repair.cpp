#include <bits/stdc++.h>
using namespace std;

int m,s,c;
int a[1048];
int b[1048];

bool cmp(int x,int y)
{
	return x>y;
}

int main ()
{
	int i;
	scanf("%d%d%d",&m,&s,&c);
	for (i=1;i<=c;i++) scanf("%d",&a[i]);
	if (m>=c)
	{
		printf("%d\n",c);
		return 0;
	}
	sort(a+1,a+c+1);
	int ans=a[c]-a[1]+1;
	for (i=1;i<=c-1;i++) b[i]=a[i+1]-a[i]-1;
	sort(b+1,b+c,cmp);
	for (i=1;i<=m-1;i++) ans-=b[i];
	cout<<ans<<endl;
	return 0;
}

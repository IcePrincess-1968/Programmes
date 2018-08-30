#include <bits/stdc++.h>
using namespace std;

int main ()
{
	freopen ("a.in","w",stdout);
	int n=100000,q=100000,lim=1e9;
	cout<<n<<' '<<q<<endl;
	for (int i=1;i<=n;i++) cout<<rand()%lim+2<<' ';
	cout<<endl;
	for (int i=1;i<=q;i++)
	{
		int op=rand()%3+1;
		cout<<op<<' ';
		if (op==1)
		{
			cout<<rand()%n+1<<endl;
		}
		else
		{
			int l=rand()%n+1,r=rand()%n+1;
			if (l>r) swap(l,r);
			cout<<l<<' '<<r<<' '<<rand()%lim+2<<endl;
		}
	}
	return 0;
}

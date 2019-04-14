//by yjz
#include<bits/stdc++.h>
using namespace std;
#define FF first
#define SS second
#define PB push_back
#define MP make_pair
#define bged(v) (v).begin(),(v).end()
#define foreach(it,s) for(__typeof((s).begin()) it=(s).begin();it!=(s).end();it++)
typedef long long ll;
const int Imx=2147483647;
const ll Lbig=2e18;
const int mod=1e9+7;
struct AmoebaDivOne
{
	int n,m;
	bool f[111][111];
	int f_pre[111][111];
	int test(int x,int l,int r){return f_pre[x][r]-(l==0?0:f_pre[x][l-1])==r-l+1;}
	int dp[111][111][2][2];
	int sum[2][2][111][111][2][2];
	int solve()
	{
		int ret=0;
		for(int i=0;i<n;i++)
		{
			memset(dp,0,sizeof(dp));
			for(int l=0;l<m;l++)
			{
				for(int r=l;r<m;r++)
				{
					if(!test(i,l,r))continue;
					for(int lm=0;lm<2;lm++)
					{
						for(int rm=0;rm<2;rm++)
						{
							int &cur=dp[l][r][lm][rm];
							cur=lm==0&&rm==0;
							for(int plm=0;plm<=lm;plm++)
							{
								int tl,vl;
								if(lm==0&&plm==0)tl=1,vl=l;
								if(lm==1&&plm==0)tl=0,vl=l-1;
								if(lm==1&&plm==1)tl=0,vl=l;
								if(vl<0)continue;
								for(int prm=0;prm<=rm;prm++)
								{
									int tr,vr;
									if(rm==0&&prm==0)tr=0,vr=r;
									if(rm==1&&prm==0)tr=1,vr=r+1;
									if(rm==1&&prm==1)tr=1,vr=r;
									cur=(cur+sum[tl][tr][vl][vr][plm][prm])%mod;
									if(tl==0&&tr==0&&l>0)cur=(cur-sum[tl][tr][l-1][l-1][plm][prm]+mod)%mod;
									if(tl==1&&tr==1)cur=(cur-sum[tl][tr][r+1][r+1][plm][prm]+mod)%mod;
								}
							}
							if(cur!=0)
							{
								ret=(ret+cur)%mod;
//								cerr<<i<<" "<<l<<","<<r<<" "<<lm<<" "<<rm<<" "<<cur<<endl;
							}
						}
					}
				}
			}
			for(int l=0;l<m;l++)
			{
				for(int r=0;r<m;r++)
				{
					for(int lm=0;lm<2;lm++)
					{
						for(int rm=0;rm<2;rm++)
						{
							sum[0][0][l][r][lm][rm]=((r==0?0:sum[0][0][l][r-1][lm][rm])+dp[l][r][lm][rm])%mod;
							sum[1][0][l][r][lm][rm]=((r==0?0:sum[1][0][l][r-1][lm][rm])+dp[l][r][lm][rm])%mod;
						}
					}
				}
			}
			for(int l=0;l<m;l++)
			{
				for(int r=m-1;r>=0;r--)
				{
					for(int lm=0;lm<2;lm++)
					{
						for(int rm=0;rm<2;rm++)
						{
							sum[0][1][l][r][lm][rm]=((r==m-1?0:sum[0][1][l][r+1][lm][rm])+dp[l][r][lm][rm])%mod;
							sum[1][1][l][r][lm][rm]=((r==m-1?0:sum[0][1][l][r+1][lm][rm])+dp[l][r][lm][rm])%mod;
						}
					}
				}
			}
			
			for(int l=0;l<m;l++)
			{
				for(int r=0;r<m;r++)
				{
					for(int lm=0;lm<2;lm++)
					{
						for(int rm=0;rm<2;rm++)
						{
							sum[0][0][l][r][lm][rm]=((l==0?0:sum[0][0][l-1][r][lm][rm])+sum[0][0][l][r][lm][rm])%mod;
							sum[0][1][l][r][lm][rm]=((l==0?0:sum[0][1][l-1][r][lm][rm])+sum[0][1][l][r][lm][rm])%mod;
						}
					}
				}
			}
			for(int l=m-1;l>=0;l--)
			{
				for(int r=0;r<m;r++)
				{
					for(int lm=0;lm<2;lm++)
					{
						for(int rm=0;rm<2;rm++)
						{
							sum[1][0][l][r][lm][rm]=((l==m-1?0:sum[1][0][l+1][r][lm][rm])+sum[1][0][l][r][lm][rm])%mod;
							sum[1][1][l][r][lm][rm]=((l==m-1?0:sum[1][1][l+1][r][lm][rm])+sum[1][1][l][r][lm][rm])%mod;
						}
					}
				}
			}
		}
		return ret;
	}
	public:
	int count(vector<string> G)
	{
		n=G.size()*2;
		m=G[0].size()*2;
		for(int i=0;i<n/2;i++)
		{
			for(int j=0;j<m/2;j++)
			{
				char c=G[i][j];
				int x=c>='0'&&c<='9'?c-'0':c-'a'+10;
				x=15-x;
				f[i+i][j+j]=x&1;
				f[i+i][j+j+1]=(x>>1)&1;
				f[i+i+1][j+j]=(x>>2)&1;
				f[i+i+1][j+j+1]=x>>3;
			}
		}
		/*
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)cerr<<f[i][j];
			cerr<<endl;
		}*/
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)f_pre[i][j]=f[i][j]+(j==0?0:f_pre[i][j-1]);
		}
		return solve();
	}
}a;
int main()
{
	freopen ("a.in","r",stdin);
	freopen ("a.ans","w",stdout);
	int nn;string s;vector<string> ss;
	AmoebaDivOne A;
	while (cin>>nn)
	{
		ss.clear();
		for (register int i=1;i<=nn;i++) cin>>s,ss.pb(s);
		cout<<A.count(ss)<<endl;
	}
	return 0;
}


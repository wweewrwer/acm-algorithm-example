#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long

const int mod=1e9+7;
using namespace std;

ll g[105];
int n,m,k,lim[105],r[105];ll c[105][105],lsum[105],rsum[105];
void ready()
{
	c[0][0]=1;
	for(int i=1;i<=100;i++)
	{
		c[i][0]=c[i][i]=1;
		for(int ii=1;ii<i;ii++)
		{
			c[i][ii]=(c[i-1][ii-1]+c[i-1][ii])%mod;
		}
	}
}
long long qkpow(long long a,long long t)
{
	long long ans=1;
	while(t)
	{
		if(t&1)ans=ans*a%mod;
		a=a*a%mod;t>>=1;
	}
	return ans;
}
ll work(int k)
{
	if(k>n-1)return 0;
	ll ans=c[n-1][k];
	for(int i=1;i<=m;i++)
		ans=ans*c[n-k-1][r[i]-1]%mod;
	return ans;
}
ll calc(int k,int s)
{
	ll ans=0;
	for(int i=0;i<=k-2;i++)
	{
		ans=(ans+c[k][i]*g[i]%mod)%mod;
	}
	ans=(mod-ans)%mod;
	ans=((ans+qkpow(s+1,k))%mod-1+mod)%mod*qkpow(c[k][k-1],mod-2)%mod;
	return ans;
}
ll lagrange(ll *x,ll *y,ll u)
{
	ll ans=0;
	for(int i=1;i<=n+1;i++)
	{
		ll mo=1;
		ll son=1;
		for(int ii=1;ii<=n+1;ii++)
		{
			if(i!=ii)
			{
				//n*n按照定义插值。 
				son=son*(u-x[ii])%mod;
				mo=mo*(x[i]-x[ii])%mod;
			}
		}
		mo=(mo+mod)%mod;
		son=(son+mod)%mod;
		ans=(ans+son*y[i]%mod*qkpow(mo,mod-2)%mod)%mod;
	}
	return ans;
}
int main()
{
	freopen("mark.in","r",stdin);
	//freopen("mark.out","w",stdout);
	ready();
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++)
		scanf("%d",&lim[i]);
	for(int i=1;i<=m;i++)
		scanf("%d",&r[i]);
	ll w3=(work(k)-c[k+1][k]*work(k+1)%mod+mod)%mod;
	ll ans=1;
	for(int i=1;i<=m;i++)
	{
		for(int ii=1;ii<=n+1;ii++)
		{
			//对于一个最高次n的式子，我们进行n+1次插值一定正确 
			lsum[ii]=ii;//表示x 
			rsum[ii]=0;//表示y 
			for(int i3=1;i3<=ii;i3++)
			{
				rsum[ii]=(rsum[ii]+qkpow(i3,n-r[i])*qkpow(ii-i3,r[i]-1)%mod)%mod;
			}
		}
		ans=ans*lagrange(lsum,rsum,lim[i])%mod;//通过插值差出lim[i]. 
	}
	cout<<ans*w3%mod<<'\n';
	return 0;
}

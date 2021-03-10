#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=10000005;
using namespace std;

int prime[maxn],tot=0,inq[maxn],mu[maxn],modnum=100000009,f[maxn],g[maxn];
void get_mu()
{
	int n=maxn-5;
	mu[1]=1;
	f[1]=1;
	g[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!inq[i])
		{
			prime[++tot]=i;
			mu[i]=-1;
			f[i]=(i-(long long)i*i)%modnum;
		}
		for(int ii=1;ii<=tot&&(long long)prime[ii]*i<=n;ii++)
		{
			inq[prime[ii]*i]=1;
			if(i%prime[ii]==0)
			{
				mu[i*prime[ii]]=0;
				f[i*prime[ii]]=(long long)f[i]*prime[ii]%modnum;
				break;
			}
			mu[i*prime[ii]]=-mu[i];
			f[i*prime[ii]]=(long long)f[i]*(f[prime[ii]])%modnum;
		}
		g[i]=(g[i-1]+f[i])%modnum;
	}
}
long long sum(long long x)
{
	return x*(x+1)/2%modnum;
}
long long query(int n,int m)
{
	if(n>m)swap(n,m);
	int last=0;
	long long tmp=0;
	for(int i=1;i<=n;i=last+1)
	{
		last=min(n/(n/i),m/(m/i));
		tmp=(tmp+sum(n/last)*sum(m/last)%modnum*(g[last]-g[i-1])%modnum)%modnum;
	}
	return tmp;
}
int main()
{
	get_mu();
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		int n,m;
		scanf("%d%d",&n,&m);
		printf("%d\n",(query(n,m)%modnum+modnum)%modnum);
	}
	return 0;
}

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

const int maxn=50005;
using namespace std;

int prime[maxn],inq[maxn],mu[maxn],n,tot=0;
void get_mu()
{
	mu[1]=1;
	for(int i=2;i<=50000;i++)
	{
		if(!inq[i])
		{
			prime[++tot]=i;
			mu[i]=-1;
		}
		for(int ii=1;(long long)prime[ii]*i<=50000;ii++)
		{
			inq[prime[ii]*i]=1;
			if(i%prime[ii]==0)
			{
				mu[i*prime[ii]]=0;
				break;
			}
			mu[prime[ii]*i]=-mu[i];//prime[ii]*i只会被筛到一次，而prime[ii]为-1； 
		}
	}
	for(int i=1;i<=50000;i++)
	{
		mu[i]+=mu[i-1];
	}
}
int work(int a,int b,int k)
{
	int tmp=0;
	int last=0;
	for(int i=1;(long long)i*k<=a&&(long long)i*k<=b;i=last+1)
	{
		last=min(a/(a/i),b/(b/i));
		tmp+=(mu[last]-mu[i-1])*(a/(last*k))*(b/(last*k));
	}
	return tmp;
}
int main()
{
	get_mu();
	int t;
	int ai,bi,ci,di,k;
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		scanf("%d%d%d%d%d",&ai,&bi,&ci,&di,&k);
		printf("%d\n",work(bi,di,k)-work(ai-1,di,k)-work(bi,ci-1,k)+work(ai-1,ci-1,k));
		//scanf("%d%d%d",&ai,&bi,&k);
		//printf("%d\n",work(ai,bi,k));
	}
	return 0;
}

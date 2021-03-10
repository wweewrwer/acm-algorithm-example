#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

const int maxn=100005;
using namespace std;

struct abc
{
	int v;
	int i;
	friend bool operator <(abc one,abc two)
	{
		return one.v<two.v;
	}
}f[maxn];
int prime[maxn],inq[maxn],tot=0,mu[maxn];
void get_mu()
{
	mu[1]=1;
	int mn=100000;
	for(int i=2;i<=mn;i++)
	{
		if(!inq[i])
		{
			prime[++tot]=i;
			mu[i]=-1;
		}
		for(int ii=1;ii<=tot&&prime[ii]*i<=mn;ii++)
		{
			inq[prime[ii]*i]=1;
			if(i%prime[ii]==0)
			{
				mu[i*prime[ii]]=0;
				break;
			}
			mu[prime[ii]*i]=-mu[i];
		}
	}
}
void get_f()
{
	int sn=0;
	int n=100000;
	for(int i=1;i<=n;i++)
	{
		sn=sqrt(i+0.5);
		int x=i;
		f[i].v=1;
		f[i].i=i;
		for(int ii=1;prime[ii]<=sn;ii++)
		{
			int tmp=1;
			int tmp2=prime[ii];
			while(x%prime[ii]==0)
			{
				tmp+=tmp2;
				tmp2*=prime[ii];
				x/=prime[ii];
			}
			f[i].v*=tmp;
		}
		if(x!=1)
		{
			f[i].v*=(x+1);
		}
	}
	sort(f+1,f+n+1);
}
struct mydata
{
	int n;
	int m;
	int a;
	int id;
	friend bool operator <(mydata one,mydata two)
	{
		return one.a<two.a;
	}
}d[20005];
int ans[maxn],c[maxn];
int lowbit(int x)
{
	return x&(-x);
}
void update(int x,int d)
{
	int n=100000;
	while(x<=n)
	{
		c[x]+=d;
		x+=lowbit(x);
	}
}
int query(int x)
{
	int tmp=0;
	while(x>0)
	{
		tmp+=c[x];
		x-=lowbit(x);
	}
	return tmp;
}
int main()
{
	get_mu();
	get_f();
	int q;
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d%d",&d[i].n,&d[i].m,&d[i].a);
		if(d[i].n<d[i].m)swap(d[i].n,d[i].m);
		d[i].id=i;
	}
	sort(d+1,d+q+1);
	int l=1;
	for(int i=1;i<=q;i++)
	{
		int last=0;
		for(;f[l].v<=d[i].a&&l<=100000;l++)
		{
			for(int ii=1;ii*f[l].i<=100000;ii++)
			{
				update(f[l].i*ii,f[l].v*mu[ii]);
			}
		}
		for(int ii=1;ii<=d[i].m;ii=last+1)
		{
			last=min(d[i].n/(d[i].n/ii),d[i].m/(d[i].m/ii));
			ans[d[i].id]+=(d[i].n/last)*(d[i].m/last)*(query(last)-query(ii-1));
		}
	}
	int modnum=(1ll<<31)-1;
	for(int i=1;i<=q;i++)
	{
		printf("%d\n",ans[i]&modnum);
	}
	return 0;
}

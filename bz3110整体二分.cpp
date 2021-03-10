#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=100005;
using namespace std;

void _scanf(long long &a)
{
	a=0;
	char ch=getchar();
	int updown=0;
	while(ch<'0'||ch>'9'){if(ch=='-')updown=1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=a*10+ch-48;ch=getchar();}
	if(updown)a=-a;
}
struct abc
{
	int id;
	int w;
	int l;
	int r;
	long long k;
}a[maxn],b1[maxn],b2[maxn];
int n,m;
int ans[maxn],inf=50005,inq[maxn];
long long c[maxn];
long long c2[maxn];
int lowbit(int x)
{
	return x&-x;
}
void update(int x,int i,int d)
{
	int d2=x*d;
	while(x<=n)
	{
		if(inq[x]!=i)inq[x]=i,c[x]=0,c2[x]=0;
		c[x]+=d;
		c2[x]+=d2;
		x+=lowbit(x);
	}
}
long long query(int x,int i)
{
	long long tmp=0;
	while(x>0)
	{
		if(inq[x]!=i)inq[x]=i,c[x]=0,c2[x]=0;
		tmp+=c[x];
		x-=lowbit(x);
	}
	return tmp;
}
long long query2(int x,int i)
{
	long long tmp=0;
	while(x>0)
	{
		if(inq[x]!=i)inq[x]=i,c[x]=0,c2[x]=0;
		tmp+=c2[x];
		x-=lowbit(x);
	}
	return tmp;
}
int tot=0;
void solve(int bl,int br,int l,int r)
{
	//if(bl>br)return;
	if(l==r)
	{
		for(int ii=bl;ii<=br;ii++)if(a[ii].w==2)ans[a[ii].id]=l;
		return;
	}
	tot++;
	int mid=(l+r)>>1;//在处理含负数的情况下只能用>>1,否则会TLE,如l为-2,r为-1时。 
	int totl=0,totr=0;
	for(int i=bl;i<=br;i++)
	{
		if(a[i].w==1)
		{
			if(a[i].k>mid)
			{
				update(a[i].l,tot,1);
				update(a[i].r+1,tot,-1);
				b1[++totl]=a[i];
			}
			else b2[++totr]=a[i];
		}
		else
		{
			long long tmp=(a[i].r+1)*query(a[i].r,tot)-query2(a[i].r,tot)-
							((a[i].l)*query(a[i].l-1,tot)-query2(a[i].l-1,tot));
			if(tmp>=a[i].k)b1[++totl]=a[i];
			else a[i].k-=tmp,b2[++totr]=a[i];
		}
	}
	
	for(int i=0;i<totl;i++)a[bl+i]=b1[i+1];
	for(int i=0;i<totr;i++)a[bl+totl+i]=b2[i+1];
	solve(bl,bl+totl-1,mid+1,r);
	solve(bl+totl,br,l,mid);
}
int main()
{
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	int ai,bi,ci;long long di;
	scanf("%d%d",&n,&m);
	int cnt=0;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&ai,&bi,&ci);
		_scanf(di);
		if(ai==2)cnt++;
		a[i]=(abc){cnt,ai,bi,ci,di};
	}
	solve(1,m,-n,n);
	for(int i=1;i<=cnt;i++)
	{
		printf("%d\n",ans[i]);
	}
	return 0;
}

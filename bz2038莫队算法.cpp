#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

const int maxn=50005;
using namespace std;

int n,m,sn,tn;
int a[maxn];
struct mydata
{
	int l;
	int r;
	int id;
	int i;
	friend bool operator <(mydata one,mydata two)
	{
		if(one.id!=two.id)return one.id<two.id;
		if(one.r!=two.r)return one.r<two.r;
		else return one.l<two.l;
	}
}q[maxn];
long long gcd(long long a,long long b)
{
	if(b==0)return a;
	else return gcd(b,a%b);
}
int c[maxn];
void upd(long long &tmp,int w,int d)//更改自己的值 
{
	tmp-=(long long)c[a[w]]*c[a[w]];
	c[a[w]]+=d;
	tmp+=(long long)c[a[w]]*c[a[w]];
}
int ans1[maxn],ans2[maxn];
int main()
{
	scanf("%d%d",&n,&m);
	sn=sqrt(n+0.5);
	tn=n/sn;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id=(q[i].l-1)/sn+1;//先比左边块编号，在比右边位置 
		q[i].i=i;
	}
	sort(q+1,q+m+1);
	int l=1,r=0;
	long long tmp=0;
	for(int i=1;i<=m;i++)
	{
		if(q[i].l==q[i].r)//l==r算答案 
		{
			ans1[q[i].i]=0;
			ans2[q[i].i]=1;
			continue;
		}
		for(;q[i].l<l;l--)upd(tmp,l-1,1);//移动更新 
		for(;q[i].r>r;r++)upd(tmp,r+1,1);
		for(;q[i].r<r;r--)upd(tmp,r,-1);
		for(;q[i].l>l;l++)upd(tmp,l,-1);
		
		//算答案 
		ans1[q[i].i]=(tmp-(q[i].r-q[i].l+1))/2;
		ans2[q[i].i]=(long long)(r-l+1)*(r-l)/2;
		int g=gcd(ans1[q[i].i],ans2[q[i].i]);
		ans1[q[i].i]/=g;
		ans2[q[i].i]/=g;
	}
	for(int i=1;i<=m;i++)
	{
		printf("%d/%d\n",ans1[i],ans2[i]);
	}
	return 0;
}

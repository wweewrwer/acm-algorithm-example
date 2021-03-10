#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

int modnum;
struct matrix
{
	long long v[25][25];
	int n,m;
	matrix()
	{
		n=0;
		m=0;
		memset(v,0,sizeof(v));
	}
	friend matrix operator *(matrix one,matrix two)
	{
		matrix c;
		c.m=one.m;c.n=two.n;
		for(int i=1;i<=c.m;i++)
		for(int ii=1;ii<=c.n;ii++)
		for(int i3=1;i3<=one.n;i3++)
		{
			c.v[i][ii]=(c.v[i][ii]+one.v[i][i3]*two.v[i3][ii]%modnum)%modnum;
		}
		return c;
	}
};
matrix mypow(matrix a,int t)
{
	if(t<=0)
	{
		matrix c;//单位矩阵 
		c.n=c.m=a.m;
		for(int i=1;i<=a.m;i++)
		{
			c.v[i][i]=1;
		}
		return c;
	}
	matrix c=mypow(a,t/2);
	if(t%2==0)return c*c;
	return c*c*a;
}
int k,n,a[25],f[25];
void work()
{
	matrix c,c2,c3;
	c.n=c.m=k;
	//先建立转移矩阵，即下一次该位置的f函数有那些函数构成。 
	for(int i=1;i<=k;i++)
	{
		c.v[1][i]=a[i];
	}
	for(int i=2;i<=c.m;i++)
	{
		c.v[i][i-1]=1;
	}
	c2.m=k,c2.n=1;
	for(int i=1;i<=k;i++)
	{
		c2.v[i][1]=f[k-i+1];
	}
	if(n>=2)c3=mypow(c,n-k)*c2;//最后乘上来即可。 
	else
	{
		cout<<f[n]<<'\n';
		return;
	}
	cout<<c3.v[1][1]<<'\n';
}
int main()
{
	while(scanf("%d%d%d",&k,&n,&modnum))
	{
		if(k==0&&n==0&&modnum==0)break;
		for(int i=1;i<=k;i++)
		{
			scanf("%d",&a[i]);
		}
		for(int i=1;i<=k;i++)
		{
			scanf("%d",&f[i]);
		}
		work();
	}
	return 0;
}

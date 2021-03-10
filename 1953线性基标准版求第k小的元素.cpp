#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

int buf[40];
void _printf(long long a)
{
	int k=0;
	if(a==0){putchar('0');putchar('\n');return;}
	if(a<0)putchar('-'),a=-a;
	while(a!=0)
	{
		buf[k++]=a%10;
		a=a/10;
	}
	for(int i=k-1;i>=0;i--)
	{
		putchar('0'+buf[i]);
	}
	putchar('\n');
}
void _scanf(long long &a)
{
	a=0;
	char ch=getchar();
	int updown=0;
	while(ch<'0'||ch>'9'){if(ch=='-')updown=1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=a*10+ch-48;ch=getchar();}
	if(updown)a=-a;
}
long long a[75];
int gauss(long long x)//O(nm+m^2);
{
	for(int i=63;i>=0;i--)
	{
		if((x>>i)&1)
		{
			if(a[i]==0)
			{
				a[i]=x;
				for(int ii=i-1;ii>=0;ii--)if((a[i]>>ii)&1)a[i]^=a[ii];//注意这里要先把该数多余的东西异或掉 
				for(int ii=63;ii>i;ii--)if((a[ii]>>i)&1)a[ii]^=a[i];//去异或掉高位的1 
				break;
			}
			else
			{
				x^=a[i];
				if(x==0)return 1;//特判能否异或出0； 
			}
		}
	}
	return 0;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,q,t;
	long long ai=0;
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		printf("Case #%d:\n",i);
	
		memset(a,0,sizeof(a));
		scanf("%d",&n);
		int isok=0;
		for(int ii=1;ii<=n;ii++)
		{
			_scanf(ai);
			isok=gauss(ai)?1:isok;
		}
		sort(a,a+65);
		n=unique(a,a+65)-a;n--;
		scanf("%d",&q);
		for(int ii=1;ii<=q;ii++)
		{
			_scanf(ai);
			ai-=isok;
			long long ans=0;
			if((ai>>n)!=0)
			{
				printf("-1\n");
				continue;
			}
			for(int i3=1;i3<=n;i3++)
				if((ai>>(i3-1))&1)ans=ans^a[i3];
			_printf(ans);
		}
	}
	return 0;
}

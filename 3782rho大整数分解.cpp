#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>

const int maxn=1000005;
using namespace std;

long long sta[maxn];int top=0;
long long mul(long long a,long long b,long long k)
{
	long long ans=0;a=a%k;
	while(b)
	{
		if(b&1)ans=(ans+a)%k;
		a=(a<<1)%k;b>>=1;
	}
	return ans;
}
long long qkpow(long long a,long long t,long long mod)
{
	long long ans=1;
	while(t)
	{
		if(t&1)ans=mul(ans,a,mod);
		a=mul(a,a,mod);t=t>>1;
	}
	return ans;
}
int miller_rabin(long long n)
{
	if(n<2)return 0;
	if(n==2)return 1;
	if(n%2==0)return 0;
	long long r=n-1,d=0,x,xx;
	while(r%2==0)r/=2,d++;
	for(int i=1;i<=10;i++)
	{
		x=qkpow(rand()%(n-2)+2,r,n);
		for(int ii=1;ii<=d;ii++)
		{
			xx=mul(x,x,n);
			if(xx==1&&x!=1&&x!=n-1)return 0;
			x=xx;
		}
		if(x!=1)return 0;
	}
	return 1;
}
long long gcd(long long x,long long y)
{
	if(y==0)return x;
	else return gcd(y,x%y);
}
//������Ȧ�ǲ�������Ȧ�ķ�Χ��ͬʱ��֤��㣬��Ȧ�ƻ���ʱ�Ϳ������ˡ� 
long long rho(long long n,long long c)
{
	long long x=rand()%n,y=x,t=n,k=2;
	for(long long i=2;;i++)
	{
		x=(mul(x,x,n)+c)%n;
		t=gcd(abs(x-y),n);
		if(t>1||y==x)break;//����û���ҵ�һ����������Ȧ�Ƿ��Ѿ���ʼѭ���ˡ� 
		if(i==k)y=x,k<<=1;//����������Ȧ�ĳ��ȣ�ͬʱ�����==x; 
	}
	return t;
}
//���̣��е�ǰ�Ƿ����������������ҵ�ǰ��һ��������Ȼ��ݹ鼴�ɡ� 
void zys(long long n)//�������������һ������Ҫ�����Ź�������������p^a�����������ô�������Ϊa��p,������һ�� 
{
	if(n==1)return;
	if(miller_rabin(n)){sta[++top]=n;return;}//���Ƿ�Ϊ���� 
	
	long long t=n;
	while(t>=n)t=rho(n,rand()%(n-1)+1);//�ҳ�һ������ 
	zys(t); 
	zys(n/t); 
}
int main()
{
	srand(20001217);
	long long x=0;
	while(cin>>x)
	{
		top=0;
		zys(x);
		sort(sta+1,sta+top+1);
		top=unique(sta+1,sta+top+1)-sta;top--;
		cout<<x<<" = ";
		for(int i=1;i<=top;i++)
		{
			int tmp=0;
			cout<<sta[i];
			while(x%sta[i]==0)
			{
				tmp++;
				x=x/sta[i];
			}
			if(tmp!=1)cout<<'^'<<tmp;
			if(i!=top)cout<<" * ";
		}
		cout<<'\n';
	}
	return 0;
}

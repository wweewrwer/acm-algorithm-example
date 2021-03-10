#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>

using namespace std;

void _scanf(long long &a,char *s)
{
	a=0;
	int t=0;
	char ch=s[++t];
	int updown=0;
	while(ch<'0'||ch>'9'){if(ch=='-')updown=1;ch=s[++t];}
	while(ch>='0'&&ch<='9'){a=a*10+ch-48;ch=s[++t];}
	if(updown)a=-a;
}
//��������˲��Դ�ģ��(longlong)ȡģ 
long long mul(long long a,long long b,long long k)
{
	//��Ҫ�ǽ��˷���Ϊ�ӷ�������ö��b�Ķ�����λ�����С� 
	long long ret=0,tt=a%k;
	while(b)
	{
		if(b&1)ret=(ret+tt)%k;
		tt=(tt<<1)%k;b>>=1;
	}
	return ret;
}

long long qkpow(long long a,long long r,long long mod)
{
	long long ans=1;
	while(r)
	{
		if(r&1)ans=mul(ans,a,mod);
		a=mul(a,a,mod);r>>=1;
	}
	return ans;
}
//�ȶ�n��2�Ĺ�ϵ�����ж����ٶ�a��r�η���Ȼ�󲻶Ͻ��ж���̽�⼴�ɡ� 
bool miller_rabin(long long n)
{
	if(n<2)return false;
	if(n==2)return true;
	if(n%2==0)return false;
	//n-1ת��Ϊr*(2��d�η�) 
	long long r=n-1,d=0,a,x,xx;
	while(r%2==0)d++,r=r/2;
	for(int i=0;i<=10;i++)
	{
		a=rand()%(n-2)+2;
		x=qkpow(a,r,n);
		for(int ii=1;ii<=d;ii++)
		{
			xx=mul(x,x,n);
			//��x*x mod p =1,x=1��x=n-1; 
			if(xx==1&&x!=1&&x!=n-1)return false;
			x=xx;
		}
		if(xx!=1)return false;
	}
	return true;
}
void work()
{
	srand(20001217);
	//����miller_rabin����
	 
}
char s[105];
int main()
{
	work(); 
	long long x;
	while(scanf("%s",s+1)!=EOF)
	{
		_scanf(x,s);
		if(miller_rabin(x))printf("Y\n");
		else printf("N\n");
	}
	return 0;
} 

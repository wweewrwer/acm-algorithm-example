#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long 

const int maxn=10005;
using namespace std;

//����Ϊ���ģ���չLucas������������ c(n,m) mod p^k��pΪ������ֵ,
//һ�����й�ʣ�ඨ���modnum���������ӡ� 
int top=0;
long long p,n,m,w[9],pri[maxn],pt[maxn];//pΪģ�� 
void getfac(long long p)
{
	for(long long i=2;i*i<=p;i++)
	{
		if(p%i==0)pri[++top]=1,pt[top]=i;
		while(p%i==0)pri[top]*=i,p/=i;
	}
	if(p!=1)pri[++top]=p,pt[top]=p;
}
long long qkpow(long long a,long long t,long long mod)
{
	long long ans=1;
	while(t)
	{
		if(t&1)ans=ans*a%mod;
		a=(a*a)%mod;t>>=1;
	}
	return ans;
}
long long exgcd(long long a,long long b,long long &x,long long &y)
{
	if(b==0){x=1,y=0;return a;}
	long long g=exgcd(b,a%b,y,x); y-=(a/b)*x;
	return g;
}
long long getinv(long long a,long long mod)
{
	long long x,y;
	long long g=exgcd(a,mod,x,y);
	return g==1?(x+mod)%mod:-1;
}
//��չlucas��׳� 
ll getfac(ll n,ll pr,ll p)//prΪģ����pΪҪģ������ 
{
	if(n==0)return 1;
	ll re=1;
	if(n>=pr)
	{
		for(int i=2;i<pr;i++)//���ȴ���p�Ļ᲻��ѭ��������һ�� 
			if(i%p)re=re*i%pr;
		re=qkpow(re,n/pr,pr);//qkpow n/p�� 
	}
	ll r=n%pr;//���������һ�� 
	for(int i=2;i<=r;i++)
		if(i%p)re=re*i%pr;
	return re*getfac(n/p,pr,p)%pr;//��ĵݹ鴦��
}
ll getmyc(ll n,ll m,ll pr,ll p)
{
	if(m>n)return 0;
	//ͳ����Ҫ���ϵ�p�ĸ��� 
	ll c=0;
	for(ll i=n;i;i/=p)c+=i/p;
	for(ll i=m;i;i/=p)c-=i/p;
	for(ll i=n-m;i;i/=p)c-=i/p;
	ll tmp=qkpow(p,c,pr);
	if(tmp==0)return 0;
	//����׳� 
	ll x=getfac(n,pr,p),y=getfac(m,pr,p),z=getfac(n-m,pr,p);
	ll ans=x*getinv(y,pr)%pr*getinv(z,pr)%pr*tmp%pr;//��y,z�����Ԫ���ٳ���qkpow;
	return ans;
}
// 
long long crt(long long n,long long m)//�й�ʣ�ඨ�� 
{
	long long re=0;
	for(int i=1;i<=top;i++)
	{
		long long wmod=p/pri[i];//inv������y,*wmod������x,Ȼ��*getc�ô𰸡� 
		long long a=getmyc(n,m,pri[i],pt[i])*wmod%p*getinv(wmod,pri[i])%p;
		//cout<<"haha:"<<getc(n,m,pri[i],pt[i])<<'\n';
		re=(re+a)%p;
	}
	return re;
}


int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	long long sum=0;
	cin>>p>>n>>m;
	for(int i=1;i<=m;i++)
		cin>>w[i],sum+=w[i];
	if(sum>n){printf("Impossible\n"); return 0;}
	
	getfac(p);//����һ����Ȼ�����crt(n,m)������c(n,m)(n>m); 
	long long ans=1;
	for(int i=1;i<=m;i++)
		ans=ans*crt(n,w[i])%p,n-=w[i];//printf("hi %lld %lld\n",ans,n);
	cout<<(ans%p+p)%p<<'\n';
	return 0;
}

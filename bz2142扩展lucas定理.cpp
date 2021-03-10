#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long 

const int maxn=10005;
using namespace std;

//以下为核心，扩展Lucas定理是用来求 c(n,m) mod p^k，p为素数的值,
//一般后接中国剩余定理把modnum拆成这个样子。 
int top=0;
long long p,n,m,w[9],pri[maxn],pt[maxn];//p为模数 
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
//扩展lucas求阶乘 
ll getfac(ll n,ll pr,ll p)//pr为模数，p为要模的质数 
{
	if(n==0)return 1;
	ll re=1;
	if(n>=pr)
	{
		for(int i=2;i<pr;i++)//首先大于p的会不断循环，顾算一个 
			if(i%p)re=re*i%pr;
		re=qkpow(re,n/pr,pr);//qkpow n/p次 
	}
	ll r=n%pr;//暴力算最后一截 
	for(int i=2;i<=r;i++)
		if(i%p)re=re*i%pr;
	return re*getfac(n/p,pr,p)%pr;//多的递归处理
}
ll getmyc(ll n,ll m,ll pr,ll p)
{
	if(m>n)return 0;
	//统计需要乘上的p的个数 
	ll c=0;
	for(ll i=n;i;i/=p)c+=i/p;
	for(ll i=m;i;i/=p)c-=i/p;
	for(ll i=n-m;i;i/=p)c-=i/p;
	ll tmp=qkpow(p,c,pr);
	if(tmp==0)return 0;
	//计算阶乘 
	ll x=getfac(n,pr,p),y=getfac(m,pr,p),z=getfac(n-m,pr,p);
	ll ans=x*getinv(y,pr)%pr*getinv(z,pr)%pr*tmp%pr;//把y,z变成逆元，再乘上qkpow;
	return ans;
}
// 
long long crt(long long n,long long m)//中国剩余定理 
{
	long long re=0;
	for(int i=1;i<=top;i++)
	{
		long long wmod=p/pri[i];//inv是在算y,*wmod是在算x,然后*getc得答案。 
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
	
	getfac(p);//先这一步，然后调用crt(n,m)即可算c(n,m)(n>m); 
	long long ans=1;
	for(int i=1;i<=m;i++)
		ans=ans*crt(n,w[i])%p,n-=w[i];//printf("hi %lld %lld\n",ans,n);
	cout<<(ans%p+p)%p<<'\n';
	return 0;
}

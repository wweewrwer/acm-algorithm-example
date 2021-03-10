//Lucas定理是用来求 c(n,m) mod p，p为素数的值
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>

const int mod=1e6+3;
using namespace std;

int t,n,l,r;
//以下是核心 
long long inv[mod+5],f[mod+5];
void ready()
{
	f[0]=1;
	for(int i=1;i<mod;i++)
		f[i]=f[i-1]*i%mod;
	inv[1]=1;	
	for(int i=2;i<mod;i++)
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	inv[0]=1;
	for(int i=1;i<mod;i++)
		inv[i]=inv[i-1]*inv[i]%mod;
}
long long lucas(int n,int m)//直接带n,m即可求出其中n>m; 
{
	if(n<m)return 0;//判特殊情况 
	if(n<mod&&m<mod)return f[n]*inv[m]%mod*inv[n-m]%mod;//判可直接求的地方 
	return lucas(n/mod,m/mod)*lucas(n%mod,m%mod)%mod;
}

int main()
{
	ready();
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		scanf("%d%d%d",&n,&l,&r);
		int m=r-l+1;
		printf("%d\n",(int)((mod+lucas(m+n,m)-1)%mod));
	}
	return 0;
}

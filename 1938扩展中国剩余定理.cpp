#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll __int128

const int maxn=100005;
using namespace std;

int t;
ll exgcd(ll a,ll b,ll &x,ll &y)
{
	if(b==0){x=1,y=0;return a;}
	ll g=exgcd(b,a%b,y,x);y-=(a/b)*x;
	return g;
}
ll lcm(ll a,ll b)
{
	ll x,y;
	ll g=exgcd(a,b,x,y);
	return a/g*b;
}
ll calc(ll a,ll b,ll c)
{
	ll x,y;
	ll g=exgcd(a,b,x,y);
	if(c%g!=0)return -1;
	ll t=b/g; 
	x=c/g*x;
	return (x%t+t)%t;
}
ll a[maxn],b[maxn];
ll crt(ll m)
{
	for(int i=2;i<=m;i++)
	{
		ll tmp=calc(a[i-1],a[i],b[i]-b[i-1]);
		if(tmp<0)return 0;
		a[i]=lcm(a[i],a[i-1]);
		b[i]=(tmp*a[i-1]+b[i-1])%a[i];
	}
	return b[m];
}
int main()
{
	//freopen("input.txt","r",stdin);
	int n,m;
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
		scanf("%lld%lld",&a[i],&b[i]);
	printf("%lld\n",crt(m)); 
	return 0;
}

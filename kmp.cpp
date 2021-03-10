#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=1000005;
using namespace std;

int f[10005];
char a[10005],b[maxn];
void getfail()
{
	f[1]=0;
	int len=strlen(a+1);
	for(int i=2;i<=len;i++)
	{
		int j=f[i-1];
		while(j>0&&a[i]!=a[j+1])j=f[j];
		f[i]=a[i]==a[j+1]?j+1:0;
	}
}
void work()
{
	getfail();
	int len=strlen(b+1);
	int n=strlen(a+1);
	int j=0;
	int cnt=0;
	for(int i=1;i<=len;i++)
	{
		while(j>0&&a[j+1]!=b[i])j=f[j];
		if(b[i]==a[j+1])j++;
		if(j==n)
		{
			cnt++;
			j=f[j];
		}
	}
	printf("%d\n",cnt);
}
int main()
{
	scanf("%s%s",a+1,b+1);
	work();
	return 0;
}

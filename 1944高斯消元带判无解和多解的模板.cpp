#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=45;
using namespace std;

int a[maxn][maxn];
int n,s[maxn],t[maxn];
int gauss(int n)
{
	int r=0;
	int t=0;
	for(int i=1;i<=n;i++)//a����n*n��Ϊ����ǰ��ϵ����n+1��Ϊ��ʽ�ӵĴ� 
	{
		r=i-t;
		for(int ii=i-t+1;ii<=n;ii++)
			if(a[ii][i]>a[r][i])r=ii;
		for(int ii=i;ii<=n+1;ii++)
			swap(a[i-t][ii],a[r][ii]);
		if(a[i-t][i]==0){t++;continue;}
		for(int ii=i-t+1;ii<=n;ii++)
			if(a[ii][i]!=0)
			for(int i3=i;i3<=n+1;i3++)
				a[ii][i3]^=a[i-t][i3];
	}
	for(int i=n-t+1;i<=n;i++)
		if(a[i][n+1]!=0)return -1;//��ʱ��Щ����ǰ��δ֪��ǰ��ϵ����Ϊ0����=�ұ߲�Ϊ0,���޽⡣ 
	return t;//t��Ϊ����Ԫ���� 
}
int main()
{
	int ai,bi;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&s[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&t[i]),a[i][n+1]=s[i]^t[i],a[i][i]=1;
	while(1)
	{
		scanf("%d%d",&ai,&bi);
		if(ai==0&&bi==0)break;
		a[bi][ai]=1;
	}
	int f=gauss(n);
	if(f<0)printf("Oh,it's impossible~!!\n");
	else cout<<(1<<f)<<'\n';
	return 0;
}

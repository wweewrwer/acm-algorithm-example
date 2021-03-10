#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=105;
const double eps=1e-6;
using namespace std;

int n;
double x[maxn],a[maxn][maxn];
double fabs(double x)
{
	return x<0?-x:x;
}
//��˹��Ԫģ�壬ע�������ʱ�����о�����
//������ʱ������lcm������������ʣ��ϵ��������������� 
void gauss()
{
	int r=0;
	for(int i=1;i<=n;i++)
	{
		r=i;
		for(int ii=i;ii<=n;ii++)
			if(fabs(a[ii][i])>fabs(a[r][i]))r=ii;
		
		if(r!=i)
			for(int ii=i;ii<=n+1;ii++)
				swap(a[i][ii],a[r][ii]);
		
		for(int ii=i+1;ii<=n;ii++)
		{
			double tmp=a[ii][i]/a[i][i];
			for(int k=i;k<=n+1;k++)
				a[ii][k]=a[ii][k]-a[i][k]*tmp;
		}
	}
	
	for(int i=n;i>=1;i--)
	{
		for(int ii=n;ii>i;ii--)
			a[i][n+1]-=a[i][ii]*x[ii];
		x[i]=a[i][n+1]/a[i][i];
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int ii=1;ii<=n+1;ii++)
			scanf("%lf",&a[i][ii]);
	gauss();
	for(int i=1;i<n;i++)
		printf("%d ",(int)(x[i]+0.5));
	printf("%d\n",(int)(x[n]+0.5));
	return 0;
}

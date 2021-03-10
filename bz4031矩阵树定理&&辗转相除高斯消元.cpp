#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int mod=1e9;
using namespace std;

int n,m,mark,cb[105][105],cx[]={0,0,0,1,-1},cy[]={0,1,-1,0,0};
int c[105][105],pos[105][105];
char s[15];
int Abs(int x){return x<0?-x:x;}
void addedge(int i,int ii)
{
	int t=pos[i][ii];
	for(int i3=1;i3<=4;i3++)
	{
		int x2=i+cx[i3],y2=ii+cy[i3];
		if(cb[x2][y2])
		{
			int t2=pos[x2][y2];
			c[t][t2]=-1,c[t][t]++;//+��Ӧ��������-��Ӧ�ڽӾ��� 
		}
	}
}
//����Ԫ�����ʺ�ģ�������Ҫ������ʽ��ֵ���������� 
//����ģ������������Ԫ���ɡ�������Ҫ������ʽ��ֵ���䣬�����ȡlcm�����������Ϳ��Ա�����������ñ�ԭʽ 
void gauss(int n)
{
	int num=0;
	for(int i=1;i<=n;i++)
	{
		num=i;
		for(int ii=i+1;ii<=n;ii++)
			if(Abs(c[ii][i])>Abs(c[num][i]))num=ii;
		
		if(num!=i)
		{
			mark^=1;//��mod�����¾�Ϊ��������Ҫ������������򲢲�֪����������͸� 
			for(int ii=i;ii<=n;ii++)
				swap(c[num][ii],c[i][ii]);
		}
		for(int ii=i+1;ii<=n;ii++)
		{
			while(c[ii][i]!=0)//����շת���������ȥ���У����ﲻ��mod�ķ��������ó˵ķ�����������Щ�����Ϊ0�������⡣ 
			{
				long long tmp=c[ii][i]/c[i][i];
				for(int k=i;k<=n;k++)
					c[ii][k]=(c[ii][k]+mod-tmp*c[i][k]%mod)%mod;
				if(c[ii][i]==0)break;//��ʽע���ڴ�break 
				mark^=1;
				for(int k=i;k<=n;k++) swap(c[ii][k],c[i][k]);
			}
		}
	}
}
int main()
{
	int cnt=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		for(int ii=1;ii<=m;ii++)
		{
			if(s[ii]=='.')cb[i][ii]=1,pos[i][ii]=++cnt;
			else cb[i][ii]=0;
		}
	}
	for(int i=1;i<=n;i++)
		for(int ii=1;ii<=m;ii++)
			if(cb[i][ii])addedge(i,ii);
	gauss(cnt-1);//��ȥ���һ�� 
	long long ans=1;
	for(int i=1;i<cnt;i++)//��ȥ���һ�� 
		ans=(ans*c[i][i])%mod;
	if(mark==1)ans=mod-ans;
	ans=(ans+mod)%mod; 
	cout<<ans<<'\n';
	return 0;
}

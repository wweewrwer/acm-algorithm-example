#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=200005;
using namespace std;

int n,rank[maxn],sa[maxn];//sa���ŵ�i���±��Ƕ��٣�rank���±�Ϊi���ŵڼ� 
int x[maxn],y[maxn];
char s[maxn];
void get_rank()//�õ������ַ������� 
{
	int tot=0;
	static pair<char,int>t[maxn];
	for(int i=1;i<=n;i++)
		t[i]=make_pair(s[i],i);
	sort(t+1,t+n+1);
	for(int i=1;i<=n;i++)
	{
		if(i==1||t[i].first!=t[i-1].first)
			++tot;
		rank[t[i].second]=tot;
	}
}
void radix_sort(int key[],int order[])//��������
{
	static int sum[maxn],cnt[maxn],temp[maxn];
	
	memset(sum,0,sizeof(sum));
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=n;i++)
		sum[key[i]]++;//�������� 
	for(int i=1;i<=n;i++)
		sum[i]+=sum[i-1];//��� 
	//ԭ��˳��Ϊi�Ĺؼ��ַ��롣�����ǰ�ؼ�������֮ǰ������һ���ؼ�������֮�� 
	for(int i=1;i<=n;i++)
		temp[(++cnt[key[order[i]]])+sum[key[order[i]]-1]]=order[i];//�ѵ�ǰ��˳��һ��λ�á� 
	memcpy(order,temp,sizeof(temp));
}
void get_prefix()
{
	get_rank();
	for(int i=1;i<=n;i<<=1)
	{
		for(int ii=1;ii<=n;ii++)
		{
			x[ii]=rank[ii];//��λ 
			y[ii]=i+ii>n?0:rank[i+ii];//�ڶ�λ���� 
			sa[ii]=ii;//��Ĭ�� 
		}
		radix_sort(y,sa);//��y����С��һλ�Ĺؼ��� 
		radix_sort(x,sa);//��x���� 
		for(int ii=1,tot=0;ii<=n;ii++)
		{
			if(ii==1||x[sa[ii]]!=x[sa[ii-1]]||y[sa[ii]]!=y[sa[ii-1]])//����Ⱦͼ�
				++tot;
			rank[sa[ii]]=tot;
		}
	}
}
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	memcpy(s+n+1,s+1,n-1);
	n=n+n-1;
	get_prefix();
	for(int i=1;i<=n;i++)
		if(sa[i]+(n>>1)<=n)putchar(s[sa[i]+(n>>1)]);
	putchar('\n');
	return 0;
}

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=200005;
using namespace std;

int n,rank[maxn],sa[maxn];//sa是排第i的下标是多少，rank是下标为i的排第几 
int x[maxn],y[maxn];
char s[maxn];
void get_rank()//得到里面字符的排序 
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
void radix_sort(int key[],int order[])//基数排序
{
	static int sum[maxn],cnt[maxn],temp[maxn];
	
	memset(sum,0,sizeof(sum));
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=n;i++)
		sum[key[i]]++;//基数排序 
	for(int i=1;i<=n;i++)
		sum[i]+=sum[i-1];//求和 
	//原本顺序为i的关键字放入。求出当前关键字在它之前，和上一个关键字在它之后 
	for(int i=1;i<=n;i++)
		temp[(++cnt[key[order[i]]])+sum[key[order[i]]-1]]=order[i];//把当前的顺序换一个位置。 
	memcpy(order,temp,sizeof(temp));
}
void get_prefix()
{
	get_rank();
	for(int i=1;i<=n;i<<=1)
	{
		for(int ii=1;ii<=n;ii++)
		{
			x[ii]=rank[ii];//本位 
			y[ii]=i+ii>n?0:rank[i+ii];//第二位补零 
			sa[ii]=ii;//先默认 
		}
		radix_sort(y,sa);//按y排序小的一位的关键字 
		radix_sort(x,sa);//按x排序 
		for(int ii=1,tot=0;ii<=n;ii++)
		{
			if(ii==1||x[sa[ii]]!=x[sa[ii-1]]||y[sa[ii]]!=y[sa[ii-1]])//不相等就加
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

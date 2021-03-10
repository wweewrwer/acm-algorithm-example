#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=200015;
using namespace std;

int n,n2,sa[maxn],rank[maxn],height[maxn];
int t1[maxn],t2[maxn],sum[maxn];
char s[maxn];
void get_height()
{
	int k=0;
	for(int i=1;i<=n;i++)rank[sa[i]]=i;
	for(int i=1;i<=n;i++)
	{
		if(rank[i]==1){k=0;height[1]=0;continue;}
		if(k)k--;
		int j=sa[rank[i]-1];
		while(j+k<=n&&i+k<=n&&s[i+k]==s[j+k])k++;
		height[rank[i]]=k;
	}
}
void prefix_doubling(int m)
{
	int i,*x=t1,*y=t2;
	for(i=1;i<=m;i++)sum[i]=0;
	for(i=1;i<=n;i++)sum[x[i]=s[i]]++;
	for(i=2;i<=m;i++)sum[i]+=sum[i-1];
	for(i=n;i>=1;i--)sa[sum[x[i]]--]=i;
	
	for(int k=1;k<=n;k<<=1)
	{
		int p=0;
		for(i=n-k+1;i<=n;i++)y[++p]=i;
		for(i=1;i<=n;i++)
			if(sa[i]>k)y[++p]=sa[i]-k;
		
		for(i=0;i<=m;i++)sum[i]=0;
		for(i=1;i<=n;i++)sum[x[i]]++;
		for(i=2;i<=m;i++)sum[i]+=sum[i-1];
		for(i=n;i>=1;i--)sa[sum[x[y[i]]]--]=y[i];
		
		swap(x,y);p=1;x[sa[1]]=1;
		for(i=2;i<=n;i++)
		{
			/*x[sa[i]]=y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k]?p:++p;*/

			if(y[sa[i]]!=y[sa[i-1]]||(sa[i]+k>n?0:y[sa[i]+k])!=(sa[i-1]+k>n?0:y[sa[i-1]+k]))
				++p;
			x[sa[i]]=p;
		}
		if(p>=n)break;
		m=p;
	}
}
struct mydata
{
	int tot;
	int w;
	friend bool operator <(mydata one,mydata two)
	{
		return one.w<two.w;
	}
}sta1[maxn],sta2[maxn];
int top1=0,top2=0;
int main()
{
	freopen("input.txt","r",stdin);
	scanf("%s",s+1);
	n2=strlen(s+1);
	s[n2+1]='{';
	scanf("%s",s+n2+2);
	n=strlen(s+1);
	prefix_doubling(130);
	get_height();
	
	int maxi=0;
	for(int i=2;i<=n;i++)
		if(height[i]>height[rank[maxi]]&&((sa[i]<=n2)!=(sa[i-1]<=n2)))
			maxi=sa[i];
	printf("%d\n",height[rank[maxi]]);
	for(int i=maxi;i<maxi+height[rank[maxi]];i++)
		putchar(s[i]);
	putchar('\n');
	
	int k;
	scanf("%d",&k);k--;
	long long ans1=0,ans2=0;
	long long mytot=0;
	for(int i=1;i<=n;i++)
	{
		int tmp=0;
		while(top1!=0&&sta1[top1].w>height[i]-k)
			tmp+=sta1[top1].tot,ans1-=1ll*sta1[top1].tot*sta1[top1--].w;
		if(height[i]>k&&tmp>0)
			sta1[++top1]=(mydata){tmp,height[i]-k},ans1+=1ll*(height[i]-k)*tmp;
		
		tmp=0;
		while(top2!=0&&sta2[top2].w>height[i]-k)
			tmp+=sta2[top2].tot,ans2-=1ll*sta2[top2].tot*sta2[top2--].w;
		if(height[i]>k&&tmp>0)
			sta2[++top2]=(mydata){tmp,height[i]-k},ans2+=1ll*(height[i]-k)*tmp;
		
		if(sa[i]<=n2)
		{
			if(height[i]>k)mytot+=ans2;
			if(n2-sa[i]+1>k)
				sta1[++top1]=(mydata){1,n2-sa[i]+1-k},ans1+=n2-sa[i]+1-k;
		}
		else
		{
			if(height[i]>k)mytot+=ans1;
			if(n-sa[i]+1>k)
				sta2[++top2]=(mydata){1,n-sa[i]+1-k},ans2+=n-sa[i]+1-k;
		}
	}
	cout<<mytot<<'\n';
	return 0;
}

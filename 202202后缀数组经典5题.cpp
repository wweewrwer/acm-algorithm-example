#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=1000005;
using namespace std;

int n,rank[maxn],sa[maxn],height[maxn];
int x[maxn],y[maxn],c[maxn][23],sum[maxn];
char s[maxn];
int buf[40];
void _printf(int a)
{
	int k=0;
	if(a==0){putchar('0');putchar('\n');return;}
	if(a<0)putchar('-'),a=-a;
	while(a!=0)
	{
		buf[k++]=a%10;
		a=a/10;
	}
	for(int i=k-1;i>=0;i--)
	{
		putchar('0'+buf[i]);
	}
	putchar('\n');
}
void _scanf(int &a)
{
	a=0;
	char ch=getchar();
	int updown=0;
	while(ch<'0'||ch>'9'){if(ch=='-')updown=1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=a*10+ch-48;ch=getchar();}
	if(updown)a=-a;
}
void get_height()
{
	int k=0;
	for(int i=1;i<=n;i++)rank[sa[i]]=i;
	for(int i=1;i<=n;i++)
	{
		if(k)k--;
		int j=sa[rank[i]-1];
		while(s[i+k]==s[j+k])k++;
		height[rank[i]]=k;
	}
}
int t1[maxn],t2[maxn];
void build_sa(int m)
{
	int i,*x=t1,*y=t2;
	for(i=1;i<=m;i++)sum[i]=0;
	for(i=1;i<=n;i++)sum[x[i]=s[i]-'a'+1]++;
	for(i=2;i<=m;i++)sum[i]+=sum[i-1];
	for(i=n;i>=1;i--)sa[sum[x[i]]--]=i;
	
	for(int k=1;k<=n;k<<=1)
	{
		int p=0;
		for(i=n-k+1;i<=n;i++)y[++p]=i;
		for(i=1;i<=n;i++)
			if(sa[i]>k)y[++p]=sa[i]-k;
		
		for(i=1;i<=m;i++)sum[i]=0;
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
void get_st()
{
	for(int i=1;i<=n;i++)
		c[i][0]=height[i+1];
	for(int ii=1;ii<=20;ii++)
		for(int i=1;i<=n-(1<<ii);i++)
		c[i][ii]=min(c[i][ii-1],c[i+(1<<(ii-1))][ii-1]);
}
int main()
{
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	
	int q,ai,bi,ci,di;
	gets(s+1);
	n=strlen(s+1);
	build_sa(26);
	get_height();
	get_st();
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		_scanf(ai);_scanf(bi);
		ai++;bi++;
		if(rank[bi]<rank[ai])swap(bi,ai);
		ci=rank[bi]-rank[ai];
		int ans=n-max(ai,bi)+1;
		di=0;
		while((1<<(di+1))<=ci)di++;
		ans=min(c[rank[ai]][di],c[rank[bi]-(1<<di)][di]);
		_printf(ans);
	}
	scanf("%d",&q);
	//最长相同可重叠子串
	int ans=0;
	for(int i=1;i<=n;i++)
		ans=max(ans,height[i]);
	printf("%d\n",ans);
	
	//最长相同不重叠子串
	height[n+1]=-1;
	int l=0,r=n,mid=0;ans=0;
	while(r>=l)//二分答案，然后连续计算 
	{
		mid=(l+r)/2;
		int isok=0,maxv=sa[1],minv=sa[1];
		for(int i=2;i<=n;i++)
		{
			if(height[i]>=mid)//当一直相同时就不断更新maxv,minv。 
			{
				maxv=max(sa[i],maxv);
				minv=min(sa[i],minv);
				if(maxv-minv>=mid)isok=1;
				if(isok==1)break;
			}
			else minv=sa[i],maxv=sa[i];//不相同就重置min和max 
		}
		if(isok)
		{
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	printf("%d\n",ans);
	
	//至少出现了p次的最长重复子串（子串可重叠）
	l=0,r=n,mid=0;ans=0;
	while(r>=l)//二分算答案 
	{
		mid=(l+r)/2;
		int tot=1,isok=0;
		for(int i=2;i<=n;i++)
		{
			if(height[i]>=mid)//算tot 
			{
				tot++;
				if(tot>=q)isok=1;
				if(isok)break; 
			}
			else tot=1;
		}
		if(isok)
		{
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	printf("%d\n",ans);
	
	//计算不同的子串个数
	long long aans=(n+1ll)*n/2;
	for(int i=1;i<=n;i++)
		aans-=height[i];
	cout<<aans<<'\n';
	return 0;
}


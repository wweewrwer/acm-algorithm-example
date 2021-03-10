#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxm=100005;
const int maxn=50005;
using namespace std;

struct edge
{
	int to;
	int next;
}e[maxm<<1];
int first[maxn],np=0,n,m;
int dfn[maxn],low[maxn],dc=0,fa[maxn],f[maxn],ans=0,dep[maxn];
void addedge(int u,int v)
{
	e[++np]=(edge){v,first[u]};
	first[u]=np;
}
int a[maxn<<1];
int qu[maxn<<1],front=0,rear=0;
void dp(int x,int now)
{
	int tot=dep[x]-dep[now]+1;//倍增破环 
	for(int i=x;i!=now;i=fa[i])
		a[tot--]=f[i];
	a[tot]=f[now];
	tot=dep[x]-dep[now]+1;
	for(int i=1;i<=tot;i++)
		a[i+tot]=a[i];
	
	qu[1]=1;front=1,rear=2;
	for(int i=2;i<=2*tot;i++)
	{
		while(rear>front&&i-qu[front]>tot/2)front++;
		
		if(rear>front)ans=max(ans,i-qu[front]+a[i]+a[qu[front]]);
		
		while(rear>front&&a[i]-a[qu[rear-1]]>=i-qu[rear-1])rear--;
		qu[rear++]=i;
	}
	
	for(int i=2;i<=tot;i++)//更新f[root]的值。 
		f[now]=max(f[now],a[i]+min(i-1,tot-i+1));
}
void dfs(int now)
{
	dfn[now]=low[now]=++dc;
	for(int p=first[now];p!=0;p=e[p].next)
	{
		int j=e[p].to;
		if(j==fa[now])continue;
		if(dfn[j])
		{
			low[now]=min(low[now],dfn[j]);
			continue;
		}
		fa[j]=now;
		dep[j]=dep[now]+1;
		dfs(j);
		low[now]=min(low[now],low[j]);
		if(low[j]>dfn[now])//若不成环，则像树一样进行 
		{
			ans=max(ans,f[j]+1+f[now]);
			f[now]=max(f[now],f[j]+1);
		}
	}
	for(int p=first[now];p!=0;p=e[p].next)//若成环，忽视环上的长度，只允许环外的长度 
	{
		int j=e[p].to;//此时now为环的父亲 
		if(fa[j]!=now&&dfn[now]<dfn[j])
			dp(j,now);
	}
}
int main()
{
	int ai,bi,k;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&k);
		ai=0;
		for(int ii=1;ii<=k;ii++)
		{
			scanf("%d",&bi);
			if(ai!=0)
			{
				addedge(ai,bi);
				addedge(bi,ai);
			}
			ai=bi;
		}
	}
	dfs(1);
	printf("%d\n",ans);
	return 0;
}

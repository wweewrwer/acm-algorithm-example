#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=1005;
using namespace std;

struct edge
{
	int to;
	int next;
}e[maxn<<1];
int first[maxn],np,n,b;
void addedge(int u,int v)
{
	e[++np]=(edge){v,first[u]};
	first[u]=np;
}
int belong[maxn],rt[maxn],s[maxn],top=0,cnt=0;
void dfs(int now,int fa)
{
	int bot=top;
	for(int p=first[now];p!=0;p=e[p].next)
	{
		int j=e[p].to;
		if(j==fa)continue;
		dfs(j,now);
		if(top-bot>=b)
		{
			rt[++cnt]=now;
			while(top!=bot)
			{
				belong[s[top--]]=cnt;
			}
		}
	}
	s[++top]=now;
}
int main()
{
	int ai,bi;
	scanf("%d%d",&n,&b);
	for(int i=2;i<=n;i++)
	{
		scanf("%d%d",&ai,&bi);
		addedge(ai,bi);
		addedge(bi,ai);
	}
	dfs(1,0);
	if(n==b)
	{
		cnt=1;
		rt[cnt]=1;
	}
	while(top!=0)belong[s[top--]]=cnt;
	printf("%d\n",cnt);
	for(int i=1;i<=n;i++)
	{
		printf("%d ",belong[i]);
	}
	printf("\n");
	for(int i=1;i<=cnt;i++)
	{
		printf("%d ",rt[i]);
	}
	printf("\n");
	return 0;
}

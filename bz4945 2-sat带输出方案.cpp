#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>

using namespace std;

struct edge
{
	int to,next;
};
int n,m,d;
int ts[50005];
struct mytree
{
	static const int maxn=160005;
	static const int maxm=600005;
	edge e[maxm];
	int np,first[maxn],dfn[maxn],low[maxn],dc,belong[maxn],sta[maxn],top,ebc;
	void addedge(int u,int v)
	{
		e[++np]=(edge){v,first[u]};
		first[u]=np;
	}
	void dfs(int now)
	{
		sta[++top]=now;
		dfn[now]=low[now]=++dc;
		for(int p=first[now];p!=0;p=e[p].next)
		{
			int j=e[p].to;
			if(dfn[j])
			{
				if(!belong[j])low[now]=min(low[now],dfn[j]);
				continue;
			}
			dfs(j);
			low[now]=min(low[now],low[j]);
		}
		if(dfn[now]==low[now])
		{
			ebc++;
			while(1)
			{
				belong[sta[top]]=ebc;
				if(sta[top--]==now)break;
			}
		}
	}
	int work()
	{
		int last=0;
		for(int i=1;i<=n;i++)
		{
			for(int ii=1;ii<=3;ii++)
			{
				if(ts[i]==ii)continue;
				int t=(i-1)*3+ii;
				if(!dfn[t])dfs(t);
				int t2=(i-1)*3+6-ii-ts[i];
				if(!dfn[t2])dfs(t2);
				if(belong[t]==belong[t2])return 0;
				break;
			}
		}
		return 1;
	}
	void putans()
	{
		int last=0;
		for(int i=1;i<=3*n;i++)
		{
			if(!dfn[i])continue;
			if(last==0)last=i;
			else
			{
				if(belong[last]<belong[i])putchar('A'+(last-1)%3);
				else putchar('A'+(i-1)%3);
				last=0;
			}
		}
		putchar('\n');
	}
	void ready()
	{
		dc=0;ebc=0;np=0;top=0;
		memset(dfn,0,sizeof(dfn));
		memset(belong,0,sizeof(belong));
		memset(first,0,sizeof(first));
		memset(low,0,sizeof(low));
	}
}e;
const int maxn=50005;
const int maxm=100005;
struct abc
{
	int ai;
	int ai2;
	int bi;
	int bi2;
}mp[maxm];
int cx[maxn],flag=0;
char s[maxn],s1[15],s2[15];
void makepic()
{
	for(int i=1;i<=m;i++)
	{
		int ai=mp[i].ai,bi=mp[i].bi,ai2=mp[i].ai2,bi2=mp[i].bi2;
		if(ai2==ts[ai])continue;
		if(bi2==ts[bi])
		{
			e.addedge((ai-1)*3+ai2,(ai-1)*3+6-ai2-ts[ai]);
			continue;
		}
		e.addedge((ai-1)*3+ai2,(bi-1)*3+bi2);
		e.addedge((bi-1)*3+6-bi2-ts[bi],(ai-1)*3+6-ai2-ts[ai]);
	}
}
void dfs(int now)
{
	if(flag)return;
	if(now>d)
	{
		e.ready();
		makepic();
		flag=e.work();
		if(flag)e.putans();
		return;
	}
	ts[cx[now]]=1;dfs(now+1);
	ts[cx[now]]=2;dfs(now+1);
}
int main()
{
	scanf("%d%d",&n,&d);
	scanf("%s",s+1);
	scanf("%d",&m);
	d=0;
	int ai,bi;
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='x')cx[++d]=i;
		else ts[i]=s[i]-'a'+1;
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%s%d%s",&ai,s1+1,&bi,s2+1);
		int ai2=s1[1]-'A'+1,bi2=s2[1]-'A'+1;
		mp[i]=(abc){ai,ai2,bi,bi2};
	}
	dfs(1);
	if(flag==0)printf("-1\n");
	return 0;
}

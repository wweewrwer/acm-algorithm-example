#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>

const int maxn=1005;
const int maxm=3005;
using namespace std;

struct edge
{
	int to,next,w;
}e[maxm<<1];
int np=0,first[maxn];
void addedge(int u,int v,int w)
{
	e[++np]=(edge){v,first[u],w};
	first[u]=np;
}
int vis[maxn][2050],g[1050];
int inq[maxn];
int st[15];
int n,m,tot;
queue<int>q;
void spfa(int sub)
{
	while(!q.empty())
	{
		int k=q.front();q.pop();
		inq[k]=0;
		for(int p=first[k];p!=0;p=e[p].next)
		{
			int j=e[p].to;
			if(e[p].w+vis[k][sub]<vis[j][sub])
			{
				vis[j][sub]=vis[k][sub]+e[p].w;
				if(!inq[j])q.push(j),inq[j]=1;
			}
		}
	}
}
void steiner()
{
	for(int ii=1;ii<(1<<n);ii++)
	{
		int tmp=vis[0][0];
		for(int i=1;i<=tot;i++)
		{
			for(int sub=((ii-1)&ii);sub!=0;sub=((sub-1)&ii))//斯坦纳树的转移，注意根不一定要在集合中 
			{
				if(vis[i][sub]+vis[i][ii^sub]<vis[i][ii])
				{
					vis[i][ii]=vis[i][sub]+vis[i][ii^sub];
				}
			}
			if(vis[i][ii]!=0x3f3f3f3f)
			{
				tmp=min(tmp,vis[i][ii]);
				q.push(i);
				inq[i]=1;
			}
		}
		spfa(ii);//转移根，通过这步实现根不在集合中也能转移 
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int ai,bi,ci;
	scanf("%d%d%d",&tot,&m,&n);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&ai,&bi,&ci);
		addedge(ai,bi,ci);
		addedge(bi,ai,ci);
	}
	memset(vis,0x3f,sizeof(vis));
	memset(g,0x3f,sizeof(g));
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&ai,&bi);
		vis[bi][1<<(i-1)]=0;//斯坦纳树的初始； 
		st[ai]=(st[ai]|(1<<(i-1)));
	}
	steiner();//斯坦纳树，实质为状压dp； 
	for(int i=1;i<=10;i++)
	{
		if(st[i]==0)continue;
		for(int ii=1;ii<=tot;ii++)
		g[st[i]]=min(g[st[i]],vis[ii][st[i]]);
	}
	for(int i=1;i<(1<<n);i++)
	{
		for(int sub=(i&(i-1));sub!=0;sub=((sub-1)&i))
		{
			g[i]=min(g[i],g[sub]+g[i^sub]);
		}
		if(g[i]!=0x3f3f3f3f)
		{
			for(int ii=1;ii<=tot;ii++)
			{
				g[i]=min(g[i],vis[ii][i]);//此题的关键，一些状态可能直接连更优 
			}
		}
	}
	printf("%d\n",g[(1<<n)-1]);
	return 0;
}

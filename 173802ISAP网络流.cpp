#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>

const int maxn=2005;
const int maxm=200005;
using namespace std;

struct edge
{
	int from,to,cap,flow,next;
};
int inf=1e7;
struct isap
{
	int n,m,s,t;
	int np,first[maxn],num[maxn],d[maxn],cur[maxn],fa[maxn];
	bool vis[maxn];
	edge e[maxm<<1];
	int other(int p)
	{
		return p&1?p+1:p-1;
	}
	void addedge(int u,int v,int w)
	{
		e[++np]=(edge){u,v,w,0,first[u]};
		first[u]=np;
		e[++np]=(edge){v,u,0,0,first[v]};
		first[v]=np;
	}
	void bfs()
	{
		memset(vis,0,sizeof(vis));
		//memset(d,-1,sizeof(d));
		memset(num,0,sizeof(num));
		for(int i=1;i<=n;i++)d[i]=n;
		
		queue<int>q;
		q.push(t);
		d[t]=0;
		num[0]=1;
		
		vis[t]=1;
		while(!q.empty())
		{
			int k=q.front();q.pop();
			for(int p=first[k];p!=0;p=e[p].next)
			{
				int j=e[p].to;
				int p2=other(p);
				if(!vis[j]&&e[p2].cap>e[p2].flow)
				{
					vis[j]=1;
					d[j]=d[k]+1;
					num[d[j]]++;
					q.push(j);
				}
			}
		}
	}
	int augment()
	{
		int x=t,a=inf;
		while(x!=s)
		{
			a=min(a,e[fa[x]].cap-e[fa[x]].flow);
			x=e[fa[x]].from;
		}
		x=t;
		while(x!=s)
		{
			e[fa[x]].flow+=a;
			e[other(fa[x])].flow-=a;
			x=e[fa[x]].from;
		}
		return a;
	}
	int maxflow(int s,int t)
	{
		this->s=s;
		this->t=t;
		int flow=0;
		bfs();
		
		//memset(num,0,sizeof(num));
		//for(int i=1;i<=n;i++)num[d[i]]++;
		
		int x=s;
		memcpy(cur,first,sizeof(cur[0])*(n+1));
		while(d[s]<n)
		{
			if(x==t)
			{
				flow+=augment();
				x=s;
			}
			int ok=0;
			for(int p=cur[x];p!=0;p=e[p].next)
			{
				int j=e[p].to;
				if(e[p].cap>e[p].flow&&d[x]==d[j]+1)
				{
					ok=1;
					cur[x]=p;
					fa[j]=p;
					x=j;
					break;
				}
			}
			if(!ok)
			{
				int md=n-1;
				for(int p=first[x];p!=0;p=e[p].next)
				{
					int j=e[p].to;
					if(e[p].cap>e[p].flow)md=min(md,d[j]);
				}
				num[d[x]]--;
				if(num[d[x]]==0)return flow;
				d[x]=md+1;
				num[d[x]]++;
				cur[x]=first[x];
				if(x!=s)x=e[fa[x]].from;
			}
		}
		return flow;
	}
}e;
int main()
{
	//freopen("maxflow.in","r",stdin);
	int ai,bi,ci;
	scanf("%d%d",&e.m,&e.n);
	for(int i=1;i<=e.m;i++)
	{
		scanf("%d%d%d",&ai,&bi,&ci);
		e.addedge(ai,bi,ci);
	}
	printf("%d\n",e.maxflow(1,e.n));
	return 0;
}

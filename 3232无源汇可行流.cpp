#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>

const int maxn=305;
const int maxm=20005;
using namespace std;

struct edge
{
	int from,to,next,cap,flow;
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
		e[++np]=(edge){u,v,first[u],w,0};
		first[u]=np;
		e[++np]=(edge){v,u,first[v],0,0};
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
	void ready()
	{
		np=0;
		memset(first,0,sizeof(first));
	}
}e;
int a[maxn];
int main()
{
	int cas,ai,bi,ci,di;
	scanf("%d",&cas);
	for(int i=1;i<=cas;i++)
	{
		memset(a,0,sizeof(a));
		e.ready();
		int n,m,s,t;
		scanf("%d%d",&n,&m);
		s=n+1;t=n+2;
		//有无源汇的可行流其实就是先默认下界，对于不守恒的点
		//这里有一个值得思考的点，若流入>流出，到底是s向其连边还是其向t连边呢？
		//应为s向其连边，因为我们是要让它多流出来平衡，而网络流算法是流量守恒的
		//那么显然我们应流入一些虚的流量让其流出已达到平衡，若流出>流入显然同理 
		for(int ii=1;ii<=m;ii++)
		{
			scanf("%d%d%d%d",&ai,&bi,&ci,&di);
			e.addedge(ai,bi,di-ci);
			a[ai]-=ci; a[bi]+=ci;
		}
		int sum=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]>0)
				e.addedge(s,i,a[i]),sum+=a[i];
			else
				e.addedge(i,t,-a[i]);
		}
		e.n=t;
		if(e.maxflow(s,t)==sum)printf("Yes\n");
		else printf("No\n");
	}	
	return 0;
}

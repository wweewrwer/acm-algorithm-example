#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>

const int maxn=505;
const int maxm=110005;
using namespace std;

struct edge
{
	int from,to,next;
	long long cap,flow;
};
long long inf=1e10;
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
	void addedge(int u,int v,long long w)
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
	long long augment()
	{
		int x=t;long long a=inf;
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
	long long maxflow(int s,int t)
	{
		this->s=s;
		this->t=t;
		long long flow=0;
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
long long a[maxn];
int main()
{
	int ai,bi,ci,di;
	int n,m,s,t;
	scanf("%d%d",&n,&m);
	s=n+1;t=n+2;
	for(int ii=1;ii<=m;ii++)
	{
		scanf("%d%d%d%d",&ai,&bi,&ci,&di);
		e.addedge(ai,bi,di-ci);
		a[ai]-=ci; a[bi]+=ci;
	}
	long long sum=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]>0)
			e.addedge(s,i,a[i]),sum+=a[i];
		else
			e.addedge(i,t,-a[i]);
	}
	e.n=t;
	e.addedge(n,1,inf);
	//有源汇的最大流就是先跑可行流，然后删t到s的路，此时是流量守恒的，
	//此时就可以跑s到t的最大流了，因为虚ss和虚tt没有办法退流，
	//故此时直接跑最大流再加上之前的就可以了。 
	if(e.maxflow(s,t)==sum)
	{
		int id=e.np-1;
		long long flow=e.e[id].flow;
		e.e[id].flow=e.e[id].cap=e.e[e.other(id)].flow=e.e[e.other(id)].cap=0;
		flow+=e.maxflow(1,n);
		cout<<flow<<'\n';
	}
	else printf("0\n");
	return 0;
}

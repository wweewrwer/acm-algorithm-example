#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>

const int maxm=1100005;
const int maxn=20005;
using namespace std;

struct edge
{
	int from,to,next,cap,flow,cost;
};
int cb[105][105],inm[maxm<<1];
int inf=200005,finf=20;
struct myek
{
	edge e[maxm<<1];
	int n,m,s,t,np,btop;
	int first[maxn],inq[maxn],d[maxn],a[maxn],fa[maxn];
	void addedge(int u,int v,int cap,int cost)
	{
		e[++np]=(edge){u,v,first[u],cap,0,cost};
		first[u]=np;
		e[++np]=(edge){v,u,first[v],0,0,-cost};
		first[v]=np;
	}
	int other(int x)
	{
		return x&1?x+1:x-1;
	}
	int spfa()
	{
		for(int i=1;i<=n;i++)d[i]=inf;
		for(int i=1;i<=n;i++)a[i]=0;
		
		queue<int>q;
		q.push(s);
		d[s]=0;
		inq[s]=1;
		a[s]=finf;
		while(!q.empty())
		{
			int k=q.front();q.pop();
			inq[k]=0;
			for(int p=first[k];p!=0;p=e[p].next)
			{
				int j=e[p].to;
				if(e[p].cap>e[p].flow&&d[j]>d[k]+e[p].cost)
				{
					d[j]=d[k]+e[p].cost;
					fa[j]=p;
					a[j]=min(a[k],e[p].cap-e[p].flow);
					if(!inq[j])
					{
						inq[j]=1;
						q.push(j);
					}
				}
			}
		}
		return a[t];
	}
	void update(int p)//若不会超时，则不用动态加边 
	{
		if(inm[p]%btop!=0)
		{
			int k=inm[p]%btop+1;
			int w=(inm[p]-1)/btop;
			for(int i=1;i<=btop;i++)
			{
				addedge(i,inm[p]+1,1,k*cb[i][w]);
			}	
			inm[p]=0;
		}
	}
	int maxflow(int s,int t)
	{
		this->s=s;
		this->t=t;
		
		int flow=0,cost=0;
		int delt=0;
		while(1)
		{
			delt=spfa();
			if(delt==0)break;
			flow+=delt;
			cost+=delt*d[t];
			int x=t;
			while(x!=s)
			{
				//动态加边的位置，即手动考虑某些边一定是在一些边满流后才会走，那么满流后再加入 
				update(fa[x]); 
				e[fa[x]].flow+=delt;
				e[other(fa[x])].flow-=delt;
				x=e[fa[x]].from;
			}
		}
		return cost;
	}
}e;
int main()
{
	freopen("order.in","r",stdin);
	//freopen("order.out","w",stdout);
	int n,m;//n为商品 
	scanf("%d%d",&n,&m);
	int s=n*(m+1)+1,t=n*(m+1)+2,btop=n;
	int ai;
	for(int i=1;i<=n;i++)
	{
		e.addedge(s,i,1,0);
		for(int ii=1;ii<=m;ii++)
		{
			scanf("%d",&cb[i][ii]);
			e.addedge(i,btop+(ii-1)*n+1,1,1*cb[i][ii]);
		}
	}
	for(int i=1;i<=m;i++)
	{
		for(int ii=1;ii<=n;ii++)
		{
			e.addedge(btop+(i-1)*n+ii,t,1,0);
			inm[e.np-1]=btop+(i-1)*n+ii;
		}
	}
	e.n=t;e.m=m;e.btop=n;
	printf("%.2lf\n",(double)e.maxflow(s,t)/n);
	return 0;
}

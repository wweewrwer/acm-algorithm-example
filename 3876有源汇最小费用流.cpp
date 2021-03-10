#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>

const int maxn=405;
const int maxm=15005;
using namespace std;

struct edge
{
	int from,to,next,cap,flow,cost;
};
int inf=300000005,dinf=-1000000,finf=5005;
struct myek
{
	edge e[maxm<<1];
	int s,t,n,m,np;
	int first[maxn],fa[maxn],a[maxn],inq[maxn],d[maxn];
	int other(int x)
	{
		return x&1?x+1:x-1;
	}
	void addedge(int u,int v,int cap,int cost)
	{
		e[++np]=(edge){u,v,first[u],cap,0,cost};
		first[u]=np;
		e[++np]=(edge){v,u,first[v],0,0,-cost};
		first[v]=np;
	}
	int spfa()
	{
		for(int i=1;i<=n;i++)d[i]=inf;
		memset(a,0,sizeof(a));
		
		queue<int>q;
		q.push(s);
		d[s]=0;
		a[s]=finf;
		inq[s]=1;
		fa[s]=0;
		while(!q.empty())
		{
			int k=q.front();q.pop();
			inq[k]=0;
			for(int p=first[k];p!=0;p=e[p].next)
			{
				int j=e[p].to;
				if(e[p].cap>e[p].flow&&d[j]>d[k]+e[p].cost)
				{
					fa[j]=p;
					d[j]=d[k]+e[p].cost;
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
	int maxflow(int s,int t)
	{
		this->s=s;
		this->t=t;
		
		int cost=0;
		int flow=0,delt=0;
		while(1)
		{
			delt=spfa();
			if(delt==0)break;
			flow+=delt;
			cost+=delt*d[t];
			int x=t;
			while(x!=s)
			{
				e[fa[x]].flow+=delt;
				e[other(fa[x])].flow-=delt;
				x=e[fa[x]].from;
			}
		}
		return cost;
	}
}e;
int a[maxn];
int main()
{
	freopen("story.in","r",stdin);
	//freopen("story.out","w",stdout);
	int n,k,ai,bi;
	scanf("%d",&n);
	int ss=n+1,t=n+2,tt=n+3,s=n+4;
	int tot2=0,sum=0;
	e.addedge(s,1,finf,0);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&k);
		e.addedge(i,t,finf,0);
		tot2+=k;
		a[i]-=k;
		for(int ii=1;ii<=k;ii++)
		{
			scanf("%d%d",&ai,&bi);
			e.addedge(i,ai,finf,bi);
			sum+=bi;
			a[ai]++;
		}
	}
	e.addedge(t,s,finf,0);
	for(int i=1;i<=n;i++)
	{
		if(a[i]>0)e.addedge(ss,i,a[i],0);
		else if(a[i]<0)e.addedge(i,tt,-a[i],0);
	}
	e.n=s;
	//最小费最小流直接跑即可。不用再从tt跑到ss即可。因为这样就已经是合法的最小费用流了，若在从t跑到s,会把原来没有满的盛满，导致问题的出现。 
	cout<<sum+e.maxflow(ss,tt)<<'\n';
	return 0;
}

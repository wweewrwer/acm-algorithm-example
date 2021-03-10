#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
const int maxn=600005;
const int maxm=600005;
using namespace std;

int buf[40];
void _printf(long long a)
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
int ecc=0,fa[maxn][20];
long long sum[maxn],posi[maxn],dist[maxn],dep[maxn];
struct edge
{
	int to;
	int next;
	long long w;
};
struct point
{
	long long id;
	long long w;
	friend bool operator <(const point &one,const point &two)
	{
		return one.w<two.w;
	}
	friend bool operator ==(const point &one,const point &two)
	{
		return one.w==two.w;
	}
}a[maxn];
struct ftree
{
	edge e[maxm];point h[maxn];
	int first[maxn],np,n,q[maxn];
	long long f[maxn];
	void addedge(int u,int v,long long w)
	{
		//if(inq[u]!=tt)inq[u]=tt,first[u]=f[u]=0;
		//if(inq[v]!=tt)inq[v]=tt,first[v]=f[v]=0;
		//printf("%d->%d %lld\n",u,v,w);
		e[++np]=(edge){v,first[u],w};
		first[u]=np;
	}
	int climb(int x,int k)//±¶Ôök´Î 
	{
  		int i=0;
   		while (k)
    	{
    	    if (k&1) x=fa[x][i];
       		k>>=1;i++;
    	}
    	return x;
	}
	long long dfs(int now)
	{
		//if(inq[now]!=tt)inq[now]=tt,first[now]=0;
		f[now]=0;
		long long ans=0;
		for(int p=first[now];p!=0;p=e[p].next)
		{
			int j=e[p].to;
			ans=max(ans,dfs(j));
			if(a[now].id<=n)ans=max(ans,f[now]+f[j]+e[p].w);
			f[now]=max(f[now],f[j]+e[p].w);
		}
		if(a[now].id>n)
		{
			int top=0;
			for(int p=first[now];p!=0;p=e[p].next)
			{
				int j=e[p].to;
				int x=climb(a[j].id,dist[a[j].id]-dist[a[now].id]-1);
				h[++top]=(point){f[j]+dep[a[j].id]-dep[x],posi[x]};
			}
			sort(h+1,h+top+1);
			for(int i=1;i<=top;i++)
				h[i+top]=(point){h[i].id,sum[a[now].id]+h[i].w};
			
			/*putchar('\n');
			for(int i=1;i<=2*top;i++)
				printf("%lld %lld\n",h[i].w,h[i].id);*/
			
			int front=1,rear=2;q[1]=1;
			for(int i=2;i<=top*2;i++)
			{
				while(rear>front&&(h[i].w-h[q[front]].w)*2>sum[a[now].id])front++;
				if(rear>front)ans=max(ans,h[i].w-h[q[front]].w+h[i].id+h[q[front]].id);
				
				while(rear>front&&h[i].id-h[q[rear-1]].id>=h[i].w-h[q[rear-1]].w)rear--;
				q[rear++]=i;
			}
		}
		return ans;
	}
	void ready(int n)
	{
		np=0;
		memset(first,0,sizeof(first[0])*(n+1));
	}
}ft;
struct mytree
{
	edge e[maxm<<1];
	int first[maxn],np,s[maxn],nt,b[maxn],c[maxn],top,tot;
	void addedge(int u,int v,long long w)
	{
		e[++np]=(edge){v,first[u],w};
		first[u]=np;
		//printf("%d->%d %d\n",u,v,w);
	}
	void dfs(int now)
	{
		s[now]=++nt;
		for(int i=1;i<=18;i++)
			fa[now][i]=fa[fa[now][i-1]][i-1];
		for(int p=first[now];p!=0;p=e[p].next)
		{
			int j=e[p].to;
			if(j==fa[now][0])continue;
			fa[j][0]=now;
			dep[j]=dep[now]+e[p].w;
			dist[j]=dist[now]+1;
			dfs(j);
		}
	}
	void treepop()
	{
		if(c[top]!=a[b[top-1]].id)
		{
			a[++tot]=(point){c[top],s[c[top]]};
			ft.addedge(tot,b[top],dep[a[b[top]].id]-dep[c[top]]);
			ft.addedge(tot,b[top-1],dep[a[b[top-1]].id]-dep[c[top]]);
			b[top-1]=tot;
		}
		else
			ft.addedge(b[top-1],b[top],dep[a[b[top]].id]-dep[a[b[top-1]].id]);
		top--;
		if(top>1)c[top]=lca(a[b[top]].id,a[b[top-1]].id);
	}
	int lca(int u,int v)
	{
		if(dist[u]<dist[v])swap(u,v);
		
		int len=dist[u]-dist[v];
		for(int i=0;i<=18;i++)
		{
			if(len&(1<<i))
				u=fa[u][i];
		}
		if(u==v)return u;
		
		for(int i=18;i>=0;i--)
		{
			if(fa[u][i]!=fa[v][i])
			{
				u=fa[u][i];
				v=fa[v][i];
			}
		}
		return fa[u][0];
	}
	void makeft()
	{
		//printf("!\n!\n!\n");
		ft.ready(tot);
		int cnt=0,ai=0;
		_scanf(cnt);
		for(int i=1;i<=cnt;i++)
		{
			_scanf(ai);
			a[i]=(point){ai,s[ai]};
		}
		sort(a+1,a+cnt+1);top=0;
		cnt=unique(a+1,a+cnt+1)-a;
		tot=--cnt;
		b[++top]=1;
		for(int i=2;i<=cnt;i++)
		{
			while(top>1&&dist[c[top]]>=dist[lca(a[b[top]].id,a[i].id)])treepop();
			b[++top]=i;
			c[top]=lca(a[i].id,a[b[top-1]].id);
		}
		while(top>1)treepop();
		_printf(ft.dfs(b[1]));
	}
}te;
struct mycactus
{	
	edge e[maxm<<1];
	int first[maxn],np,n;
	int dfn[maxn],low[maxn],sta[maxn],top,dc;
	long long ste[maxn];
	void addedge(int u,int v,long long w)
	{
		e[++np]=(edge){v,first[u],w};
		first[u]=np;
	}
	void dfs(int now,int fd)
	{
		sta[++top]=now;
		dfn[now]=low[now]=++dc;
		for(int p=first[now];p!=0;p=e[p].next)
		{
			int j=e[p].to;
			if(p==fd)continue;
			if(!dfn[j])
			{
				ste[top]=e[p].w;
				dfs(j,p&1?p+1:p-1);
				low[now]=min(low[now],low[j]);
				if(low[j]==dfn[j])
					te.addedge(now,j,e[p].w); 
			}
			else
			{
				if(dfn[j]<dfn[now])
				{
					int btop=top;
					for(;sta[btop]!=j;btop--)continue;
					++ecc;
					sum[ecc]=e[p].w;
					for(int i=btop;i<top;i++)sum[ecc]+=ste[i];
					
					long long su=0;
					te.addedge(j,ecc,0);
					for(int i=btop;i<top;i++)
					{
						su+=ste[i];
						posi[sta[i+1]]=su;
						te.addedge(ecc,sta[i+1],min(sum[ecc]-su,su));
					}
				}
				low[now]=min(low[now],dfn[j]);
			}
		}
		top--;
	}
}tc;
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int ai,bi,ci,n,m,q;
	_scanf(n);_scanf(m);
	tc.n=n;
	ecc=n;
	ft.n=n;
	for(int i=1;i<=m;i++)
	{
		_scanf(ai);
		_scanf(bi);
		_scanf(ci);
		tc.addedge(ai,bi,ci);
		tc.addedge(bi,ai,ci);
	}
	tc.dfs(1,0);
	te.dfs(1);
	_scanf(q);
	for(int i=1;i<=q;i++)
		te.makeft();
	return 0;
}

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

const int maxn=100005;
using namespace std;

void _scanf(int &a)
{
	a=0;
	char ch=getchar();
	int updown=0;
	while(ch<'0'||ch>'9'){if(ch=='-')updown=1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=a*10+ch-48;ch=getchar();}
	if(updown)a=-a;
}
struct edge
{
	int to;
	int next;
}e[maxn<<1];
int first[maxn],np,n,m,qt;
void addedge(int u,int v)
{
	e[++np]=(edge){v,first[u]};
	first[u]=np;
}

int s[maxn]/*s&e of point*/,v[maxn],vw[maxn],top=0,vw2[maxn],sta[maxn];
long long w[maxn];//the xinqi
int fa[maxn][21],dist[maxn],tt=0,sn=0,belong[maxn],tn=0;
void dfs(int now)
{
	int bot=top;
	s[now]=++tt;
	for(int i=1;i<=17;i++)
	{
		fa[now][i]=fa[fa[now][i-1]][i-1];
	}
	for(int p=first[now];p!=0;p=e[p].next)
	{
		int j=e[p].to;
		if(j==fa[now][0])continue;
		dist[j]=dist[now]+1;
		fa[j][0]=now;
		dfs(j);
		if(top-bot>=sn)//树上莫队依赖于国王游戏的分法P1086 
		{
			tn++;
			while(top!=bot)
			{
				belong[sta[top--]]=tn;
			}
		}
	}
	sta[++top]=now;
}
int lca(int u,int v)
{
	if(dist[u]<dist[v])swap(u,v);
	
	int len=dist[u]-dist[v];
	for(int i=0;i<=17;i++)
	{
		if(len&(1<<i))
		{
			u=fa[u][i];
		}
	}
	if(u==v)return u;
	
	for(int i=17;i>=0;i--)
	{
		if(fa[u][i]!=fa[v][i])
		{
			u=fa[u][i];
			v=fa[v][i];
		}
	}
	return fa[u][0];
}
struct mydata
{
	int id;
	int t;
	int l;
	int r;
	friend bool operator <(mydata one,mydata two)//一般有错都是在莫队的比较函数，仔细想一想 
	{
		if(belong[one.l]!=belong[two.l])return belong[one.l]<belong[two.l];
		if(belong[one.r]!=belong[two.r])return belong[one.r]<belong[two.r];
		return one.t<two.t;
	}
}q[maxn],ch[maxn];//q question,ch change;
int np2=0,g[maxn];
int inq[maxn];
long long ans[maxn];//keep answer
long long myans=0;
long long tttt;
void chd(int wh,int d)//time.change;
{
	int ww=ch[wh].l;
	if(inq[ww])
	{
		myans-=w[g[vw[ww]]]*v[vw[ww]];
		g[vw[ww]]--;
		myans+=w[g[vw[ww]]]*v[vw[ww]];
	}
	if(d==1)
	{
		vw[ww]=ch[wh].r;
	}
	else
	{
		vw[ww]=ch[wh].id;
	}
	if(inq[ww])
	{
		myans-=w[g[vw[ww]]]*v[vw[ww]];
		g[vw[ww]]++;
		myans+=w[g[vw[ww]]]*v[vw[ww]];
	}
}
void upd(int wh)
{
	myans-=w[g[vw[wh]]]*v[vw[wh]];
	inq[wh]^=1;
	if(inq[wh]==0)g[vw[wh]]-=1;
	if(inq[wh]==1)g[vw[wh]]+=1;
	myans+=w[g[vw[wh]]]*v[vw[wh]];
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int ai,bi,ci;
	scanf("%d%d%d",&n,&m,&qt);
	sn=pow(n,2.0/3.0)+0.000005;
	for(int i=1;i<=m;i++)
	{
		_scanf(v[i]);
	}
	for(int i=1;i<=n;i++)
	{
		_scanf(ai);
		w[i]=w[i-1]+ai;
	}
	for(int i=1;i<n;i++)
	{
		_scanf(ai);
		_scanf(bi);
		addedge(ai,bi);
		addedge(bi,ai);
	}
	dfs(1);
	while(top!=0)belong[sta[top--]]=tn;
	
	for(int i=1;i<=n;i++)
	{
		_scanf(vw[i]);
		vw2[i]=vw[i];
	}
	int tot=0;
	int tot2=0;
	for(int i=1;i<=qt;i++)
	{
		_scanf(ai);
		_scanf(bi);
		_scanf(ci);
		if(ai==0)
		{
			ch[++tot2]=(mydata){vw2[bi],i,bi,ci};
			vw2[bi]=ci;
		}
		else if(ai==1)
		{
			if(s[bi]>s[ci])swap(bi,ci);
			q[++tot]=(mydata){tot,i,bi,ci};
		}
	}
	qt=tot;
	sort(q+1,q+qt+1);
	/*for(int i=1;i<=qt;i++)
	{
		printf("%d %d %d\n",belong[q[i].l],belong[q[i].r],q[i].t);
	}*/
	int l=1,r=1,t=0;//树上移动依赖于T(u,nowv)=T(nowu,nowv)^T(nowu,u); 
	for(int i=1;i<=qt;i++)//莫队主程序易错，每步都应推敲 
	{
		for(;q[i].t>ch[t+1].t&&t<tot2;t++)chd(t+1,1);
		for(;q[i].t<ch[t].t;t--)chd(t,-1); 
		
		int mylca=lca(q[i].l,l);//依次取反即可 
		for(;l!=mylca;l=fa[l][0])upd(l);
		for(l=q[i].l;l!=mylca;l=fa[l][0])upd(l);
		l=q[i].l;
		
		mylca=lca(q[i].r,r);
		for(;r!=mylca;r=fa[r][0])upd(r);
		for(r=q[i].r;r!=mylca;r=fa[r][0])upd(r);
		r=q[i].r;
		
		mylca=lca(l,r);
		upd(mylca);
		
		ans[q[i].id]=myans;
		
		upd(mylca);
	}
	//cout<<tttt<<'\n';
	
	for(int i=1;i<=qt;i++)
	{
		printf("%lld\n",ans[i]);
	}
	return 0;
}

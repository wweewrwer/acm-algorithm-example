#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=150005;
const int maxh=105;
using namespace std;

void _scanf(int &a)
{
	a=0;char ch=getchar();int updown=0;
	while(ch<'0'||ch>'9'){if(ch=='-')updown=1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=a*10+ch-48;ch=getchar();}
	if(updown)a=-a;
}
int buf[40];
void _printf(long long a)
{
	int k=0;
	if(a==0){putchar('0');putchar('\n');return;}
	if(a<0)putchar('-'),a=-a;
	while(a!=0){buf[k++]=a%10;a=a/10;}
	for(int i=k-1;i>=0;i--)putchar('0'+buf[i]);
	putchar('\n');
}
struct edge{int to;int next;int w;}e[maxn<<1];
int n,m,np=0;
int first[maxn],wh[maxn],w[maxn],dfn[5*maxn],low[5*maxn],son[5*maxn][3],inq[maxn<<1];
int c[maxh][maxn],dist[maxh][maxn],cd[maxh][maxn];long long g[maxh][maxn];
void addedge(int u,int v,int ww){e[++np]=(edge){v,first[u],ww};first[u]=np;}
int sz[maxn],cnt=0,maxd,maxi,maxf;
void dfs(int now,int fa,int dep)
{
	sz[now]=1;
	for(int p=first[now];p!=0;p=e[p].next)
	{
		int j=e[p].to;
		if(j==fa||inq[p])continue;
		dist[dep][j]=dist[dep][now]+e[p].w;
		dfs(j,now,dep);
		if(max(sz[j],cnt-sz[j])<maxd)maxd=max(sz[j],cnt-sz[j]),maxi=p,maxf=now;
		sz[now]+=sz[j];
	}
}
int all=0;
int mydivide(int now,int nown,int dep,int le)
{
	int fa=++all;
	c[dep][0]=le;
	if(nown==1)
	{
		wh[now]=fa;
		dfn[fa]=++c[dep][0];
		c[dep][dfn[fa]]=w[now];
		cd[dep][dfn[fa]]=now;
		low[fa]=dfn[fa];
		return fa;
	}
	maxd=n;maxi=0;maxf=0;cnt=nown;dfs(now,0,dep);
	int ai=e[maxi].to,bi=maxf,ci=sz[e[maxi].to];
	son[fa][2]=e[maxi].w;
	inq[maxi]=1;inq[(maxi&1)?maxi+1:maxi-1]=1;
	son[fa][0]=mydivide(ai,ci,dep+1,le);
	son[fa][1]=mydivide(bi,nown-ci,dep+1,low[son[fa][0]]);
	dfn[fa]=c[dep][0]+1;low[fa]=c[dep][0]+nown;c[dep][0]=low[fa];
	ai=son[fa][0];bi=son[fa][1];
	int l=dfn[ai],r=dfn[bi];
	for(int i=dfn[fa];i<=low[fa];i++)
	{
		if((r>low[bi])||(l<=low[ai]&&c[dep+1][l]<=c[dep+1][r]))cd[dep][i]=cd[dep+1][l],c[dep][i]=c[dep+1][l++];
		else cd[dep][i]=cd[dep+1][r],c[dep][i]=c[dep+1][r++];
		if(i!=dfn[fa])g[dep][i]+=g[dep][i-1];
		g[dep][i]+=dist[dep][cd[dep][i]];
	}
	return fa;
}
long long query(int now,int x,int l,int r,int dep)
{
	long long tmp=0;
	int ai,bi,ci,di;
	if(now==wh[x])return 0;
	if(dfn[wh[x]]<=low[son[now][0]])
	{
		ai=son[now][0];di=son[now][1];
		bi=lower_bound(c[dep]+dfn[di],c[dep]+low[di]+1,l)-c[dep];
		ci=upper_bound(c[dep]+dfn[di],c[dep]+low[di]+1,r)-c[dep];
		ci--;if(ci>=dfn[di])tmp+=g[dep][ci];
		if(bi>dfn[di])tmp-=g[dep][bi-1];
	}
	else
	{
		ai=son[now][1];di=son[now][0];
		bi=lower_bound(c[dep]+dfn[di],c[dep]+low[di]+1,l)-c[dep];
		ci=upper_bound(c[dep]+dfn[di],c[dep]+low[di]+1,r)-c[dep];
		ci--;if(ci>=dfn[di])tmp+=g[dep][ci];
		if(bi>dfn[di])tmp-=g[dep][bi-1];
	}
	tmp+=(long long)(ci-bi+1)*(son[now][2]+dist[dep][x])+query(ai,x,l,r,dep+1);
	return tmp;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int ai,bi,ci,A,l,r;long long ans=0;
	scanf("%d%d%d",&n,&m,&A);
	for(int i=1;i<=n;i++)_scanf(w[i]);
	for(int i=1;i<n;i++)
	{
		_scanf(ai);_scanf(bi);_scanf(ci);
		addedge(ai,bi,ci);
		addedge(bi,ai,ci);
	}
	memset(low,-1,sizeof(low));
	mydivide(1,n,0,0);
	for(int i=1;i<=m;i++)
	{
		_scanf(ci);_scanf(ai);_scanf(bi);
		l=min((ai+ans)%A,(bi+ans)%A);
		r=max((ai+ans)%A,(bi+ans)%A);
		ans=query(1,ci,l,r,1);
		_printf(ans);
	}
	return 0;
}

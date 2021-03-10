#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

typedef long long ll;
const int maxn=300010;
const ll inf=1000000000000000000LL;

struct edge
{
    int to,next;
    ll len;
};
struct node
{
    ll posi,sum;
    bool operator <(node a)const {return posi<a.posi;}
};

int n,times,top,circnt,edgecnt[3],tot,cnt;
ll ans;
int head[3][2*maxn],stack[maxn],dfn[maxn],low[maxn],a[2*maxn],b[2*maxn],c[2*maxn],fa[20][2*maxn],dfx[2*maxn],dep[2*maxn],lg2[2*maxn],q[maxn];
ll sum[2*maxn],dp[2*maxn],dis[2*maxn],stdis[maxn],posi[maxn];
edge e[3][4*maxn];
node h[2*maxn];

void push(int k,int x,int y,ll z)
{
    e[k][edgecnt[k]].to=y;e[k][edgecnt[k]].len=z;e[k][edgecnt[k]].next=head[k][x];head[k][x]=edgecnt[k]++;
	if(k==2)
	{
		//printf("%d->%d %lld\n",x,y,z);
	}
}

void dfs0(int k,int pre)
{
	//点双联通分量缩点 
    dfn[k]=low[k]=++times;
    stack[++top]=k;int p=head[0][k];
    while (p!=-1)
    {
        if (pre!=(p^1))
        {
            if (dfn[e[0][p].to]==0)
            {
                stdis[top]=e[0][p].len;
                dfs0(e[0][p].to,p);
                low[k]=min(low[k],low[e[0][p].to]);
                //若v和当前点为树边 
                if (dfn[e[0][p].to]==low[e[0][p].to]) 
				push(1,k,e[0][p].to,e[0][p].len);//建立圆方树中的圆圆边 
            }
            else
                if (dfn[e[0][p].to]<dfn[k])//此时找到了一个环 
                {
                	//开始建圆方边 
                    int j=top;
                    for (;stack[j]!=e[0][p].to;) j--;
                    circnt++;head[1][circnt]=-1; 
                    push(1,e[0][p].to,circnt,0);
                    
                    sum[circnt]=e[0][p].len;
                    for (int i=j;i<top;i++) sum[circnt]+=stdis[i];
                    ll s=0;
                    for (int i=j;i<top;i++)
                    {
                        s+=stdis[i];
						posi[stack[i+1]]=s;//记下当前环上该点一个方向的值 
						//建立环边 
                        push(1,circnt,stack[i+1],min(sum[circnt]-s,s));
                    }
                    low[k]=min(low[k],dfn[e[0][p].to]);
                }
        }
        p=e[0][p].next;
    }
    top--;//去掉当前点 
}

void dfs1(int k)
{
    dfx[k]=++times;int p=head[1][k];
    while (p!=-1)
    {
        dep[e[1][p].to]=dep[k]+1;
        fa[0][e[1][p].to]=k;
        dis[e[1][p].to]=dis[k]+e[1][p].len;
        dfs1(e[1][p].to);
        p=e[1][p].next;
    }
}

bool cmp(int x,int y) {return dfx[x]<dfx[y];}

int kthfa(int x,int k)//倍增k次 
{
    int i=0;
    while (k)
    {
        if (k&1) x=fa[i][x];
        k>>=1;i++;
    }
    return x;
}

int lca(int x,int y)
{
    if (dep[x]<dep[y]) swap(x,y);
    x=kthfa(x,dep[x]-dep[y]);
    if (x==y) return x;
    int k=lg2[dep[x]];
    while (k>=0)
    {
        if (fa[k][x]!=fa[k][y]) {x=fa[k][x];y=fa[k][y];}
        k--;
    }
    return fa[0][x];
}

void treepop()
{
    if (c[top]!=a[b[top-1]]) 
    {
        a[++tot]=c[top];head[2][tot]=-1;
        push(2,tot,b[top],dis[a[b[top]]]-dis[a[tot]]);
        push(2,tot,b[top-1],dis[a[b[top-1]]]-dis[a[tot]]);
        b[top-1]=tot;
    }
    else
        push(2,b[top-1],b[top],dis[a[b[top]]]-dis[a[b[top-1]]]);
    top--;
    if (top>1) c[top]=lca(a[b[top]],a[b[top-1]]);
}

void check(ll &x,ll &y,ll z)
{
    if (z>x)
    {
        y=x;x=z;
    }
    else
        y=max(y,z);
}

void dfs2(int k)
{
    int p=head[2][k];
    ll seco=dp[k]=-inf;
    if (k<=cnt) dp[k]=0;//重新编号后判断该点能否为起点 
    while (p!=-1)
    {
        dfs2(e[2][p].to);
        check(dp[k],seco,dp[e[2][p].to]+e[2][p].len);//更新最长和次长 
        p=e[2][p].next;
    }
    if (a[k]<=n)//若是圆点，方点是需要特判的 
        ans=max(ans,dp[k]+seco);
    else//方点 
    {
    	//直接建虚树，并不用建虚仙人掌，只要是方点就倍增上来判断即可。 
        int p=head[2][k],m=0;
        while (p!=-1)
        {
        	//倍增至方点下一个点 
            int x=kthfa(a[e[2][p].to],dep[a[e[2][p].to]]-dep[a[k]]-1); 
            //存下每一个点 
			h[++m].posi=posi[x];h[m].sum=dp[e[2][p].to]+dis[a[e[2][p].to]]-dis[x];
            p=e[2][p].next;
        }
        sort(h+1,h+m+1);
        //破环 
		for (int i=1;i<m;i++) {h[i+m].posi=sum[a[k]]+h[i].posi;h[i+m].sum=h[i].sum;}
        
        /*for(int i=1;i<=2*m;i++)
			printf("%lld %lld\n",h[i].posi,h[i].sum);*/
        
		int f=1,r=1;q[1]=1;//环上单调队列维护环上两点间最短路。同正常仙人掌那样进行 
        for (int i=2;i<=m*2-1;i++)
        {
            while (f<=r&&(h[i].posi-h[q[f]].posi)*2>sum[a[k]]) f++;
            if (f<=r) ans=max(ans,h[i].posi-h[q[f]].posi+h[i].sum+h[q[f]].sum);
            while (f<=r&&h[i].sum-h[i].posi>=h[q[r]].sum-h[q[r]].posi) r--;
            q[++r]=i;
        }
    }
}

int main()
{
    freopen("input.txt","r",stdin);
	freopen("output2.txt","w",stdout);
    int m;scanf("%d%d",&n,&m);
    edgecnt[0]=0;for (int i=1;i<=n;i++) head[0][i]=-1;
    for (int i=1;i<=m;i++)
    {
        int x,y,z;scanf("%d%d%d",&x,&y,&z);
        push(0,x,y,z);push(0,y,x,z);
    }
    int q;scanf("%d",&q);
    times=top=edgecnt[1]=0;
	circnt=n;
    memset(dfn+1,0,n*sizeof(int));
    for (int i=1;i<=n;i++) head[1][i]=-1;
    dfs0(1,-1);
    
    lg2[1]=0;//算lg2 
	for (int i=2;i<=circnt;i++)lg2[i]=lg2[i>>1]+1;
	
	//memset fa数组 
    for (int i=0;i<=lg2[circnt];i++) memset(fa[i]+1,0,circnt*sizeof(int));
    memset(dfx+1,0,circnt*sizeof(int));dis[1]=times=dep[1]=0;
    
	dfs1(1);//处理圆方树的信息 
    for (int i=1;i<=lg2[circnt];i++)
        for (int j=1;j<=circnt;j++)
            fa[i][j]=fa[i-1][fa[i-1][j]];
            
    while (q--)
    {
    	//建立虚圆方树 
        scanf("%d",&cnt);
        for (int i=1;i<=cnt;i++) scanf("%d",&a[i]);
        //a原始点，b单调栈存下标，c存lca 
		sort(a+1,a+cnt+1,cmp);
        tot=cnt;
        for (int i=1;i<=tot;i++) head[2][i]=-1;edgecnt[2]=0;
        
		//建虚树部分 
        top=1;b[1]=1;
        for (int i=2;i<=cnt;i++)
        {
        	//在维护一个深度单调递增的栈c 
            while (top>1&&dep[c[top]]>=dep[lca(a[b[top]],a[i])]) treepop();
            b[++top]=i;
			c[top]=lca(a[i],a[b[top-1]]);
        }
        while (top>1) treepop();
        
		ans=0;dfs2(b[1]);
        printf("%lld\n",ans);
    }
    return 0;
}

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
 
const int maxn=305;
const int maxm=400005;
const int mod=1e9+7;
using namespace std;
 
struct edge
{
    int from,to,cap,flow,next;
};
int inf=1e7;
struct isap
{
    static const int maxn=605;
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
    void rebuild(int p,int w)
    {
        e[p].flow=0;
        e[other(p)].flow=0;
        if(w)
        {
            e[p].cap=0;
            e[other(p)].cap=0;
        }
    }
}e;
int n;long long inv[maxn][maxn],a[maxn][maxn],b[maxn][maxn],c[maxn][maxn];
int mysp[maxn*2];
long long qkpow(long long a,int t){
    long long ans=1;
    while (t!=0){
        if (t&1) ans=(ans*a)%mod;
        a=(a*a)%mod;t>>=1;
    }
    return ans;
}
int myabs(int x){return x<0?-x:x;}
//矩阵求逆操作方法就是消a为单位矩阵，同时对单位矩阵进行同样的操作以达到构造出a矩阵的逆的效果。 
//此题通过把普通方程变为同余方程来消除误差，
//一是因为我们根本不关注值为多少，只关注有无值，
//二是答案绝不会太大，因为出现的整数都都小于10000，绝不会出现b需要a*一个大数来合成，故可用该方法。 
int gauss(int n) 
{
    int r=0;
    for(int i=1;i<=n;i++)
        inv[i][i]=1;
    for(int i=1;i<=n;i++)
    {
        r=i;
        for(int ii=i+1;ii<=n;ii++)
            if(myabs(a[ii][i])>myabs(a[r][i]))r=ii;
        //对于矩阵求逆一定要从1开始走，因为逆矩阵并不一定被消成上三角矩阵，故都要操作 
        for(int ii=1;ii<=n;ii++)
        {
            swap(a[r][ii],a[i][ii]);
            swap(inv[r][ii],inv[i][ii]);
        }
             
        if(a[i][i]==0)return -1;
        long long t=qkpow(a[i][i],mod-2);
        for(int ii=1;ii<=n;ii++)
        {
            a[i][ii]=a[i][ii]*t%mod;
            inv[i][ii]=inv[i][ii]*t%mod;
        }
        for(int ii=1;ii<=n;ii++)
        {
            if(ii!=i&&a[ii][i]!=0)
            {
                t=a[ii][i];
                for(int i3=1;i3<=n;i3++)//同理，不然这里同样要错。 
                {
                    a[ii][i3]=(a[ii][i3]-a[i][i3]*t%mod+mod)%mod;
                    inv[ii][i3]=(inv[ii][i3]-inv[i][i3]*t%mod+mod)%mod;
                }
            }
             
        }
    }
    return 1;
}
int main()
{
    int ai;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int ii=1;ii<=n;ii++)
            scanf("%d",&ai),a[i][ii]=ai;
         
    int ans=gauss(n);
    for(int i=1;i<=n;i++)
        for(int ii=1;ii<=n;ii++)
            scanf("%d",&ai),b[i][ii]=ai;
    if(ans==-1)printf("NIE\n");
    else
    {
        for(int i=1;i<=n;i++)
            for(int ii=1;ii<=n;ii++)
                for(int i3=1;i3<=n;i3++)
                    c[i][ii]=(c[i][ii]+b[i][i3]*inv[i3][ii]%mod)%mod;
         
        int s=2*n+1,t=2*n+2;
        e.n=t;
        for(int i=1;i<=n;i++)
        {
            mysp[i]=e.np+1;
            e.addedge(s,i,1);
            mysp[i+n]=e.np+1;
            e.addedge(i+n,t,1);
            for(int ii=1;ii<=n;ii++)
            {
                if(c[ii][i]!=0)e.addedge(i,ii+n,1);
            }
        }
        int w=e.maxflow(s,t);
        if(w!=n)printf("NIE\n");
        else
        {
            printf("TAK\n");
            for(int i=1;i<=n;i++)
            {
                int mygo=0;
                for(int p=e.first[i];p!=0;p=e.e[p].next)
                {
                    if(e.e[p].cap==e.e[p].flow&&e.e[p].cap!=0)
                        mygo=e.e[p].to;
                    if(e.e[p].to!=s)e.rebuild(p,1);
                }
                e.rebuild(mysp[i],0);
                e.rebuild(mysp[mygo],0);
                for(int ii=1;ii<=n;ii++)
                {
                    if(c[ii][i]!=0)
                    {
                        int w=e.np+1;
                        e.addedge(i,ii+n,1);
                        int pl=e.maxflow(s,t);
                        if(pl)
                        {
                            printf("%d\n",ii);
                            break;
                        }
                        else e.rebuild(w,1);
                    }
                }
            }
        }
    }
    return 0;
}

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=1000005;
using namespace std;

int n,T;
struct state
{
	//par是par树中的边，表示right集,par可以形成一棵树 
	//go是真实的转移边 
	int par,go[26];
	int val;//val是它的长度 
}c[maxn];
struct SAM
{
	long long vis[maxn],ww[maxn];int v[maxn],wh[maxn];
	int rt,last,np;
	SAM(){rt=last=++np;}
	void extend(int w)//一步一步往里增加数 
	{
		int p=last;//找到串尾,为结束位置的后缀 
		c[last=++np].val=c[p].val+1;//新建np,为新的结束位置的后缀 
		int now=np;
		ww[np]=1;
		while(p&&c[p].go[w]==0)//对于没有标号为x的边的祖先，加一条边 
		{
			c[p].go[w]=np;
			p=c[p].par;
		}
		if(p==0)//若祖先都没有去x的边，建一条根到now的边 
			c[now].par=rt;
		else
		{
			int q=c[p].go[w];//找出该祖先去x的边 
			if(c[p].val+1==c[q].val)//若恰好长度吻合，直接接上去即可 
				c[now].par=q;
			else
			{
				c[++np].val=c[p].val+1;
				int nq=np;//新建一个节点令它的最长的长度为原来吻合长度 
				memcpy(c[nq].go,c[q].go,sizeof(c[q].go));//拷贝 
				c[nq].par=c[q].par;//取代q 
				c[q].par=nq;//令q的fa为nq 
				c[now].par=nq;//分成两部分
				while(p&&c[p].go[w]==q)//改变所有祖先 
					c[p].go[w]=nq,p=c[p].par;
			}
			last=now;
		}
	}
	void pre()
	{
		//这三步是为了把每个点按长度排序，长度相同按先后次序排 
		for(int i=1;i<=np;i++)v[c[i].val]++;
		for(int i=1;i<=n;i++)v[i]+=v[i-1];
		for(int i=np;i>=1;i--)wh[v[c[i].val]--]=i;
		
		//ww是它的right集合的大小
		ww[1]=0;
		for(int i=np;i>=2;i--)
		{
			int t=wh[i];
			if(T==1)ww[c[t].par]+=ww[t];
			else ww[t]=1;
		}
		ww[1]=0;
		
		//vis是当前节点的路径数 
		for(int i=np;i>=1;i--)
		{
			int t=wh[i];vis[t]=ww[t];
			for(int ii=0;ii<26;ii++)
				if(c[t].go[ii])vis[t]+=vis[c[t].go[ii]];
		}
	}
	void dfs(int now,int k)//递归求答案。 
	{
		if(k<=ww[now])return;
		k-=ww[now];
		for(int i=0;i<26;i++)
		{
			if(c[now].go[i])
			{
				if(k<=vis[c[now].go[i]])
				{
					putchar(i+'a');
					dfs(c[now].go[i],k);
					return;
				}
				k-=vis[c[now].go[i]];
			}
		}
	}
}sam;
char s[500005];
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	gets(s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
		sam.extend(s[i]-'a');
	int k;
	scanf("%d%d",&T,&k);
	sam.pre();
	if(k>sam.vis[1])printf("-1\n");
	else sam.dfs(sam.rt,k),putchar('\n');
	return 0;
}

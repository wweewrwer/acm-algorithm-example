#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=2200005;
using namespace std;

struct mydata
{
	int son[2];
	int fa;
	int w;
};
struct bst
{
	int rt,np;
	mydata c[maxn];
	void ins(int now,int v)
	{
		int d=0;
		while(now)
		{
			d=(c[now].w<v);
			if(c[now].son[d]==0)break;
			now=c[now].son[d];
		}
		c[++np]=(mydata){{0,0},now,v};
		c[now].son[d]=np;
		if(now==0)rt=np;
	}
	void del(int now,int v)
	{
		now=find(now,v);
		if(now==0)return;
		int x=0,y=0,d=0;
		if(c[now].son[0])
		{
			x=c[now].son[0];
			while(c[x].son[1])x=c[x].son[1];
			c[now].w=c[x].w;
			y=c[x].fa;
			c[y].son[c[y].son[1]==x]=c[x].son[0];
			c[x].fa=0;
			if(c[x].son[0])c[c[x].son[0]].fa=y;
		}
		else if(c[now].son[1])
		{
			y=c[now].fa;
			c[y].son[c[y].son[1]==now]=c[now].son[1];
			c[now].fa=0;
			c[c[now].son[1]].fa=y;
		}
		else
		{
			if(now==rt)rt=0;
			else
			{
				y=c[now].fa;
				c[y].son[c[y].son[1]==now]=0;
				c[now].fa=0;
			}
		}
	}
	int max(int now)
	{
		while(c[now].son[1])now=c[now].son[1];
		return now;
	}
	int min(int now)
	{
		while(c[now].son[0])now=c[now].son[0];
		return now;
	}
	int find(int now,int x)
	{
		int d=0;
		while(now)
		{
			if(c[now].w==x)break;
			d=(c[now].w<x);
			now=c[now].son[d];
		}
		return now;
	}
	int pred(int now,int x)
	{
		int d=0,t=0;
		while(now)
		{
			if(c[now].w<x)t=now,now=c[now].son[1];
			else now=c[now].son[0];
		}
		return t;
	}
	int succ(int now,int x)
	{
		int d=0,t=0;
		while(now)
		{
			if(c[now].w>x)t=now,now=c[now].son[0];
			else now=c[now].son[1];
		}
		return t;
	}
}c;
char s[55];
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int ai;
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&ai);
		c.ins(c.rt,ai);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%s",s+1);
		if(s[1]=='I')
		{
			scanf("%d",&ai);
			c.ins(c.rt,ai);
		}
		else if(s[1]=='D')
		{
			scanf("%d",&ai);
			c.del(c.rt,ai);
		}
		else if(s[1]=='M')
		{
			int d=0;
			if(c.rt==0)continue;
			if(s[2]=='i')printf("%d\n",c.c[c.min(c.rt)].w);
			else printf("%d\n",c.c[c.max(c.rt)].w);
		}
		else if(s[1]=='F')
		{
			scanf("%d",&ai);
			if(c.find(c.rt,ai))printf("Y\n");
			else printf("N\n");
		}
		else if(s[1]=='P')
		{
			scanf("%d",&ai);
			int d=c.pred(c.rt,ai);
			if(d!=0)printf("%d\n",c.c[d].w);
		}
		else if(s[1]=='S')
		{
			scanf("%d",&ai);
			int d=c.succ(c.rt,ai);
			if(d!=0)printf("%d\n",c.c[d].w);
		}
	}
	return 0;
}

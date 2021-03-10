#include<iostream>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cstdio>

const int maxn=400002;
using namespace std;

struct mydata
{
	int son[2];
	int fa;
	int w;
	int sz;
};
struct bst
{
	int rt,np;
	mydata c[maxn<<1];
	void pushup(int x)
	{
		c[x].sz=1;
		if(c[x].son[0])c[x].sz+=c[c[x].son[0]].sz;
		if(c[x].son[1])c[x].sz+=c[c[x].son[1]].sz;
	}
	void rot(int x)
	{
		int y=c[x].fa,z=c[y].fa;
		int d=(c[y].son[0]==x);
		
		c[y].son[d^1]=c[x].son[d];
		c[c[x].son[d]].fa=y;
		
		c[x].son[d]=y;
		c[y].fa=x;
		
		c[x].fa=z;
		if(z)c[z].son[c[z].son[1]==y]=x;
		
		pushup(y);
		pushup(x);
	}
	void splay(int x,int anc)
	{
		if(x==0)return;
		while(c[x].fa!=anc)
		{
			int y=c[x].fa,z=c[y].fa;
			if(z!=anc)
			{
				if((c[y].son[1]==x)==(c[z].son[1]==y))rot(y);
				else rot(x);
			}
			rot(x);
		}
		if(anc==0)rt=x;
	}
	void ins(int now,int v)
	{
		int d=0;
		while(now)
		{
			d=c[now].w<v;
			if(c[now].son[d]==0)break;
			now=c[now].son[d];
		}
		c[++np]=(mydata){{0,0},now,v,1};
		if(now)c[now].son[d]=np;
		splay(np,0);
	}
	int find(int now,int v)
	{
		while(now)
		{
			if(c[now].w==v)break;
			now=c[now].son[v>c[now].w];
		}
		splay(now,0);
		return now;
	}
	void del(int now,int v)
	{
		int x=find(now,v);
		if(!x)return;
		if(c[x].son[0])
		{
			int p=c[x].son[0];
			while(c[p].son[1])p=c[p].son[1];
			splay(p,x);
			c[p].fa=0;
			c[p].son[1]=c[x].son[1];
			c[c[x].son[1]].fa=p;
			rt=p;
			pushup(p);
		}
		else
		{
			c[c[x].son[1]].fa=0;
			rt=c[x].son[1];
		}
	}
	int count(int now,int x)
	{
		int tmp=0;
		while(now)
		{
			int t=1;
			if(c[now].son[0])t+=c[c[now].son[0]].sz;
			if(c[now].w<x)tmp+=t,now=c[now].son[1];
			else now=c[now].son[0];
		}
		return tmp;
	}
	int kth(int now,int x)
	{
		while(now)
		{
			int t=1;
			if(c[now].son[0])t+=c[c[now].son[0]].sz;
			if(t==x)break;
			if(x>t)x-=t,now=c[now].son[1];
			else now=c[now].son[0];
		}
		splay(now,0);
		return now;
	}
	int rank(int now,int x)
	{
		if(!find(now,x))return 0;
		else return count(rt,x)+1;
	}
}c;
char s[25];
int main()
{
	int n,m,ai,bi,ci;
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
		else if(s[1]=='K')
		{
			scanf("%d",&ai);
			int d=c.kth(c.rt,ai);
			if(d==0)printf("invalid\n");
			else printf("%d\n",c.c[d].w);
		}
		else if(s[1]=='C')
		{
			scanf("%d",&ai);
			printf("%d\n",c.count(c.rt,ai));
		}
		else if(s[1]=='R')
		{
			scanf("%d",&ai);
			int d=c.rank(c.rt,ai);
			if(d==0)printf("None\n");
			else printf("%d\n",d);
		}
	}
	return 0;
}

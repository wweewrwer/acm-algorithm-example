#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>

const int maxn=400005;
using namespace std;

struct mydata
{
	int son[2];
	int w;
	int sz;
	int fix;
};
struct bst
{
	int rt,np;
	mydata c[maxn];
	void pushup(int now)
	{
		if(!now)return;
		c[now].sz=1;
		if(c[now].son[0])c[now].sz+=c[c[now].son[0]].sz;
		if(c[now].son[1])c[now].sz+=c[c[now].son[1]].sz;
	}
	int merge(int a,int b)//b中全部大于a 
	{
		if(a==0||b==0)return a+b;
		
		if(c[a].fix>c[b].fix)
		{
			c[a].son[1]=merge(c[a].son[1],b);
			pushup(a);
			return a; 
		}
		else
		{
			c[b].son[0]=merge(a,c[b].son[0]);
			pushup(b);
			return b;
		}
	}
	void split(int now,int k,int &a,int &b)
	{
		if(k==0){a=0,b=now;return;}
		
		if(c[c[now].son[0]].sz>=k)
		{
			split(c[now].son[0],k,a,b);
			c[now].son[0]=b;
			b=now;
			pushup(now);
		}
		else
		{
			split(c[now].son[1],k-c[c[now].son[0]].sz-1,a,b);
			c[now].son[1]=a;
			a=now;
			pushup(now);
		}
	}
	int count(int now,int v)
	{
		int tmp=0;
		while(now)
		{
			int t=1;
			if(c[now].son[0])t+=c[c[now].son[0]].sz;
			if(v>c[now].w)tmp+=t,now=c[now].son[1];
			else now=c[now].son[0];
		}
		return tmp;
	}
	int find(int now,int v)
	{
		while(now)
		{
			if(c[now].w==v)break;
			now=c[now].son[c[now].w<v];
		}
		return now;
	}
	int rank(int now,int v)
	{
		if(!find(now,v))return 0;
		else return count(now,v)+1;
	}
	int kth(int now,int x)
	{
		while(now)
		{
			int t=1;
			if(c[now].son[0])t+=c[c[now].son[0]].sz;
			if(t==x)break;
			if(t<x)x-=t,now=c[now].son[1];
			else now=c[now].son[0];
		}
		return now;
	}
	void ins(int v)
	{
		c[++np]=(mydata){{0,0},v,1,rand()};
		int k,a,b;
		k=count(rt,v);
		split(rt,k,a,b);
		a=merge(a,np);
		rt=merge(a,b);
	}
	void del(int v)
	{
		if(!find(rt,v))return;
		int k,a,b,bb;
		k=count(rt,v);
		split(rt,k,a,b);
		split(b,1,bb,b);
		rt=merge(a,b);
	}
}c;
char s[25];
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,m,ai,bi,ci;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&ai);
		c.ins(ai);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%s",s+1);
		if(s[1]=='I')
		{
			scanf("%d",&ai);
			c.ins(ai);
		}
		else if(s[1]=='D')
		{
			scanf("%d",&ai);
			c.del(ai);
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

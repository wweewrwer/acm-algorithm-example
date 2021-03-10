#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>

const int maxn=300005;
using namespace std;

struct mydata
{
	int son[2];
	int sz;
	int v;
	int w;
	int fix;
};
struct mytree
{
	mydata c[maxn*55];
	int rt[maxn],np;
	void pushup(int now)
	{
		if(now==0)return;
		c[now].sz=1;
		c[now].w=c[now].v;
		if(c[now].son[0])c[now].sz+=c[c[now].son[0]].sz,c[now].w=max(c[now].w,c[c[now].son[0]].w);
		if(c[now].son[1])c[now].sz+=c[c[now].son[1]].sz,c[now].w=max(c[now].w,c[c[now].son[1]].w);
	}
	int merge(int a,int b)
	{
		if(a==0||b==0)return a+b;
		
		if(c[a].fix>c[b].fix)
		{
			c[++np]=c[a];a=np;
			c[a].son[1]=merge(c[a].son[1],b);
			pushup(a);
			return a;
		}
		else
		{
			c[++np]=c[b];b=np;
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
			c[++np]=c[now];now=np;
			split(c[now].son[0],k,a,b);
			c[now].son[0]=b;
			b=now;
			pushup(now);
		}
		else
		{
			c[++np]=c[now];now=np;
			split(c[now].son[1],k-c[c[now].son[0]].sz-1,a,b);
			c[now].son[1]=a;
			a=now;
			pushup(now);
		}
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
	void ins(int i,int x,int v)
	{
		c[++np]=(mydata){{0,0},1,v,v,rand()};
		int cc=np;
		int a,b;
		split(rt[i],x,a,b);
		a=merge(a,cc);
		rt[i]=merge(a,b);
	}
	void del(int i,int x)
	{
		int a,b,bb;
		split(rt[i],x-1,a,b);
		split(b,1,bb,b);
		rt[i]=merge(a,b);
	}
	int query(int i,int x,int y)
	{
		int a,b,bb;
		split(rt[i],x-1,a,b);
		split(b,y-x+1,b,bb);
		int v=c[b].w;
		b=merge(b,bb);
		rt[i]=merge(a,b);
		return v;
	}
}c;
int main()
{
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	int n,m,ai,bi,ci;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&ai);
		c.ins(0,i-1,ai);
	}
	int lastans=0;
	int t=0;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&ai);
		t++;
		c.rt[t]=c.rt[t-1];
		if(ai==1)
		{
			scanf("%d%d",&bi,&ci);
			bi=(bi+lastans)%(n+1);ci=ci^lastans;
			n++;
			c.ins(t,bi,ci);
		}
		else if(ai==2)
		{
			scanf("%d",&ai);
			ai=(ai+lastans)%n+1;
			n--;
			c.del(t,ai);
		}
		else if(ai==3)
		{
			scanf("%d%d",&ai,&bi);
			ai=(ai+lastans)%n+1;
			bi=(bi+lastans*2)%n+1;
			if(ai>bi)swap(ai,bi);
			lastans=c.query(t,ai,bi);
			printf("%d\n",lastans);
		}
		else if(ai==4)
		{
			scanf("%d",&ai);
			ai=(ai+lastans)%i;
			c.rt[t]=c.rt[ai];
			n=c.c[c.rt[t]].sz;
		}
	}
	return 0;
}

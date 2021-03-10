#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>

const int maxn=200005;
using namespace std;

struct mydata
{
	int son[2];
	int w;
};
struct mytree
{
	mydata c[maxn*22];
	int rt[maxn],np;
	void pushup(int now)
	{
		c[now].w=c[c[now].son[0]].w+c[c[now].son[1]].w;
	}
	void update(int now1,int &now,int l,int r,int x)
	{
		now=++np;
		c[now]=c[now1];
		if(l==r){c[now].w++;return;}
		
		int m=(l+r)/2;
		if(x<=m)update(c[now1].son[0],c[now].son[0],l,m,x);
		else update(c[now1].son[1],c[now].son[1],m+1,r,x);
		pushup(now);
	}
	int query(int now1,int now,int l,int r,int x)
	{
		if(l==r)return l;
		
		int m=(l+r)/2;
		int t=c[c[now].son[1]].w-c[c[now1].son[1]].w;
		if(x<=t)return query(c[now1].son[1],c[now].son[1],m+1,r,x);
		else return query(c[now1].son[0],c[now].son[0],l,m,x-t);
	}
	int query2(int now1,int now,int l,int r,int x,int y)
	{
		if(!now)return 0;
		if(x<=l&&r<=y)return c[now].w-c[now1].w;
		
		int m=(l+r)/2;
		if(y<=m)return query2(c[now1].son[0],c[now].son[0],l,m,x,y);
		else if(x>m)return query2(c[now1].son[1],c[now].son[1],m+1,r,x,y);
		else return query2(c[now1].son[0],c[now].son[0],l,m,x,m)+
		query2(c[now1].son[1],c[now].son[1],m+1,r,m+1,y);
	}
}c;
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int nn=200000;
	int lastans=0;
	int ai,bi,ci,di,ei;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&ai);
		c.update(c.rt[i-1],c.rt[i],0,nn,ai);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&ai,&bi,&ci,&di);
		if(ai==1)
		{
			bi^=lastans;
			ci^=lastans;
			if(bi>ci)swap(bi,ci);
			lastans=c.query(c.rt[bi-1],c.rt[ci],0,nn,di);
			printf("%d\n",lastans);
		}
		else
		{
			bi^=lastans;
			ci^=lastans;
			if(bi>ci)swap(bi,ci);
			scanf("%d",&ei);
			lastans=c.query2(c.rt[bi-1],c.rt[ci],0,nn,di,ei);
			printf("%d\n",lastans);
		}
	}
	return 0;
}

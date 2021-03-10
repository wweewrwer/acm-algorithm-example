#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=200005;
using namespace std;

struct mydata
{
	int son[2];
	int minv;
};
int a[maxn];
struct mytree
{
	mydata c[maxn*20];
	int rt[maxn],np;
	void pushup(int now)
	{
		c[now].minv=min(c[c[now].son[0]].minv,c[c[now].son[1]].minv);
	}
	void build(int &now,int l,int r)
	{
		now=++np;
		if(l==r){c[now]=(mydata){{0,0},a[l]};return;}
		
		int m=(l+r)/2;
		build(c[now].son[0],l,m);
		build(c[now].son[1],m+1,r);
		pushup(now);
	}
	void update(int now1,int &now,int l,int r,int x,int v)
	{
		now=++np;
		c[now]=c[now1];
		if(l==r){c[now].minv=v;return;}
		
		int m=(l+r)/2;
		if(x<=m)update(c[now1].son[0],c[now].son[0],l,m,x,v);
		else update(c[now1].son[1],c[now].son[1],m+1,r,x,v);
		pushup(now);
	}
	int query(int now,int l,int r,int x,int y)
	{
		if(x<=l&&r<=y)return c[now].minv;
		
		int m=(l+r)/2;
		if(y<=m)return query(c[now].son[0],l,m,x,y);
		else if(x>m)return query(c[now].son[1],m+1,r,x,y);
		else return min(query(c[now].son[0],l,m,x,m),query(c[now].son[1],m+1,r,m+1,y));
	}
}c;
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	c.build(c.rt[0],1,n);
	int ai,bi,ci,di;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&ai,&bi,&ci);
		if(ai==1)c.update(c.rt[i-1],c.rt[i],1,n,bi,ci);
		else
		{
			scanf("%d",&di);
			c.rt[i]=c.rt[i-1];
			printf("%d\n",c.query(c.rt[bi],1,n,ci,di));
		}
	}
	return 0;
}

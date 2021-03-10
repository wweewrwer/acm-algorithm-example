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
int a[maxn],b[maxn],inf=1e9+5;
struct mytree//此类主席树注意没有更新的地方要继承过来 
{
	mydata c[maxn*22];
	int rt[maxn],np;
	void mycl()
	{
		np=0;
	}
	void pushup(int now)
	{
		c[now].w=max(c[c[now].son[0]].w,c[c[now].son[1]].w);
	}
	void update(int now1,int &now,int l,int r,int x,int v)
	{
		now=++np;
		c[now].son[0]=c[now1].son[0];
		c[now].son[1]=c[now1].son[1];
		c[now].w=0;
		if(l==r){c[now].w=v;return;}
		
		int m=(l+r)/2;
		if(x<=m)update(c[now1].son[0],c[now].son[0],l,m,x,v);
		else update(c[now1].son[1],c[now].son[1],m+1,r,x,v);
		pushup(now);
	}
	int query(int now,int l,int r,int x,int y)
	{
		if(x<=l&&r<=y)return c[now].w;
		
		int m=(l+r)/2;
		if(y<=m)return query(c[now].son[0],l,m,x,y);
		else if(x>m)return query(c[now].son[1],m+1,r,x,y);
		else return max(query(c[now].son[0],l,m,x,m),query(c[now].son[1],m+1,r,m+1,y));
	}
}c;
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int ai,bi,ci;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	int tot=unique(b+1,b+n+1)-b;tot--;
	
	c.c[0].w=-inf;
	for(int i=1;i<=n;i++)
	{
		int k=lower_bound(b+1,b+tot+1,a[i])-b;
		c.update(c.rt[k],1,n,i,a[i]);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&ai,&bi,&ci);
		
		int k=upper_bound(b+1,b+tot+1,ci-1)-b;
		k--;
		k=c.query(c.rt[k],1,n,ai,bi);
		if(k<=-inf+2)printf("None\n");
		else printf("%d\n",k);
	}
	return 0;
}

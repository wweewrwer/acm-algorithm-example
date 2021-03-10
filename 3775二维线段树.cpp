#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=1000005;
using namespace std;

struct abc
{
	int maxv,minv;
	friend abc operator +(abc one,abc two)
	{
		return (abc){max(one.maxv,two.maxv),min(one.minv,two.minv)};
	}
};
struct mydata
{
	int son[2];
	abc w;
};
namespace tree
{
	int cb[1005][1005],son[maxn<<1][2];
	mydata c[maxn*25];
	int rt,np,np2,n,m,nx;
	struct node
	{
		int rt;
		void pushup(int now)
		{
			c[now].w=c[c[now].son[0]].w+c[c[now].son[1]].w;
		}
		void build(int &now,int l,int r)
		{
			now=++np;
			if(l==r){c[now].w=(abc){cb[nx][l],cb[nx][l]};return;}
			
			int m=(l+r)/2;
			build(c[now].son[0],l,m);
			build(c[now].son[1],m+1,r);
			pushup(now);
		}
		void update(int now,int l,int r,int x,abc v)
		{
			if(l==r){c[now].w=v;return;}
			
			int m=(l+r)/2;
			if(x<=m)update(c[now].son[0],l,m,x,v);
			else update(c[now].son[1],m+1,r,x,v);
			pushup(now);
		}
		abc query(int now,int l,int r,int x,int y)
		{
			if(x<=l&&r<=y)return c[now].w;
			
			int m=(l+r)/2;
			if(y<=m)return query(c[now].son[0],l,m,x,y);
			else if(x>m)return query(c[now].son[1],m+1,r,x,y);
			else return query(c[now].son[0],l,m,x,y)+query(c[now].son[1],m+1,r,x,y);
		}
	}nd[maxn<<1];
	void pushup(int now,int l)
	{
		abc ai=nd[now].query(nd[son[now][0]].rt,1,m,l,l);
		abc bi=nd[now].query(nd[son[now][1]].rt,1,m,l,l);
		nd[now].update(nd[now].rt,1,m,l,ai+bi);
	}
	void pushup(int now1,int now2,int now3,int l,int r)
	{
		c[now1].w=c[now2].w+c[now3].w;
		if(l==r)return;
		
		int mid=(l+r)/2;
		pushup(c[now1].son[0],c[now2].son[0],c[now3].son[0],l,mid);
		pushup(c[now1].son[1],c[now2].son[1],c[now3].son[1],mid+1,r);
	}
	void build(int &now,int l,int r)
	{
		now=++np2;nx=l;
		nd[now].build(nd[now].rt,1,m);
		if(l==r)return;
		
		int mid=(l+r)/2;
		build(son[now][0],l,mid);
		build(son[now][1],mid+1,r);
		pushup(nd[now].rt,nd[son[now][0]].rt,nd[son[now][1]].rt,1,m);
	}
	abc query(int now,int l,int r,int x,int y,int z,int w)
	{
		if(x<=l&&r<=y)return nd[now].query(nd[now].rt,1,m,z,w);
		
		int mid=(l+r)/2;
		if(y<=mid)return query(son[now][0],l,mid,x,y,z,w);
		else if(x>mid)return query(son[now][1],mid+1,r,x,y,z,w);
		else
		{
			return query(son[now][0],l,mid,x,y,z,w)+query(son[now][1],mid+1,r,x,y,z,w);
		}
	}
	void update(int now,int l,int r,int x,int y,abc v)
	{
		if(l==r)
		{
			nd[now].update(nd[now].rt,1,m,y,v);
			return;
		}
		int mid=(l+r)/2;
		if(x<=mid)update(son[now][0],l,mid,x,y,v);
		else update(son[now][1],mid+1,r,x,y,v);
		pushup(now,y);
	}
	void work()
	{
		scanf("%d",&n);
		m=n;
		for(int i=1;i<=n;i++)
		{
			for(int ii=1;ii<=n;ii++)
			{
				scanf("%d",&cb[i][ii]);
			}
		}
		int q,ai,bi,l;abc ha;
		build(rt,1,n);
		scanf("%d",&q);
		for(int i=1;i<=q;i++)
		{
			scanf("%d%d%d",&ai,&bi,&l);
			l=(l-1)/2;
			ha=query(rt,1,n,max(1,ai-l),min(ai+l,n),max(1,bi-l),min(bi+l,n));
			l=((long long)ha.maxv+ha.minv)/2;
			printf("%d\n",l);
			update(rt,1,n,ai,bi,(abc){l,l});
		}
	}
}
int main()
{
	tree::work();
	return 0;
}

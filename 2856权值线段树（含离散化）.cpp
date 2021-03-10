#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>

const int maxn=600005;
using namespace std;

struct mydata
{
	int son[2];
	int sum;
};
struct mytree
{
	int rt,np;
	mydata c[maxn<<1];
	void pushup(int now)
	{
		c[now].sum=c[c[now].son[0]].sum+c[c[now].son[1]].sum;
	}
	void build(int &now,int l,int r)
	{
		now=++np;
		if(l==r){c[now]=(mydata){{0,0},0};return;}
		
		int m=(l+r)/2;
		build(c[now].son[0],l,m);
		build(c[now].son[1],m+1,r);
		pushup(now);
	}
	void update(int now,int l,int r,int v,int d)
	{
		if(l==r)
		{
			if(c[now].sum==0&&d==-1)return;
			c[now].sum+=d;
			return;
		}
		
		int m=(l+r)/2;
		if(v<=m)update(c[now].son[0],l,m,v,d);
		else update(c[now].son[1],m+1,r,v,d);
		pushup(now);
	}
	int query(int now,int l,int r,int x,int y)
	{
		if(x<=l&&r<=y){return c[now].sum;}
		
		int m=(l+r)/2;
		if(y<=m)return query(c[now].son[0],l,m,x,y);
		else if(x>=m+1)return query(c[now].son[1],m+1,r,x,y);
		else return query(c[now].son[0],l,m,x,m)+query(c[now].son[1],m+1,r,m+1,y);
	}
	int kth(int now,int l,int r,int k)
	{
		if(l==r){if(k<=c[now].sum)return l;return -1;}
		
		int m=(l+r)/2;
		if(k<=c[c[now].son[0]].sum)return kth(c[now].son[0],l,m,k);
		else return kth(c[now].son[1],m+1,r,k-c[c[now].son[0]].sum);
	}
	int count(int now,int l,int r,int x)
	{
		if(l==r)return 0;
		
		int m=(l+r)/2;
		if(x<=m)return count(c[now].son[0],l,m,x);
		else return c[c[now].son[0]].sum+count(c[now].son[1],m+1,r,x); 
	}
}c;
char s[15];
int b[maxn];
struct point
{
	int id;
	int v;
	int v2;
}q[400005];
int main()
{
	int n,m,ai,bi,ci;
	scanf("%d%d",&n,&m);
	c.build(c.rt,0,maxn-5);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&ai);
		q[i].id=1;
		q[i].v=ai;
		b[i]=ai;
	}
	int tot=n;
	for(int i=1;i<=m;i++)
	{
		scanf("%s",s+1);
		if(s[1]=='I')
		{
			scanf("%d",&ai);
			q[n+i].id=1;q[n+i].v=ai;
			b[++tot]=ai;
		}
		else if(s[1]=='D')
		{
			scanf("%d",&ai);
			q[n+i].id=2;q[n+i].v=ai;
			b[++tot]=ai;
		}
		else if(s[1]=='K')
		{
			scanf("%d",&ai);
			q[n+i].id=3;q[n+i].v=ai;
			b[++tot]=ai;
		}
		else if(s[1]=='C')
		{
			scanf("%d",&ai);
			q[n+i].id=4;q[n+i].v=ai;
			b[++tot]=ai;
		}
		else if(s[1]=='A')
		{
			scanf("%d%d",&ai,&bi);
			q[n+i].id=5;q[n+i].v=ai;q[n+i].v2=bi;
			b[++tot]=ai;b[++tot]=bi;
		}
	}
	sort(b+1,b+tot+1);
	tot=unique(b+1,b+tot+1)-b;
	tot--;
	for(int i=1;i<=n+m;i++)
	{
		if(q[i].id==1)
		{
			ai=lower_bound(b+1,b+tot+1,q[i].v)-b;
			c.update(c.rt,0,maxn-5,ai,1);
		}
		else if(q[i].id==2)
		{
			ai=lower_bound(b+1,b+tot+1,q[i].v)-b;
			c.update(c.rt,0,maxn-5,ai,-1);
		}
		else if(q[i].id==3)
		{
			ai=q[i].v;
			int d=c.kth(c.rt,0,maxn-5,ai);
			if(d<0||ai==0)printf("invalid\n");
			else printf("%d\n",b[d]);
		}
		else if(q[i].id==4)
		{
			ai=lower_bound(b+1,b+tot+1,q[i].v)-b;
			printf("%d\n",c.count(c.rt,0,maxn-5,ai));
		}
		else if(q[i].id==5)
		{
			ai=lower_bound(b+1,b+tot+1,q[i].v)-b;
			bi=lower_bound(b+1,b+tot+1,q[i].v2)-b;
			printf("%d\n",c.query(c.rt,0,maxn-5,ai,bi));
		}
	}
	return 0;
}

#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

const int maxm=50005;
const int maxn=200005;
using namespace std;

struct mydata
{
	int son[2];
	int sum;
	int len;
	int cnt;
	int lr;
	int rr;
};
struct mytree
{
	int rt,np;
	mydata c[maxn<<1];
	void pushup(int now,int l,int r)
	{
		if(c[now].sum)
		{
			c[now].len=r-l;
			c[now].cnt=c[now].lr=c[now].rr=1;
		}
		else
		{
			if(r==l+1)c[now].len=0,c[now].cnt=c[now].lr=c[now].rr=0;
			else 
			{
				c[now].len=c[c[now].son[0]].len+c[c[now].son[1]].len;
				c[now].lr=c[c[now].son[0]].lr;
				c[now].rr=c[c[now].son[1]].rr;
				c[now].cnt=c[c[now].son[0]].cnt+c[c[now].son[1]].cnt;
				if(c[c[now].son[0]].rr==1&&c[c[now].son[1]].lr==1)c[now].cnt--;
			}
		}
	}
	void build(int &now,int l,int r)
	{
		now=++np;
		if(r==l+1){c[now]=(mydata){{0,0},0,0,0,0};return;}
		
		int m=(l+r)/2;
		build(c[now].son[0],l,m);
		build(c[now].son[1],m,r);
	}
	void modify(int now,int l,int r,int x,int y,int d)
	{
		if(x<=l&&r<=y)
		{
			c[now].sum+=d;
			pushup(now,l,r);
			return;
		}
		int m=(l+r)/2;
		if(y<=m)modify(c[now].son[0],l,m,x,y,d);
		else if(x>=m)modify(c[now].son[1],m,r,x,y,d);
		else
		{
			modify(c[now].son[0],l,m,x,m,d);
			modify(c[now].son[1],m,r,m,y,d);
		}
		pushup(now,l,r);
	}
}c;
struct myline
{
	int l;
	int r;
	int h;
	int d;
	friend bool operator <(myline one,myline two)
	{
		if(one.h!=two.h)return one.h<two.h;
		else return one.d>two.d;
	}
}q[2*maxm];
int main()
{
	freopen("input.txt","r",stdin);
	int ai,bi,ci,di;
	int n,m;
	scanf("%d",&n);
	int tot=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d%d",&ci,&bi,&ai,&di);
		ai+=100000;
		ci+=100000;
		bi+=100000;
		di+=100000;
		q[++tot]=(myline){bi,di,ai,-1};
		q[++tot]=(myline){bi,di,ci,1};
	}
	sort(q+1,q+2*n+1);
	
	long long tmp=0;
	c.build(c.rt,0,200000);
	int last=0;
	for(int i=1;i<=2*n;i++)
	{
		tmp+=(q[i].h-q[i-1].h)*2*c.c[c.rt].cnt;
		last=c.c[c.rt].len;
		c.modify(c.rt,0,200000,q[i].l,q[i].r,q[i].d);
		tmp+=abs(c.c[c.rt].len-last);
	}
	cout<<tmp<<'\n';
	return 0;
}

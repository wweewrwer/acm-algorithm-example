#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=4000005;
using namespace std;

void _scanf(int &a)
{
	a=0;
	char ch=getchar();
	int updown=0;
	while(ch<'0'||ch>'9'){if(ch=='-')updown=1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=a*10+ch-48;ch=getchar();}
	if(updown)a=-a;
}
struct abc
{
	int sz;
	int lsum;
	int rsum;
	int msum;
	int sum;
	friend abc operator +(abc one,abc two)
	{
		abc three;
		three.lsum=max(one.lsum,one.sum+two.lsum);
		three.rsum=max(two.rsum,two.sum+one.rsum);
		three.msum=max(one.rsum+two.lsum,
		max(max(three.lsum,three.rsum),max(one.msum,two.msum)));
		three.sum=one.sum+two.sum;
		three.sz=one.sz+two.sz;
		return three;
	}
	void setv(int v)
	{
		sum=sz*v;
		if(v>=0)
		{
			msum=lsum=rsum=sz*v;
		}
		else msum=lsum=rsum=v;
	}
	void change()
	{
		swap(lsum,rsum);
	}
};
struct mydata
{
	int son[2];
	int fa;
	abc v;
	int w;
	int mark;
	int setv;
};
struct mytree
{
	int rt,np;
	mydata c[maxn<<1];
	void pushup(int now)
	{
		if(!now)return;
		c[now].v=(abc){1,c[now].w,c[now].w,c[now].w,c[now].w};
		if(c[now].son[0])c[now].v=c[c[now].son[0]].v+c[now].v;
		if(c[now].son[1])c[now].v=c[now].v+c[c[now].son[1]].v;
	}
	void pushdown(int now)
	{
		if(c[now].setv!=10000)
		{
			if(c[now].son[0])
			{
				int x=c[now].son[0];
				c[x].setv=c[now].setv;
				c[x].v.setv(c[now].setv);
				c[x].w=c[now].setv;
			}
			if(c[now].son[1])
			{
				int x=c[now].son[1];
				c[x].setv=c[now].setv;
				c[x].v.setv(c[now].setv);
				c[x].w=c[now].setv;
			}
			c[now].setv=10000;
		}
		if(c[now].mark)
		{
			c[now].mark=0;
			if(c[now].son[0])
			{
				int x=c[now].son[0];
				c[x].mark^=1;
				c[x].v.change();
				swap(c[x].son[0],c[x].son[1]);
			}
			if(c[now].son[1])
			{
				int x=c[now].son[1];
				c[x].mark^=1;
				c[x].v.change();
				swap(c[x].son[0],c[x].son[1]);
			}
		}
		
	}
	void rot(int x)//核心，旋转 
	{
		int y=c[x].fa,z=c[y].fa;
		int d=(c[y].son[0]==x);
		
		c[y].son[d^1]=c[x].son[d];
		c[c[x].son[d]].fa=y;
		
		c[x].fa=z;
		if(z)c[z].son[c[z].son[1]==y]=x;
		
		c[y].fa=x;
		c[x].son[d]=y;
		
		pushup(y);
		pushup(x);
	}
	void splay(int x,int anc)//核心，扭上去。 
	{
		pushdown(x);
		while(c[x].fa!=anc)
		{
			int y=c[x].fa,z=c[y].fa;
			if(z!=anc)pushdown(z);
			pushdown(y);
			pushdown(x);
			if(z!=anc)
			{
				if((c[y].son[1]==x)==(c[z].son[1]==y))rot(y);
				else rot(x);
			}
			rot(x);
		}
		pushup(x);
		if(anc==0)rt=x;
	}
	int kth(int now,int x)
	{
		while(now)
		{
			pushdown(now);
			int t=1;
			if(c[now].son[0])t+=c[c[now].son[0]].v.sz;
			if(t==x)break;
			if(t<x)x-=t,now=c[now].son[1];
			else now=c[now].son[0];
		}
		//splay(now,0);因为这里每次查找都是在makeab里面所以不需要
		return now;
	}
	int makeab(int x,int y)//构造区间a,b,并返回作为该区间的父节点
	{
		if(x==1)
		{
			y=kth(rt,y+1);
			splay(y,0);
			return y;
		}
		
		x=kth(rt,x-1);
		y=kth(rt,y+1);
		splay(x,0);
		splay(y,x);
		return y;
	}
	int build(int x)
	{
		int ai=0;
		int now=0;
		for(int i=1;i<=x;i++)
		{
			_scanf(ai);
			c[++np]=(mydata){{0,0},0,{1,ai,ai,ai,ai},ai,0,10000};
			if(now==0)
			{
				now=np;
			}
			else
			{
				c[now].son[1]=np;
				c[np].fa=now;
				now=np;
			}
		}
		int rt2=rt;
		if(now!=0)splay(now,0);
		rt=rt2;
		return now;
	}
	void del(int x,int y)
	{
		int k=makeab(x,y);
		c[c[k].son[0]].fa=0;
		c[k].son[0]=0;
		splay(k,0);
	}
	void setv(int x,int y,int v)
	{
		int k=makeab(x,y);
		k=c[k].son[0];
		c[k].setv=v;
		c[k].v.setv(v);
		c[k].w=v;
		splay(k,0);
	}
	void ins(int x,int y)
	{
		int k=makeab(x+1,x);//使左儿子为空 
		int k2=build(y);
		c[k].son[0]=k2;
		c[k2].fa=k;
		splay(k2,0);
	}
	void rev(int x,int y)
	{
		int k=makeab(x,y);
		k=c[k].son[0];
		c[k].mark^=1;
		swap(c[k].son[0],c[k].son[1]);
		pushup(k);
		splay(k,0);
	}
	abc query(int x,int y)
	{
		int k=makeab(x,y);
		k=c[k].son[0];
		return c[k].v;
	}
}c;
char s[15];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	c.rt=1;
	c.c[++c.np]=(mydata){{0,0},0,{1,0,0,0,0},-20000,0,10000};
	c.ins(0,n);
	int ai,bi,ci;
	for(int i=1;i<=m;i++)
	{
		scanf("%s",s+1);
		if(s[3]=='S')
		{
			scanf("%d%d",&ai,&bi);
			c.ins(ai,bi);
		}
		else if(s[3]=='L')
		{
			scanf("%d%d",&ai,&bi);
			c.del(ai,ai+bi-1);
		}
		else if(s[3]=='K')
		{
			scanf("%d%d%d",&ai,&bi,&ci);
			c.setv(ai,ai+bi-1,ci);
		}
		else if(s[3]=='V')
		{
			scanf("%d%d",&ai,&bi);
			c.rev(ai,ai+bi-1);
		}
		else if(s[3]=='T')
		{
			scanf("%d%d",&ai,&bi);
			abc k=c.query(ai,ai+bi-1);
			printf("%d\n",k.sum);
		}
		else if(s[3]=='X')
		{
			printf("%d\n",c.c[c.rt].v.msum);
		}
	}
	return 0;
}

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=100005;
using namespace std;

int buf[40];
void _printf(long long a)
{
	int k=0;
	if(a==0){putchar('0');return;}
	if(a<0)putchar('-'),a=-a;
	while(a!=0)
	{
		buf[k++]=a%10;
		a=a/10;
	}
	for(int i=k-1;i>=0;i--)
	{
		putchar('0'+buf[i]);
	}
	putchar('\n');
}
struct mydata
{
	int son[2];
	long long sum;
	int mark;
};
int a[maxn];
struct mytree
{
	mydata c[maxn*100];
	int rt[maxn],np;
	void pushup(int now)
	{
		c[now].sum=c[c[now].son[0]].sum+c[c[now].son[1]].sum;
	}
	void pushdown(int now,int l,int r)
	{
		int m=(l+r)/2;
		if(c[now].mark!=0)
		{
			c[++np]=c[c[now].son[0]];
			c[now].son[0]=np;
			c[++np]=c[c[now].son[1]];
			c[now].son[1]=np;
			
			c[c[now].son[0]].mark+=c[now].mark;
			c[c[now].son[0]].sum+=(long long)c[now].mark*(m-l+1);
			c[c[now].son[1]].mark+=c[now].mark;
			c[c[now].son[1]].sum+=(long long)c[now].mark*(r-m);
			
			c[now].mark=0;
		}
	}
	void build(int &now,int l,int r)
	{
		now=++np;
		if(l==r){c[now]=(mydata){{0,0},a[l],0};return;}
		
		int m=(l+r)/2;
		build(c[now].son[0],l,m);
		build(c[now].son[1],m+1,r);
		pushup(now);
	}
	void update(int now1,int &now,int l,int r,int x,int y,int d)
	{
		if(l!=r)pushdown(now1,l,r);
		now=++np;
		c[now]=c[now1];
		if(x<=l&&r<=y)
		{
			c[now].mark+=d;
			c[now].sum+=(long long)(r-l+1)*d;
			return;
		}
		int m=(l+r)/2;
		if(y<=m)update(c[now1].son[0],c[now].son[0],l,m,x,y,d);
		else if(x>m)update(c[now1].son[1],c[now].son[1],m+1,r,x,y,d);
		else
		{
			update(c[now1].son[0],c[now].son[0],l,m,x,m,d);
			update(c[now1].son[1],c[now].son[1],m+1,r,m+1,y,d);
		}
		pushup(now);
	}
	long long query(int now,int l,int r,int x,int y)
	{
		if(x<=l&&r<=y)return c[now].sum;
		
		pushdown(now,l,r);
		int m=(l+r)/2;
		if(y<=m)return query(c[now].son[0],l,m,x,y);
		else if(x>m)return query(c[now].son[1],m+1,r,x,y);
		else return query(c[now].son[0],l,m,x,m)+query(c[now].son[1],m+1,r,m+1,y);
	}
}c;
char s[15];
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
	int t=0;
	for(int i=1;i<=m;i++)
	{
		scanf("%s",s+1);
		if(s[1]=='C')
		{
			t++;
			scanf("%d%d%d",&ai,&bi,&ci);
			c.update(c.rt[t-1],c.rt[t],1,n,ai,bi,ci);
		}
		else if(s[1]=='Q')
		{
			scanf("%d%d",&ai,&bi);
			_printf(c.query(c.rt[t],1,n,ai,bi));
		}
		else if(s[1]=='H')
		{
			scanf("%d%d%d",&ai,&bi,&ci);
			_printf(c.query(c.rt[ci],1,n,ai,bi));
		}
		else if(s[1]=='B')
		{
			scanf("%d",&t);
		}
	}
	return 0;
}

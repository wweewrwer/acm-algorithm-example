#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

const int maxn=400005;
const int KD=2;
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
}
int D;
struct point{
	int d[KD];
	friend bool operator ==(point one,point two)
	{
		for(int i=0;i<KD;i++)
		{
			if(one.d[i]!=two.d[i])return false;
		}
		return true;
	}
	friend bool operator <=(point one,point two)
	{
		for(int i=0;i<KD;i++)
		{
			if(one.d[i]>two.d[i])return false;
		}
		return true;
	}
}a[maxn];
bool comp(point one,point two)
{
	return one.d[D]<two.d[D];
}
bool comp2(point one,point two)
{
	if(one.d[0]!=two.d[0])return one.d[0]<two.d[0];
	else return one.d[1]<two.d[1];
}
struct abc
{
	int w;
	int x;
	int y;
	int x1;
	int y1;
}q[maxn];
struct mydata
{
	int son[2];
	point p,mi,mx;
	long long sum;
	long long v;
	long long w;
};
//int tttt=0;
struct kdtree
{
	mydata c[maxn];
	int rt,np;
	void pushup(int now)
	{
		c[now].mi=c[now].mx=c[now].p;
		c[now].w=c[now].sum=c[now].v;
		if(c[now].son[0])
		{
			int t=c[now].son[0];
			for(int i=0;i<KD;i++)
			{
				c[now].mi.d[i]=min(c[now].mi.d[i],c[t].mi.d[i]);
				c[now].mx.d[i]=max(c[now].mx.d[i],c[t].mx.d[i]);
			}
			c[now].w=max(c[now].w,c[t].w);
			c[now].sum+=c[t].sum;
		}
		if(c[now].son[1])
		{
			int t=c[now].son[1];
			for(int i=0;i<KD;i++)
			{
				c[now].mi.d[i]=min(c[now].mi.d[i],c[t].mi.d[i]);
				c[now].mx.d[i]=max(c[now].mx.d[i],c[t].mx.d[i]);
			}
			c[now].w=max(c[now].w,c[t].w);
			c[now].sum+=c[t].sum;
		}
	}
	void build(int &now,int l,int r,int k)
	{
		if(l>r)return;
		
		int m=(l+r)/2;
		D=k;nth_element(a+l,a+m,a+r+1,comp);
		now=++np;
		c[now]=(mydata){{0,0},a[m],a[m],a[m],0,0,0};
		build(c[now].son[0],l,m-1,(k+1)%KD);
		build(c[now].son[1],m+1,r,(k+1)%KD);
		pushup(now);
	}
	bool addv(int now,int k,point ap,int v)
	{
		if(!now)return false;
		if(c[now].p==ap)
		{
			//tttt++;
			c[now].v+=v;
			c[now].sum+=v;
			c[now].w=max(c[now].w,c[now].v);
			return true;
		}
		
		bool anum=false;
		if(ap.d[k]<c[now].p.d[k])
		{
			anum=addv(c[now].son[0],(k+1)%KD,ap,v);
		}
		else if(ap.d[k]>c[now].p.d[k])anum=addv(c[now].son[1],(k+1)%KD,ap,v);
		else
		{
			anum=addv(c[now].son[0],(k+1)%KD,ap,v);
			if(anum==false)anum=addv(c[now].son[1],(k+1)%KD,ap,v);
		}
		pushup(now);
		return anum;
	}
	int qin(int now,point x,point y)
	{
		if(!now)return false;
		if(x<=c[now].p&&c[now].p<=y)return true;
		return false;
	}
	int qans(int now,point x,point y)
	{
		if(!now)return false;
		if(x<=c[now].mi&&c[now].mx<=y)return true;
		return false;
	}
	int qx(int now,point x,point y)
	{
		if(!now)return false;
		if(c[now].mi<=y&&x<=c[now].mx)return true;
		/*for(int i=0;i<KD;i++)
		{
			if(c[now].mi.d[i]>y.d[i]||c[now].mx.d[i]<x.d[i])return false;
		}
		return true;*/
		return false;
	}
	long long query(long long &ans,int now,point x,point y)
	{
		if(!now)return 0;
		
		long long tmp=0;
		if(qans(now,x,y))
		{
			ans=max(ans,c[now].w);
			return c[now].sum;
		}
		if(qin(now,x,y))
		{
			tmp+=c[now].v;
			ans=max(ans,c[now].v);
		}
		if(qx(c[now].son[0],x,y))tmp+=query(ans,c[now].son[0],x,y);
		if(qx(c[now].son[1],x,y))tmp+=query(ans,c[now].son[1],x,y);
		return tmp;
	}
}c;
int main()
{
	int n,m=0;
	scanf("%d",&n);
	int ai,bi,ci,di,ei;
	n=0;
	while(true)
	{
		_scanf(ai);
		if(ai==3)break;
		if(ai==1)
		{
			_scanf(bi);
			_scanf(ci);
			_scanf(di);
			q[++m]=(abc){ai,bi,ci,di,0};
			a[++n]=(point){{bi,ci}};
		}
		else if(ai==2)
		{
			_scanf(bi);
			_scanf(ci);
			_scanf(di);
			_scanf(ei);
			q[++m]=(abc){ai,bi,ci,di,ei};
		}
	}
	sort(a+1,a+n+1,comp2);
	n=unique(a+1,a+n+1)-a;
	n--;
	c.build(c.rt,1,n,0);
	long long ans=0;
	for(int i=1;i<=m;i++)
	{
		if(q[i].w==1)
		{
			//tttt--;
			c.addv(c.rt,0,(point){{q[i].x,q[i].y}},q[i].x1);
		}
		else
		{
			ans=0;
			long long sum=c.query(ans,c.rt,(point){{q[i].x,q[i].y}},(point){q[i].x1,q[i].y1});
			_printf(sum);putchar(' ');_printf(ans);putchar('\n');
		}
	}
	//printf("%d\n",tttt);
	return 0;
}


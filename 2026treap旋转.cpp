#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>

const int maxn=400005;
using namespace std;

struct mydata
{
	int son[2];
	int w;
	int fix;
	int sz;
};
struct treap
{
	int rt,np;
	mydata c[maxn];
	void pushup(int now)
	{
		if(!now)return;
		c[now].sz=1;
		if(c[now].son[0])c[now].sz+=c[c[now].son[0]].sz;
		if(c[now].son[1])c[now].sz+=c[c[now].son[1]].sz;
	}
	void rot(int &now,int d)
	{
		int t=c[now].son[d^1];
		c[now].son[d^1]=c[t].son[d];
		c[t].son[d]=now;
		pushup(now);
		pushup(t);//注意这里now必须不为0； 
		now=t;
	}
	void ins(int &now,int x)
	{
		if(now==0)
		{
			c[++np]=(mydata){{0,0},x,rand(),1};
			now=np;
			return;
		}
		int d=(x>c[now].w);
		ins(c[now].son[d],x);
		pushup(now);
		if(c[now].fix<c[c[now].son[d]].fix)rot(now,d^1);
	}
	void del(int &now,int x)
	{
		if(!now)return;
		if(x==c[now].w)
		{
			if(c[now].son[0]&&c[now].son[1])
			{
				int d=(c[c[now].son[0]].fix>c[c[now].son[1]].fix);
				rot(now,d);
				del(c[now].son[d],x);
			}
			else
			{
				if(c[now].son[0])now=c[now].son[0];
				else now=c[now].son[1];
			}
		}
		else
		{
			del(c[now].son[x>c[now].w],x);
		}
		pushup(now);
	}
	/*void rot(int x)
	{
		int y=c[x].fa,z=c[y].fa;
		int d=(c[y].son[1]==x);
		
		c[y].son[d]=c[x].son[d^1];
		c[c[x].son[d^1]].fa=y;
		
		c[x].fa=z;
		if(z!=0)c[z].son[c[z].son[1]==y]=x;
		
		c[x].son[d^1]=y;
		c[y].fa=x;
		pushup(y);
		pushup(x);
	}
	void ins(int now,int x)
	{
		int d=0;
		while(now)
		{
			d=(x>c[now].w);
			if(c[now].son[d]==0)break;
			now=c[now].son[d];
		}
		c[++np]=(mydata){{0,0},now,x,rand(),1};
		if(now!=0)c[now].son[d]=np;
		while(now)pushup(now),now=c[now].fa;
		now=np;
		while(c[now].fa!=0&&c[now].fix>c[c[now].fa].fix)rot(now);
		if(c[now].fa==0)rt=np;
	}
	void del(int now,int x)
	{
		while(now)
		{
			if(x==c[now].w)
			{
				if(c[now].son[0]&&c[now].son[1])
				{
					int d=(c[c[now].son[1]].fix>c[c[now].son[0]].fix);
					rot(c[now].son[d]);
				}
				else
				{
					int y=c[now].fa;c[now].fa=0;
					int d=(c[y].son[1]==now);
					if(c[now].son[0])c[y].son[d]=c[now].son[0],c[c[now].son[0]].fa=y;
					else c[y].son[d]=c[now].son[1],c[c[now].son[1]].fa=y;
					now=y;
					while(now)pushup(now),now=c[now].fa;
				}
			}
			else
			{
				now=c[now].son[x>c[now].w];
			}
		}
	}*/
	int count(int now,int x)
	{
		int tmp=0;
		while(now)
		{
			int t=1;
			if(c[now].son[0])t+=c[c[now].son[0]].sz;
			if(x>c[now].w)tmp+=t,now=c[now].son[1];
			else now=c[now].son[0];
		}
		return tmp;
	}
	int find(int now,int x)
	{
		while(now)
		{
			if(x==c[now].w)break;
			now=c[now].son[x>c[now].w];
		}
		return now;
	}
	int rank(int now,int x)
	{
		if(find(now,x))return count(now,x)+1;
		else return 0;
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
}c;
char s[25];
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int ai,bi;
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&ai);
		c.ins(c.rt,ai);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%s",s+1);
		if(s[1]=='I')
		{
			scanf("%d",&ai);
			c.ins(c.rt,ai);
		}
		else if(s[1]=='D')
		{
			scanf("%d",&ai);
			c.del(c.rt,ai);
		}
		else if(s[1]=='C')
		{
			scanf("%d",&ai);
			printf("%d\n",c.count(c.rt,ai));
		}
		else if(s[1]=='R')
		{
			scanf("%d",&ai);
			int d=c.rank(c.rt,ai);
			if(d==0)printf("None\n");
			else printf("%d\n",d);
		}
		else if(s[1]=='K')
		{
			scanf("%d",&ai);
			if(c.c[c.rt].sz<ai||ai==0)printf("invalid\n");
			else printf("%d\n",c.c[c.kth(c.rt,ai)].w);
		}
	}
	return 0;
}

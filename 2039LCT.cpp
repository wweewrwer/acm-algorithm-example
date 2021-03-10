#include<iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>

const int maxn=300005;
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
void _scanf(char *s)
{
	int cnt=0;
	char c=getchar();
	while(!isalpha(c)) c=getchar();
	while(isalpha(c)) s[cnt++]=c,c=getchar();
	s[cnt]='\0';
}
int buf[40];
void _printf(int a)
{
	int k=0;
	if(a==0){putchar('0');putchar('\n');return;}
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
	int maxv;
	int sum;
	int v;
	int sz;
	int pa;
	int mark;
	int rev;
};
struct edge
{
	int to,next;
};
struct lct
{
	mydata c[maxn];
	int rt,np;
	int isroot(int x){return c[c[x].pa].son[0]!=x&&c[c[x].pa].son[1]!=x;}
	void pushup(int now)
	{
		c[now].maxv=c[now].sum=c[now].v;c[now].sz=1;
		if(c[now].son[0])
		{
			c[now].maxv=max(c[now].maxv,c[c[now].son[0]].maxv);
			c[now].sum+=c[c[now].son[0]].sum;
			c[now].sz+=c[c[now].son[0]].sz;
		}
		if(c[now].son[1])
		{
			c[now].maxv=max(c[now].maxv,c[c[now].son[1]].maxv);
			c[now].sum+=c[c[now].son[1]].sum;
			c[now].sz+=c[c[now].son[1]].sz;
		}
	}
	void pushdown(int now)
	{
		int lc=c[now].son[0],rc=c[now].son[1];
		if(c[now].mark)
		{
			if(lc)
			{
				c[lc].mark+=c[now].mark;
				c[lc].v+=c[now].mark;
				c[lc].maxv+=c[now].mark;
				c[lc].sum+=c[lc].sz*c[now].mark;
			}
			if(rc)
			{
				c[rc].mark+=c[now].mark;
				c[rc].v+=c[now].mark;
				c[rc].maxv+=c[now].mark;
				c[rc].sum+=c[rc].sz*c[now].mark;
			}
			c[now].mark=0;
		}
		if(c[now].rev)
		{
			if(lc)c[lc].rev^=1,swap(c[lc].son[0],c[lc].son[1]);
			if(rc)c[rc].rev^=1,swap(c[rc].son[0],c[rc].son[1]);
			c[now].rev=0;
		}
	}
	void rot(int x)
	{
		int y=c[x].pa,z=c[y].pa;
		int d=(c[y].son[0]==x);
		
		pushdown(y);
		pushdown(x);
		c[y].son[d^1]=c[x].son[d];
		c[c[x].son[d]].pa=y;
		
		c[x].pa=z;
		if(!isroot(y))c[z].son[c[z].son[1]==y]=x;
		
		c[y].pa=x;
		c[x].son[d]=y;
		
		pushup(y);
		pushup(x);
	}
	void splay(int x)
	{
		pushdown(x);
		while(!isroot(x))
		{
			int y=c[x].pa;
			int z=c[y].pa;
			if(!isroot(y))
			{
				if((c[z].son[1]==y)==(c[y].son[1]==x))rot(y);
				else rot(x);
			}
			rot(x);
		}
		rt=x;
	}
	int acc(int x)
	{
		int y=0;
		for(y=0;x;y=x,x=c[x].pa)
		{
			splay(x);
			c[x].son[1]=y;
			pushup(x);
		}
		return y;
	}
	int lca(int x,int y)
	{
		acc(x);
		int z=acc(y);
		return z;
	}
	void mroot(int x)
	{
		acc(x);
		splay(x);
		c[x].rev^=1;
		swap(c[x].son[0],c[x].son[1]);
	}
	int find(int x)
	{
		acc(x);splay(x);
		while(c[x].son[0])
		{
			pushdown(x);
			x=c[x].son[0];
		}
		return x;
	}
	void _link(int x,int y)
	{
		if(find(x)==find(y))return;
		mroot(x);
		c[x].pa=y;
	}
	void _cut(int x,int y)
	{
		if(find(x)!=find(y))return;
		mroot(x);
		acc(y);
		splay(y);
		c[c[y].son[0]].pa=0;//这里是剪断y与原本y的父亲 
		c[y].son[0]=0;
		pushup(y);
	}
	void update(int x,int y,int v)
	{
		mroot(x);
		acc(y);
		splay(y);
		c[y].v+=v;
		c[y].mark+=v;
		c[y].maxv+=v;
		c[y].sum+=c[y].sz*v;
	}
	int query(int x,int y)
	{
		mroot(x);
		acc(y);
		splay(y);
		return c[y].maxv;
	}
	int query2(int x,int y)
	{
		mroot(x);
		acc(y);
		splay(y);
		return c[y].sum;
	}
	void work()
	{
		int m,ai,bi,ci;
		char s[15];
		_scanf(m);
		for(int i=1;i<=m;i++)
		{
			_scanf(s+1);
			if(s[1]=='M'&&s[2]=='o')
			{
				_scanf(ai);_scanf(bi);_scanf(ci); 
				if(find(ai)!=find(bi))printf("continue\n");
				else update(ai,bi,ci);
			}
			else if(s[1]=='C')
			{
				_scanf(ai);_scanf(bi);
				if(find(ai)!=find(bi))printf("continue\n");
				else _cut(ai,bi);
			}
			else if(s[1]=='L')
			{
				_scanf(ai);_scanf(bi);
				if(find(ai)==find(bi))printf("continue\n");
				else _link(ai,bi);
			}
			else if(s[1]=='S')
			{
				_scanf(ai);_scanf(bi);
				if(find(ai)!=find(bi))printf("continue\n");
				else _printf(query2(ai,bi));
			}
			else if(s[1]=='M'&&s[2]=='a')
			{
				_scanf(ai);_scanf(bi);
				if(find(ai)!=find(bi))printf("continue\n");
				else _printf(query(ai,bi));
			}
		}
	}
}c;
struct tree
{
	edge e[maxn<<1];
	int first[maxn],np,fa[maxn],n,w[maxn];
	void addedge(int u,int v)
	{
		e[++np]=(edge){v,first[u]};
		first[u]=np;
	}
	void dfs(int now)
	{
		for(int p=first[now];p!=0;p=e[p].next)
		{
			int j=e[p].to;
			if(j==fa[now])continue;
			fa[j]=now;
			c.c[j].pa=now;
			dfs(j);
		}
	}
	void ready()
	{
		_scanf(n);
		int ai,bi;
		for(int i=2;i<=n;i++)
		{
			_scanf(ai);_scanf(bi);
			addedge(ai,bi);
			addedge(bi,ai);
		}
		for(int i=1;i<=n;i++)
		{
			_scanf(w[i]);
			c.c[i].v=w[i];
			c.c[i].maxv=w[i];
			c.c[i].sum=w[i];
			c.c[i].sz=1;
		}
		dfs(1);
	}
}e;
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	e.ready();
	c.work();
	return 0;
}

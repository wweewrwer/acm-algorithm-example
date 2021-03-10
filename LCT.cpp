//lct
//普通lct 
struct mydata
{
	int son[2];
	int pa;
	int w;
	int sum;
	int rev;
};
struct lct
{
	mydata c[maxn];
	int rt,np;
	int isrt(int x){return c[c[x].pa].son[0]!=x&&c[c[x].pa].son[1]!=x;}
	void pushup(int now)
	{
		c[now].sum=w;
		int lc=c[now].son[0],rc=c[now].son[1];
		if(lc)c[now].sum+=c[lc].sum;
		if(rc)c[now].sum+=c[rc].sum;
	}
	void pushdown(int now)
	{
		int lc=c[now].son[0],rc=c[now].son[1];
		if(c[now].rev)
		{
			if(lc)
			{
				swap(c[lc].son[0],c[lc].son[1]);
				c[lc].rev^=1;
			}
			if(rc)
			{
				swap(c[rc].son[0],c[rc].son[1]);
				c[rc].rev^=1;
			}
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
		while(!isrt(x))
		{
			int y=c[x].pa;
			int z=c[y].pa;
			if(!isrt(y))
			{
				if((c[z].son[1]==y)==(c[y].son[1]==x))rot(y);
				else rot(x);
			}
			rot(x);
		}
	}
	int acc(int x)//核心操作, 
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
	void mroot(int x)//换根，很多询问通过把链上一个端点移到根上，另一个点acc完成 
	{
		acc(x);
		splay(x);
		swap(c[x].son[0],c[x].son[1]);
		c[x].rev^=1;
	}
	void link(int x,int y)//连接 
	{
		mroot(x);
		c[x].pa=y;
	}
	void cut(int x,int y)//切断 
	{
		mroot(x);
		acc(y);
		splay(y);
		c[c[y].son[0]].pa=0;
		c[y].son[0]=0;
		pushup(y);
	}
}
//维护子树信息的lct
//pushup时更新x的总信息为：x实儿子的总信息+x虚儿子的信息+x本身的信息。 
struct mydata
{
	int son[2];
	int tsz;//总信息（子树大小） 
	int sz;//虚儿子信息（子树除了链以外的大小）
	int rev;
	int pa;
};
struct lct//其他与之前相同 
{
	void pushup(int now)
	{
		if(!now)return;
		c[now].tsz=c[now].sz+1;
		int lc=c[now].son[0],rc=c[now].son[1];
		if(lc)c[now].tsz+=c[lc].tsz;
		if(rc)c[now].tsz+=c[rc].tsz; 
	}
	int acc(int x)
	{
		int y=0;
		for(y=0;x;y=x,x=c[x].pa)
		{
			splay(x);
			c[x].sz+=c[c[x].son[1]].tsz-c[y].tsz;
			c[x].son[1]=y;
			pushup(x);
		}
		return y;
	}
	void link(int x,int y)
	{
		mroot(x);
		mroot(y);
		c[x].pa=y;
		c[y].sz+=c[x].tsz;
		pushup(y);
	}
}
//lct 处理边权，把边弄成一个点，搞成点权。 

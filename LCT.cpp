//lct
//��ͨlct 
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
	int acc(int x)//���Ĳ���, 
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
	void mroot(int x)//�������ܶ�ѯ��ͨ��������һ���˵��Ƶ����ϣ���һ����acc��� 
	{
		acc(x);
		splay(x);
		swap(c[x].son[0],c[x].son[1]);
		c[x].rev^=1;
	}
	void link(int x,int y)//���� 
	{
		mroot(x);
		c[x].pa=y;
	}
	void cut(int x,int y)//�ж� 
	{
		mroot(x);
		acc(y);
		splay(y);
		c[c[y].son[0]].pa=0;
		c[y].son[0]=0;
		pushup(y);
	}
}
//ά��������Ϣ��lct
//pushupʱ����x������ϢΪ��xʵ���ӵ�����Ϣ+x����ӵ���Ϣ+x�������Ϣ�� 
struct mydata
{
	int son[2];
	int tsz;//����Ϣ��������С�� 
	int sz;//�������Ϣ����������������Ĵ�С��
	int rev;
	int pa;
};
struct lct//������֮ǰ��ͬ 
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
//lct �����Ȩ���ѱ�Ū��һ���㣬��ɵ�Ȩ�� 

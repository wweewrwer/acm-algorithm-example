const int KD=2;
const int maxn=200005;

int D;
struct point
{
	int d[KD];
	friend bool operator <(point one,point two)
	{
		return one.d[D]<two.d[D];
	}
}a[maxn];
struct kdtree
{
	int son[maxn][2];
	point p[maxn],mi[maxn],mx[maxn];
	int rt,np;
	int newnode(point now)
	{
		++np;
		son[np][1]=son[np][0]=0;
		p[np]=mi[np]=mx[np]=now;
		return np;
	}
	void pushup(int now)
	{
		mi[now]=mx[now]=p[now];
		for(int i=0;i<KD;i++)
		{
			if(son[now][0])
			{
				int t=son[now][0];
				mi[now].d[i]...
				mx[now].d[i]...
			}
			......
		}
	}
	void build(int &now,int l,int r,int k)
	{
		if(l>r){now=0;return;}
		
		int m=(l+r)/2;
		D=k;nth_element(a+l,a+m,a+r+1);
		now=newnode(a[m]);
		build(son[now][0],l,m-1,(k+1)%KD);
		build(son[now][1],m+1,r,(k+1)%KD);
		pushup(now);
	}
	void ins(int &now,point ap,int k)
	{
		if(now==0)
		{
			now=newnode(ap);
			return;
		}
		D=k;
		if(ap<p[now])ins(son[now][0],ap,(k+1)%KD);
		else ins(son[now][1],ap,(k+1)%KD);
		pushup(now);
	}
	int dist(point x,point y)
	{
		int tmp=0;
		for(int i=0;i<KD;i++)tmp+=abs(x.d[i]-y.d[i]);
		return tmp;
	}
	int nearmi(point ap,int x)
	{
		if(!x)return inf;
		
		int tmp=0;
		for(int i=0;i<KD;i++)
		{
			
		}
	}
	void qmin(int now,point ap)
	{
		if(!now)return;
		ans=min(ans,dist(p[now],ap));
		int t1=nearmi(ap,son[now][0]);
		int t2=nearmi(ap,son[now][1]);
		if(t1<=t2)
		{
			if(t1<ans)qmin(son[now][0],ap);
			if(t2<ans)qmin(son[now][1],ap);
		}
		else
		{
			if(t2<ans)qmin(son[now][1],ap);
			if(t1<ans)qmin(son[now][1],ap);
		}
	}
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
	if(x<=c[now].mx&&c[now].mi<=y)return true;
	return false;
}
//Çø¼ä
long long query(long long &ans,int now,point x,point y)
{
	if(!now)return 0;
	
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
} 

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=200005;
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
int D,inf=2000000000,ans;//KD表示有几维，D表示目前比较哪一维 
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
	point p[maxn],mi[maxn],mx[maxn];//mx表示该区间的最大值，mi表示最小值 
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
				mi[now].d[i]=min(mi[now].d[i],mi[t].d[i]);
				mx[now].d[i]=max(mx[now].d[i],mx[t].d[i]);
			}
			if(son[now][1])
			{
				int t=son[now][1];
				mi[now].d[i]=min(mi[now].d[i],mi[t].d[i]);
				mx[now].d[i]=max(mx[now].d[i],mx[t].d[i]);
			}
		}
	}
	void build(int &now,int l,int r,int k)
	{
		if(l>r){now=0;return;}
		
		int m=(l+r)/2;
		D=k;nth_element(a+l,a+m,a+r+1);//找出当前位于中间的一个元素。 
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
		D=k;//简单的类似搜索树的插入 
		if(ap<p[now])ins(son[now][0],ap,(k+1)%KD);
		else ins(son[now][1],ap,(k+1)%KD);
		pushup(now);
	}
	int dist(point x,point y)//询问k维的距离 
	{
		int tmp=0;
		for(int i=0;i<KD;i++)tmp+=abs(x.d[i]-y.d[i]);
		return tmp;
	}
	int nearmi(point ap,int x)//贪心减枝，看那个区间离询问点的距离近。 
	{
		if(!x)return inf;
		
		int tmp=0;
		for(int i=0;i<KD;i++)
		{
			//基本思路就是看在这个区间的左边和右边分别算，到时候这个肯定是要推的。 
			if(ap.d[i]<mi[x].d[i])tmp+=mi[x].d[i]-ap.d[i];
			if(ap.d[i]>mx[x].d[i])tmp+=ap.d[i]-mx[x].d[i];
		}
		return tmp;
	}
	void qmin(int now,point ap)
	{
		if(!now)return;
		ans=min(ans,dist(p[now],ap));
		int t1=nearmi(ap,son[now][0]);
		int t2=nearmi(ap,son[now][1]);//先选近的，再选远的 
		if(t1<=t2)
		{
			if(t1<ans)qmin(son[now][0],ap);//减枝 
			if(t2<ans)qmin(son[now][1],ap);
		}
		else
		{
			if(t2<ans)qmin(son[now][1],ap);
			if(t1<ans)qmin(son[now][0],ap);
		}
	}
	int nearmx(point ap,int x)
	{
		if(!x)return -inf;
		
		int tmp=0;
		for(int i=0;i<KD;i++)
		{
			//算最远距离，基本就是算可能的最远距离，每次贪心的取最远。 
			if(ap.d[i]<mi[x].d[i])tmp+=mx[x].d[i]-ap.d[i];
			else if(ap.d[i]>mx[x].d[i])tmp+=ap.d[i]-mi[x].d[i];
			else tmp+=max(mx[x].d[i]-ap.d[i],ap.d[i]-mi[x].d[i]);
		}
		return tmp;
	}
	void qmax(int now,point ap)
	{
		if(!now)return;
		//单点询问基本思路算左右然后贪心的走 
		ans=max(ans,dist(ap,p[now]));
		int t1=nearmx(ap,son[now][0]);
		int t2=nearmx(ap,son[now][1]);
		if(t1>=t2)
		{
			//注意若没有ans优就直接退掉即可。 
			if(t1>ans)qmax(son[now][0],ap);
			if(t2>ans)qmax(son[now][1],ap);
		}
		else
		{
			if(t2>ans)qmax(son[now][1],ap);
			if(t1>ans)qmax(son[now][0],ap);
		}
	}
}c;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].d[0],&a[i].d[1]);
	}
	c.build(c.rt,1,n,0);
	int m;
	scanf("%d",&m);
	int ai,bi,ci;
	for(int i=1;i<=m;i++)
	{
		_scanf(ai);
		_scanf(bi);
		_scanf(ci);
		if(ai==0)
		{
			c.ins(c.rt,(point){bi,ci},0);
		}
		else if(ai==1)
		{
			ans=inf;
			c.qmin(c.rt,(point){bi,ci});
			printf("%d\n",ans);
		}
		else if(ai==2)
		{
			ans=0;
			c.qmax(c.rt,(point){bi,ci});
			printf("%d\n",ans);
		}
	}
	return 0;
}

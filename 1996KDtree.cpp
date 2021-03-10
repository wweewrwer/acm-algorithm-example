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
int D,inf=2000000000,ans;//KD��ʾ�м�ά��D��ʾĿǰ�Ƚ���һά 
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
	point p[maxn],mi[maxn],mx[maxn];//mx��ʾ����������ֵ��mi��ʾ��Сֵ 
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
		D=k;nth_element(a+l,a+m,a+r+1);//�ҳ���ǰλ���м��һ��Ԫ�ء� 
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
		D=k;//�򵥵������������Ĳ��� 
		if(ap<p[now])ins(son[now][0],ap,(k+1)%KD);
		else ins(son[now][1],ap,(k+1)%KD);
		pushup(now);
	}
	int dist(point x,point y)//ѯ��kά�ľ��� 
	{
		int tmp=0;
		for(int i=0;i<KD;i++)tmp+=abs(x.d[i]-y.d[i]);
		return tmp;
	}
	int nearmi(point ap,int x)//̰�ļ�֦�����Ǹ�������ѯ�ʵ�ľ������ 
	{
		if(!x)return inf;
		
		int tmp=0;
		for(int i=0;i<KD;i++)
		{
			//����˼·���ǿ�������������ߺ��ұ߷ֱ��㣬��ʱ������϶���Ҫ�Ƶġ� 
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
		int t2=nearmi(ap,son[now][1]);//��ѡ���ģ���ѡԶ�� 
		if(t1<=t2)
		{
			if(t1<ans)qmin(son[now][0],ap);//��֦ 
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
			//����Զ���룬������������ܵ���Զ���룬ÿ��̰�ĵ�ȡ��Զ�� 
			if(ap.d[i]<mi[x].d[i])tmp+=mx[x].d[i]-ap.d[i];
			else if(ap.d[i]>mx[x].d[i])tmp+=ap.d[i]-mi[x].d[i];
			else tmp+=max(mx[x].d[i]-ap.d[i],ap.d[i]-mi[x].d[i]);
		}
		return tmp;
	}
	void qmax(int now,point ap)
	{
		if(!now)return;
		//����ѯ�ʻ���˼·������Ȼ��̰�ĵ��� 
		ans=max(ans,dist(ap,p[now]));
		int t1=nearmx(ap,son[now][0]);
		int t2=nearmx(ap,son[now][1]);
		if(t1>=t2)
		{
			//ע����û��ans�ž�ֱ���˵����ɡ� 
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

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<cmath>

const int maxn=1005;
const double eps=1e-8;
const double pi=acos(-1.0);
using namespace std;

int dcmp(double x)
{
	if(fabs(x)<=eps)return 0;
	else return x<0?-1:1;
}
struct point
{
	double x,y;
	double ang;
	point(double x0=0,double y0=0){x=x0;y=y0;}
	void getang(){ang=atan2(y,x);}
}a[maxn],c[maxn],O,Ba;
struct abc
{
	point a,b,c;
}b[maxn];
typedef point vec;
vec operator +(const vec &x,const vec &y){return vec(x.x+y.x,x.y+y.y);}
vec operator -(const vec &x,const vec &y){return vec(x.x-y.x,x.y-y.y);}
vec operator *(const vec &x,const double &y){return vec(x.x*y,x.y*y);}
vec operator /(const vec &x,const double &y){return (point){x.x/y,x.y/y};}
double dot(const vec &x,const vec &y){return x.x*y.x+x.y*y.y;}
double cross(const vec &x,const vec &y){return x.x*y.y-x.y*y.x;}
bool operator ==(const vec &x,const vec &y){return x.x==y.x&&x.y==y.y;}
bool operator <(const vec &x,const vec &y){return dcmp(x.ang-y.ang)<0;}
bool comp(const vec &x,const vec &y){return dcmp(cross(x,y))>0;}
bool spi(const point &x,const point &y,const point &z,const point &w)
{
	double t1=cross(x-w,z-w),t2=cross(y-w,z-w);
	return dcmp(t1)*dcmp(t2)<0;
}
bool ons(const point &x,const point &y,const point &z)
{
	return dcmp(cross(x-y,x-z))==0&&dcmp(dot(y-x,z-x))<=0;
}
point getlinei(const point &p,const vec &v,const point &q,const vec &w)//��ֱ���󽻵� 
{
	vec u=p-q;
	double t=cross(w,u)/cross(v,w);
	return p+v*t;
}
bool rspi(const point &x,const point &y,const point &z,const point &w)
{
	if(spi(x,y,z,w))return true;
	//point p=getlinei(x,y-x,z,w-z);
	return ons(z,x,y)||ons(w,x,y);
}
int n,m;
struct myl
{
	point u,v;
	double ang;
	int k,id;
	friend bool operator <(const myl &one,const myl &two)
	{
		point p=getlinei(one.u,one.v-one.u,O,Ba);
		point p2=getlinei(two.u,two.v-two.u,O,Ba);
		return dcmp(dot(p,p)-dot(p2,p2))<0;
	}
}d[maxn*4];
bool comp2(const myl &x,const myl &y){return dcmp(x.ang-y.ang)<0;}
multiset<myl>s;
multiset<myl>::iterator it,itt[maxn*2];
int main()
{
	//����֮���Կ�����ɨ���ߣ�����Ϊ��Щ���ǲ��ཻ�ģ���һ����һ��λ�����ȣ��ͻ�������λ�����ȡ� 
	freopen("input.txt","r",stdin);
	point w[5];O=(0.0,0.0);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf",&a[i].x,&a[i].y);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%lf%lf%lf%lf%lf%lf",&b[i].a.x,&b[i].a.y,&b[i].b.x,&b[i].b.y,&b[i].c.x,&b[i].c.y);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		//ɨ���ߵ�һ����ȷ������ 
		s.clear(); 
		for(int ii=i+1;ii<=n;ii++)
		{
			c[ii]=a[ii]-a[i];
			c[ii].getang();
		}
		sort(c+i+1,c+n+1);
		int tot=0,idcnt=0;
		for(int ii=1;ii<=m;ii++)
		{
			w[1]=b[ii].a-a[i];
			w[2]=b[ii].b-a[i];
			w[3]=b[ii].c-a[i];
			//�������ڶ�������ȡһ�����õ��߶Σ�������Ϊû�е��������ε��ڲ�
			//ͬʱֻҪû�п�Խ180�Ĵ�ǣ�������ֱ�ӶԲ������ 
			sort(w+1,w+4,comp);//ע��˴�Ӧ�Բ��������Ϊ�����ɱ����Խ+180��-180ʱ���鷳�� 
			w[1].getang();w[3].getang();
			if(w[1].ang>w[3].ang)//���ڿ�Խ�����������ߵģ�Ӧ�ò�ֳ������߶ν��д��� 
			{
				point tmp=getlinei(w[1],w[3]-w[1],O,point(-1,0));
				
				++idcnt;
				d[++tot]=(myl){w[1],tmp,w[1].ang,0,idcnt};
				//�˴�һ��ϸ�ڣ��˴���ȻΪpi,����˴�����õĽǣ���Ȼ������⣨���������жϣ��� 
				d[++tot]=(myl){w[1],tmp,pi,1,idcnt};
				 
				idcnt++;
				d[++tot]=(myl){tmp,w[3],-pi,0,idcnt};
				d[++tot]=(myl){tmp,w[3],w[3].ang,1,idcnt};
			}
			else
			{
				idcnt++;
				d[++tot]=(myl){w[1],w[3],w[1].ang,0,idcnt};
				d[++tot]=(myl){w[1],w[3],w[3].ang,1,idcnt};
			}	
		}
		sort(d+1,d+tot+1,comp2);//���������� 
		int l=1;
		for(int ii=i+1;ii<=n;ii++)
		{
			while(l<=tot&&((dcmp(d[l].ang-c[ii].ang)<=0&&d[l].k==0)||dcmp(d[l].ang-c[ii].ang)<0))
			{
				//�˴�һ��ɾ�Ͳ��붼Ҫ���У���Ϊ������֤���߶β��ཻ��
				//������ֱ�ߣ���ÿ�ζ�Ҫ���¶�base��ͬʱΪ�˱�֤�����������߶ζ��������λ�ã�
				//����һ��Ҫ��ʱɾ�� 
				Ba=d[l].u;
				if(d[l].k)
				{
					s.erase(itt[d[l].id]);
				}
				else
				{
					itt[d[l].id]=s.insert(d[l]);
				}
				l++;
			}
			Ba=c[ii];
			it=s.begin();
			if(it!=s.end())
			{
				if(!rspi(c[ii],O,it->u,it->v))ans++;
			}
			else ans++;
		}
		//printf("%.2lf %.2lf %d\n",a[i].x,a[i].y,ans);
	}
	printf("%d\n",ans);
	return 0;
}

//acos����ֵ��[0,pi]֮��
//asin����ֵ��[-pi/2,pi/2]
//atan        [-pi/2,pi/2]
//atan2(y,x),����ֵ[-pi,pi] 
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cmath>

const double eps=1e-10;
const int maxn=310;
using namespace std;

int dcmp(double x)
{
	if(fabs(x)<=eps)return 0;
	else return x<0?-1:1;
}
struct point
{
	double x,y;
	point(double x0=0,double y0=0){x=x0;y=y0;}
};
typedef point vec;
vec operator +(const vec &x,const vec &y){return vec(x.x+y.x,x.y+y.y);}
vec operator -(const vec &x,const vec &y){return vec(x.x-y.x,x.y-y.y);}
vec operator *(const vec &x,const double &y){return vec(x.x*y,x.y*y);}
vec operator /(const vec &x,const double &y){return (point){x.x/y,x.y/y};}
bool operator ==(const vec &x,const vec &y){return x.x==y.x&&x.y==y.y;}
bool operator <(const vec &x,const vec &y){return x.x!=y.x?x.x<y.x:x.y<y.y;}
double dot(const vec &x,const vec &y){return x.x*y.x+x.y*y.y;}
double cross(const vec &x,const vec &y){return x.x*y.y-x.y*y.x;}
double length(const vec &x){return sqrt(dot(x,x));}
//���㼸�κܶ඼�Ǵ�dot��length��������ġ�
//�淶�ཻ��ԭ�������������߶ε������˵��Ƿ������
//��ô����Ҫ�淶�ཻ��?һ��Ҫ�����ж˵��Ƿ�����һ��ֱ���ϣ����У���������ͬһֱ���ϵĲ�ͬ�߶λ�Ӱ�졣 
//�����Ĵε��Ƿ���ֱ���ϣ������Ĵε��Ƿ��ص�(�ɲ������У����ཻ���ǹ淶�ཻ�Ļ�) 
bool spi(const point &x,const point &y,const point &z,const point &w)//�淶�ཻ 
{
	double t1=cross(y-w,z-w),t2=cross(x-w,z-w),
		   t3=cross(w-y,x-y),t4=cross(z-y,x-y);
	if(dcmp(t1)*dcmp(t2)<0&&dcmp(t3)*dcmp(t4)<0)return true;
	return false;
}
double dts(const point &p,const point &x,const point &y)//�㵽�߶εľ��� 
{
	if(x==y)return length(p-x);
	vec v1=p-x,v2=p-y,v3=y-x,v4=x-y;
	if(dcmp(dot(v1,v3))<0)return length(v1);
	else if(dcmp(dot(v2,v4))<0)return length(v2);
	else return fabs(cross(v1,v3))/length(v3);
}
point getlinei(const point &p,const vec &v,const point &q,const vec &w)//��ֱ���󽻵� 
{
	vec u=p-q;
	double t=cross(w,u)/cross(v,w);
	return p+v*t;
}
//����ֱ���ϣ�����˼·��x,p,y,Ҳ�ǹ淶��ֱ���ϣ�����ÿ����Ҫ�����С�
bool ons(const point &p,const point &x,const point &y)//�����߶��ϣ������˵�
{
	//��Ҫ���˵�,�ڶ�����Ϊ<=0 
	return dcmp(cross(x-p,y-p))==0&&dcmp(dot(x-p,y-p))<0;
}
vec rotate(const vec &x,double ang){
return vec(x.x*cos(ang)-x.y*sin(ang),x.x*sin(ang)+x.y*cos(ang));}//��ת
vec normal(const vec &x){double t=length(x);return vec(-x.y/t,x.x/t);}//������ 
int getchull(point *p,int n,point *ch)//��͹�� 
{
	sort(p+1,p+n+1);//����͹��Ҫ������ 
	int m=0;
	for(int i=1;i<=n;i++)
	{
		//����ȡ��ȡ����ȡ����͹�����ϵĵ㱣������������ʱ������� 
		while(m>=2&&cross(ch[m]-ch[m-1],p[i]-ch[m-1])<=0)m--;
		ch[++m]=p[i];
	}
	
	//����ϸ�ڣ��˴�����Ҫ�½��ף������m>k 
	int k=m;
	for(int i=n-1;i>=1;i--)//��ε�n����Ͳ�����һ���ˣ���Ϊ�Ѿ��Ž�ȥ�ˣ���1�ŵ���ȻҪ�㣬���򲻶� 
	{
		while(m>k&&cross(ch[m]-ch[m-1],p[i]-ch[m-1])<=0)m--;
		ch[++m]=p[i];
	}
	if(n>1)m--;//�����˵�����Ϊ1�ŵ㱻�ظ���������Σ�����n==1ʱ��1�ǽ������һ�εġ� 
	return m;
}
double parea(point *ch,int m)//�����η���͹�������� 
{
	double tmp=0;
	for(int i=2;i<m;i++)
	{
		//ע��˴�����ʱ���������������ƽ���ı��У�Ҫ����2�ġ� 
		tmp+=cross(ch[i]-ch[1],ch[i+1]-ch[1]);
	}
	return tmp/2;
}
//������
int inp(const point &p,point *poly,int n)//����͹����ε�λ�ù�ϵ 
{
	//������һ��ˮƽ���ҵ����ߣ���ͨ��˳����ٴΡ������ڸõ����ߣ����ǿ��԰�����ת������⣩ 
	//I~I,~��ʾ��Ļ�������Ϊ2�� 
	poly[n+1]=poly[1];//ע��Ҫ����1�ŵ㸴�Ƶ���n+1�ŵ�ȥ�� 
	int wn=0;
	for(int i=1;i<=n;i++)
	{
		if(ons(p,poly[i],poly[i+1]))return -1;//���ڶ���б��� 
		int k=dcmp(cross(poly[i+1]-poly[i],p-poly[i]));
		int d1=dcmp(poly[i].y-p.y);
		int d2=dcmp(poly[i+1].y-p.y);
		//ע��һ��ϸ�ڣ�ֻ��һ��ȡ��(�������ıߣ�������ν�ģ���Ϊ����һ���������㶼�����أ���������ء� 
		if(k>0&&d1<=0&&d2>0)wn++;//����εı���ʱ�봩���� 
		if(k<0&&d2<=0&&d1>0)wn--;//����εı�˳ʱ�봩���� 
	}
	if(wn!=0)return 1;
	return 0;
}
double getmax(point *p,int n)//��ת���� 
{
	int j=2;
	double tmp=0;
	p[0]=p[n];
	p[n+1]=p[1];
	//����ԭ���������˵��ƶ��ĵ����� 
	for(int i=1;i<=n;i++)//��ת���ǻ���˼·�Ƕ���ÿһ���ߣ����ҳ���Ӧ����Զ�ıߡ� 
	{
		//��һֱ��ת����������ת����һ������Ϊֹ����ʱ���Ա�֤���ڵ�i,��õ�һ������Զ�� 
		while(cross(p[i+1]-p[i],p[(j+1)%n]-p[j])>0)j=(j+1)%n;
		tmp=max(tmp,length(p[i+1]-p[j]));
		tmp=max(tmp,length(p[i+1]-p[(j+1)%n]));
		tmp=max(tmp,length(p[i]-p[j]));
		tmp=max(tmp,length(p[i]-p[(j+1)%n]));
	}
	return tmp;
}
struct line
{
	point p;
	vec v;
	double ang;
	line(){}
	line(point p,vec v):p(p),v(v){ang=atan2(v.y,v.x);}
	bool operator <(const line &l)const{
		return ang<l.ang;
	}
};
point getlinei(line x,line y)//�����ཻ 
{
	vec u=x.p-y.p;
	double t=cross(y.v,u)/cross(x.v,y.v);
	return x.p+x.v*t;
}
bool onleft(point p,line l)//�������� 
{
	//�˴����ڼ���Ϊ���Ͽ��У�������ϲ����С� 
	return dcmp(cross(l.v,p-l.p))>=0;
}
line q[maxn];
int hpi(line *l,int n,point *p)//��ƽ�潻 
{
	//���������� 
	sort(l+1,l+n+1);
	
	int first=1,last=0;
	for(int i=1;i<=n;i++)
	{
		//ɾ��ǰ������ƽ�棬last��ǰ��first�ں� 
		//ɾ��ĩ������ƽ�棬ͨ���жϵ��Ƿ���������ȷ�� 
		while(first<last && !onleft(p[last-1],l[i])) last--;
		while(first<last && !onleft(p[first],l[i])) first++;
		
		if(dcmp(l[i].ang-q[last].ang)==0)//������ƽ��ʱѡһ������ߵģ�������������ang�ò��Ҳ�� 
		q[last]=onleft(l[i].p,q[last])?l[i]:q[last];
		else q[++last]=l[i];//�������ñ� 
		
		if(last>first)p[last-1]=getlinei(q[last],q[last-1]);//�����µĵ� 
	}
	while(first<last&&!onleft(p[last-1],q[first]))last--;//���ɾ��ǰ�˲���ȷ�ĵ�
	
	if(last-first<=1)return 0;//�������ޱ߽�����ʱ������Ҫ��ӱ߽�ģ����������������һ�������Ҫ�����޽⣬������Ӧ����3���߶� 
	p[last]=getlinei(q[last],q[first]);
	
	return last-first+1;
}
double f(double x)//����ֵ 
{
	return 0;
}
double cut(double l,double r,double fl,double fm,double fr)//����ɭ��ʽ 
{
	return (r-l)/6*(4*fm+fl+fr);
}
//������Щf����ǳ��������Ծ����ܵ��ظ�ʹ��һЩ���� 
double simpson(double l,double mid,double r,double fl,double fm,double fr,double s)//����ɭ������ 
{
	double mid1=(l+mid)/2,mid2=(mid+r)/2;
	double fm1=f(mid1),fm2=f(mid2);
	double s1=cut(l,mid,fl,fm1,fm);
	double s2=cut(mid,r,fm,fm2,fr);
	if(dcmp(s-s1-s2)==0)return s;
	return simpson(l,mid1,mid,fl,fm1,fm,s1)+simpson(mid,mid2,r,fm,fm2,fr,s2);
}
void mcc(point *p,int n,point &cc,double &r)//��СԲ 
{
	random_shuffle(p+1,p+n+1);//�����p���� 
	cc=p[1];
	r=0;
	for(int i=2;i<=n;i++)
	{
		if(dcmp(length(cc-p[i])-r)>0)//������һ���㲻�ڵ�ǰԲ�С� 
		{
			cc=p[i];
			r=0;
			for(int ii=1;ii<i;ii++)
			{
				if(dcmp(length(cc-p[ii])-r)>0)//�����ֵڶ��㲻��Բ�� 
				{
					cc.x=(p[i].x+p[ii].x)/2;
					cc.y=(p[i].y+p[ii].y)/2;
					r=length(cc-p[i]);
					for(int i3=1;i3<ii;i3++)
					{
						if(dcmp(length(cc-p[i3])-r)>0)//�����ֵ������㲻��Բ�� 
						{
							cc=getcc(p[i],p[ii],p[i3]);//�����д����㽹�� 
							r=length(cc-p[i]);
						}
					}
				}
			}
		}
	}
}
int main()
{
	return 0;
}

//acos返回值在[0,pi]之间
//asin返回值在[-pi/2,pi/2]
//atan        [-pi/2,pi/2]
//atan2(y,x),返回值[-pi,pi] 
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
//计算几何很多都是从dot和length引申出来的。
//规范相交，原理在于判两条线段的两个端点是否在异侧
//那么不需要规范相交呢?一定要单独判端点是否在另一条直线上，易判，否则两在同一直线上的不同线段会影响。 
//先判四次点是否在直线上，再判四次点是否重叠(可不单独判，若相交不是规范相交的话) 
bool spi(const point &x,const point &y,const point &z,const point &w)//规范相交 
{
	double t1=cross(y-w,z-w),t2=cross(x-w,z-w),
		   t3=cross(w-y,x-y),t4=cross(z-y,x-y);
	if(dcmp(t1)*dcmp(t2)<0&&dcmp(t3)*dcmp(t4)<0)return true;
	return false;
}
double dts(const point &p,const point &x,const point &y)//点到线段的距离 
{
	if(x==y)return length(p-x);
	vec v1=p-x,v2=p-y,v3=y-x,v4=x-y;
	if(dcmp(dot(v1,v3))<0)return length(v1);
	else if(dcmp(dot(v2,v4))<0)return length(v2);
	else return fabs(cross(v1,v3))/length(v3);
}
point getlinei(const point &p,const vec &v,const point &q,const vec &w)//两直线求交点 
{
	vec u=p-q;
	double t=cross(w,u)/cross(v,w);
	return p+v*t;
}
//点在直线上：基本思路是x,p,y,也是规范在直线上，对于每个点要单独判。
bool ons(const point &p,const point &x,const point &y)//点在线段上，不含端点
{
	//若要含端点,第二处改为<=0 
	return dcmp(cross(x-p,y-p))==0&&dcmp(dot(x-p,y-p))<0;
}
vec rotate(const vec &x,double ang){
return vec(x.x*cos(ang)-x.y*sin(ang),x.x*sin(ang)+x.y*cos(ang));}//旋转
vec normal(const vec &x){double t=length(x);return vec(-x.y/t,x.x/t);}//法向量 
int getchull(point *p,int n,point *ch)//求凸包 
{
	sort(p+1,p+n+1);//首先凸包要先排序。 
	int m=0;
	for(int i=1;i<=n;i++)
	{
		//这里取不取等于取决于凸包边上的点保不保留，方向到时候可再推 
		while(m>=2&&cross(ch[m]-ch[m-1],p[i]-ch[m-1])<=0)m--;
		ch[++m]=p[i];
	}
	
	//两个细节：此处首先要新建底，其次是m>k 
	int k=m;
	for(int i=n-1;i>=1;i--)//其次第n个点就不在算一遍了，因为已经放进去了，但1号点仍然要算，否则不对 
	{
		while(m>k&&cross(ch[m]-ch[m-1],p[i]-ch[m-1])<=0)m--;
		ch[++m]=p[i];
	}
	if(n>1)m--;//这里退掉是因为1号点被重复入队了两次，但当n==1时，1是仅被入队一次的。 
	return m;
}
double parea(point *ch,int m)//三角形法求凸多边形面积 
{
	double tmp=0;
	for(int i=2;i<m;i++)
	{
		//注意此处是逆时针有向面积，且是平行四边行，要除以2的。 
		tmp+=cross(ch[i]-ch[1],ch[i+1]-ch[1]);
	}
	return tmp/2;
}
//绕数法
int inp(const point &p,point *poly,int n)//点与凸多边形的位置关系 
{
	//假想有一个水平向右的射线，求通过顺逆多少次。（对于该点的左边，我们可以把它旋转过来理解） 
	//I~I,~表示点的话，绕数为2。 
	poly[n+1]=poly[1];//注意要将第1号点复制到第n+1号点去。 
	int wn=0;
	for(int i=1;i<=n;i++)
	{
		if(ons(p,poly[i],poly[i+1]))return -1;//点在多边行边上 
		int k=dcmp(cross(poly[i+1]-poly[i],p-poly[i]));
		int d1=dcmp(poly[i].y-p.y);
		int d2=dcmp(poly[i+1].y-p.y);
		//注意一个细节，只能一边取等(至于是哪边，是无所谓的，因为不会一条边两个点都与它重，否则会算重。 
		if(k>0&&d1<=0&&d2>0)wn++;//多边形的边逆时针穿过。 
		if(k<0&&d2<=0&&d1>0)wn--;//多边形的边顺时针穿过。 
	}
	if(wn!=0)return 1;
	return 0;
}
double getmax(point *p,int n)//旋转卡壳 
{
	int j=2;
	double tmp=0;
	p[0]=p[n];
	p[n+1]=p[1];
	//基本原理是利用了点移动的单调性 
	for(int i=1;i<=n;i++)//旋转卡壳基本思路是对于每一条边，都找出对应的最远的边。 
	{
		//及一直旋转到不能再旋转距离一定减少为止，此时可以保证对于点i,求得的一定是最远点 
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
point getlinei(line x,line y)//两线相交 
{
	vec u=x.p-y.p;
	double t=cross(y.v,u)/cross(x.v,y.v);
	return x.p+x.v*t;
}
bool onleft(point p,line l)//点在线左 
{
	//此处等于即以为边上可行，否则边上不可行。 
	return dcmp(cross(l.v,p-l.p))>=0;
}
line q[maxn];
int hpi(line *l,int n,point *p)//半平面交 
{
	//按极角排序 
	sort(l+1,l+n+1);
	
	int first=1,last=0;
	for(int i=1;i<=n;i++)
	{
		//删除前端无用平面，last在前，first在后 
		//删除末端无用平面，通过判断点是否在线左来确定 
		while(first<last && !onleft(p[last-1],l[i])) last--;
		while(first<last && !onleft(p[first],l[i])) first++;
		
		if(dcmp(l[i].ang-q[last].ang)==0)//当出现平行时选一个在左边的，这里用若不用ang用叉积也行 
		q[last]=onleft(l[i].p,q[last])?l[i]:q[last];
		else q[++last]=l[i];//否则加入该边 
		
		if(last>first)p[last-1]=getlinei(q[last],q[last-1]);//更新新的点 
	}
	while(first<last&&!onleft(p[last-1],q[first]))last--;//最后删除前端不正确的点
	
	if(last-first<=1)return 0;//但处理无边界问题时，我们要外加边界的，故若算出来够不成一个区域就要返回无解，故至少应该有3条线段 
	p[last]=getlinei(q[last],q[first]);
	
	return last-first+1;
}
double f(double x)//求函数值 
{
	return 0;
}
double cut(double l,double r,double fl,double fm,double fr)//辛普森公式 
{
	return (r-l)/6*(4*fm+fl+fr);
}
//考虑有些f运算非常慢，所以尽可能的重复使用一些变量 
double simpson(double l,double mid,double r,double fl,double fm,double fr,double s)//辛普森主程序 
{
	double mid1=(l+mid)/2,mid2=(mid+r)/2;
	double fm1=f(mid1),fm2=f(mid2);
	double s1=cut(l,mid,fl,fm1,fm);
	double s2=cut(mid,r,fm,fm2,fr);
	if(dcmp(s-s1-s2)==0)return s;
	return simpson(l,mid1,mid,fl,fm1,fm,s1)+simpson(mid,mid2,r,fm,fm2,fr,s2);
}
void mcc(point *p,int n,point &cc,double &r)//最小圆 
{
	random_shuffle(p+1,p+n+1);//随机化p个点 
	cc=p[1];
	r=0;
	for(int i=2;i<=n;i++)
	{
		if(dcmp(length(cc-p[i])-r)>0)//当出现一个点不在当前圆中。 
		{
			cc=p[i];
			r=0;
			for(int ii=1;ii<i;ii++)
			{
				if(dcmp(length(cc-p[ii])-r)>0)//当出现第二点不在圆中 
				{
					cc.x=(p[i].x+p[ii].x)/2;
					cc.y=(p[i].y+p[ii].y)/2;
					r=length(cc-p[i]);
					for(int i3=1;i3<ii;i3++)
					{
						if(dcmp(length(cc-p[i3])-r)>0)//当出现第三个点不在圆中 
						{
							cc=getcc(p[i],p[ii],p[i3]);//两两中垂线算焦点 
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

//fft用途可以用于多项式乘法（即卷积），其他通过构造多项式系数来算，
//注意构造要满足多项式乘法的系数变化。例如(1+2*x)*(2+3*x+4*x*x)。 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

const int maxn=200005;
const double pi=acos(-1.0);
using namespace std;

struct fftnum
{
	double x;
	double y;
	fftnum(){}
	fftnum(double _x,double _y){x=_x;y=_y;}
	friend fftnum operator +(const fftnum &x,const fftnum &y)
	{
		return fftnum(x.x+y.x,x.y+y.y);
	}
	friend fftnum operator -(const fftnum &x,const fftnum &y)
	{
		return fftnum(x.x-y.x,x.y-y.y);
	}
	friend fftnum operator *(const fftnum &x,const fftnum &y)
	{
		return fftnum(x.x*y.x-x.y*y.y,x.y*y.x+x.x*y.y);
	}
};
void _scanf(fftnum *a,int n)
{
	int tmp=n;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while('0'<=ch&&ch<='9'){a[--tmp].x=ch-48;ch=getchar();}
}
int r[maxn];
int n,m,l;
fftnum a[maxn],b[maxn];
void fft(fftnum *c,int f)
{
	for(int i=0;i<n;i++)if(i<r[i])swap(c[i],c[r[i]]);
	
	for(int i=1;i<n;i=(i<<1))//第一维控制将被操作的长度 
	{
		fftnum wn(cos(pi/i),sin(f*pi/i)),x,y;//先cos后sin 
		for(int ii=0;ii<n;ii+=(i<<1))//第二维控制起点 
		{
			fftnum w(1,0);
			for(int i3=0;i3<i;i3++,w=w*wn)//合并最低的两块 
			{
				x=c[ii+i3];y=w*c[i+ii+i3];//都是前一个无变化，后一个要乘 
				c[ii+i3]=x+y;
				c[i+ii+i3]=x-y;
			}
		}
	}
}
int d[maxn];
int main()
{
	scanf("%d",&n);
	//a,b为目标数组,下面不变即可。 
	_scanf(a,n);
	_scanf(b,n);
	m=n*2;
	for(n=1;n<m;n=(n<<1))l++;
	for(int i=0;i<n;i++)r[i]=((r[i>>1]>>1)|((i&1)<<(l-1)));
	fft(a,1);
	fft(b,1);
	for(int i=0;i<n;i++)a[i]=a[i]*b[i];
	
	fft(a,-1);//fft逆过程，-1即可
	for(int i=0;i<n;i++)a[i].x/=n,a[i].y/=n;//注意除以n 
	//此时a便为新函数的值。 
	for(int i=0;i<=m;i++)
	{
		d[i]+=(int)(a[i].x+0.1);
		d[i+1]+=d[i]/10,d[i]=d[i]%10;
	}
	while(d[m]==0)m--;
	for(int i=m;i>=0;i--)putchar(d[i]+'0');
	putchar('\n');
	return 0;
} 

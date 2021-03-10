#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>

const int maxn=40005;
const int maxm=50005;
using namespace std;

int n,a[maxn],b[maxn];
int sn,tn;//sn为块长，tn为块数。 
struct myblock
{
	int c[205][205],inq[maxn],inq2[maxn],f[205][40005];
	//c[i][ii]表示从i块到ii块的众数，f[i][ii]表示1-i的块每个数出现的次数 
	int qid;
	void get_most()
	{
		qid=0;
		for(int i=1;i<=tn;i++)
		{
			memset(inq,0,sizeof(inq));
			int md=0,mi=0;
			for(int ii=i;ii<=tn;ii++)
			{
				for(int i3=sn*(ii-1)+1;i3<=sn*ii;i3++)
				{
					inq[a[i3]]++;
					if(inq[a[i3]]>md)
					{
						md=inq[a[i3]];
						mi=a[i3];
					}
					if(inq[a[i3]]==md&&a[i3]<mi)
						mi=a[i3];
				}
				c[i][ii]=mi;
			}
		}
		
		memset(inq,0,sizeof(inq));
		for(int i=1;i<=tn;i++)
		{
			for(int ii=sn*(i-1)+1;ii<=sn*i;ii++)
				inq[a[ii]]++;
			memcpy(f[i],inq,sizeof(inq[0])*(n+1));
		}
		memset(inq,0,sizeof(inq));
	}
	int query2(int l,int r)
	{
		qid++;//标记从而不用memset 
		int md=0;
		int mi=0;
		for(int i=l;i<=r;i++)
		{
			if(inq2[a[i]]!=qid)
			{
				inq2[a[i]]=qid;
				inq[a[i]]=0;
			}
			inq[a[i]]++;
			if(inq[a[i]]>md)
			{
				md=inq[a[i]];
				mi=a[i];
			}
			if(inq[a[i]]==md&&a[i]<mi)
			{
				mi=a[i];
			}
		}
		return mi;
	}
	int query(int l,int r)
	{
		qid++;
		int wl=(l-1)/sn+1,wr=(r-1)/sn+1;//求出块编号 
		int md=0,mi=0;
		if(wr-wl>1)//处理位于不同块
		{
			inq2[c[wl+1][wr-1]]=qid;
			inq[c[wl+1][wr-1]]=f[wr-1][c[wl+1][wr-1]]-f[wl][c[wl+1][wr-1]];
			md=inq[c[wl+1][wr-1]];
			mi=c[wl+1][wr-1];
			for(int i=l;i<=wl*sn;i++)//暴力枚举左边部分
			{
				if(inq2[a[i]]!=qid)
				{
					inq2[a[i]]=qid;
					inq[a[i]]=f[wr-1][a[i]]-f[wl][a[i]];
				}
				inq[a[i]]++;
				if(inq[a[i]]>md)
				{
					md=inq[a[i]];
					mi=a[i];
				}
				if(inq[a[i]]==md&&a[i]<mi)
				{
					mi=a[i];
				}
			}
			for(int i=(wr-1)*sn+1;i<=r;i++)//暴力枚举右边部分 
			{
				if(inq2[a[i]]!=qid)
				{
					inq2[a[i]]=qid;
					inq[a[i]]=f[wr-1][a[i]]-f[wl][a[i]];
				}
				inq[a[i]]++;
				if(inq[a[i]]>md)
				{
					md=inq[a[i]];
					mi=a[i];
				}
				if(inq[a[i]]==md&&a[i]<mi)
				{
					mi=a[i];
				}
			}
			return mi;
		}
		else return query2(l,r);//暴力处理位于同一块 
	}
}c;
int main()
{
	int ai,bi;
	scanf("%d",&n);
	int m;
	scanf("%d",&m);
	sn=sqrt(n+0.5);
	tn=n/sn;
	
	//离散化 
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	int tot=unique(b+1,b+n+1)-b;
	tot--;
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(b+1,b+tot+1,a[i])-b;
	
	c.get_most();
	int x=0;
	
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&ai,&bi);
		ai=(ai+x-1)%n+1;
		bi=(bi+x-1)%n+1;
		if(ai>bi)swap(ai,bi);
		x=b[c.query(ai,bi)];
		//x=b[c.query2(ai,bi)];
		printf("%d\n",x);
		//x=0;
	}
	return 0;
}

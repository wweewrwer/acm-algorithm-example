#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=500005;
using namespace std;

struct mydata
{
	int son[2];
	int w;
};
struct myheap
{
	int rt[105],np;//这个结构体里有很多个堆
	mydata c[maxn];
	int merge(int a,int b)//合并
	{
		if(a==0||b==0)return a+b;
		if(c[a].w>c[b].w)swap(a,b);
		c[a].son[1]=merge(c[a].son[1],b);
		swap(c[a].son[1],c[a].son[0]);
		return a;
	}
	int push(int a,int x)//插入 
	{
		c[++np].w=x;
		return merge(a,np);
	}
	int pop(int a)//弹出 
	{
		return merge(c[a].son[0],c[a].son[1]);
	}
	int top(int a)//求top 
	{
		return c[a].w;
	}
}q;
char s[15];
int main()
{
	int n,m;
	int ai,bi;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%s",s);
		if(s[0]=='A')
		{
			scanf("%d%d",&ai,&bi);
			q.rt[ai]=q.push(q.rt[ai],bi);
		}
		else if(s[0]=='D')
		{
			scanf("%d",&ai);
			if(q.rt[ai]==0)continue;
			q.rt[ai]=q.pop(q.rt[ai]);
		}
		else if(s[0]=='M')
		{
			scanf("%d%d",&ai,&bi);
			if(ai==bi)continue;
			q.rt[ai]=q.merge(q.rt[ai],q.rt[bi]);
			q.rt[bi]=0;
		}
		else if(s[0]=='Q')
		{
			scanf("%d",&ai);
			if(q.rt[ai]==0)printf("NOne\n");
			else printf("%d\n",q.top(q.rt[ai]));
		}
	}
	return 0;
}

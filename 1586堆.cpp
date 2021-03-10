#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=100005;
using namespace std;

struct myheap
{
	int w[maxn],np;
	void push(int x)
	{
		w[++np]=x;
		int i=np/2,j=np;
		while(i>0)
		{
			if(w[i]<=w[j])break;
			swap(w[i],w[j]);
			j=i;
			i=j/2;
		}
	}
	void pop()
	{
		w[1]=w[np];np--;
		int i=2,j=1;
		while(i<=np)
		{
			if(i+1<=np&&w[i+1]<w[i])i++;
			if(w[i]>=w[j])break;
			swap(w[i],w[j]);
			j=i;
			i=j*2;
		}
	}
	int top()
	{
		return w[1];
	}
}q;
int n;
int main()
{
	int ai,bi;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&ai);
		if(ai==1)
		{
			scanf("%d",&bi);
			q.push(bi);
		}
		else if(ai==2&&q.np!=0)
		{
			printf("%d\n",q.top());
		}
		else if(ai==3&&q.np!=0)
		{
			q.pop();
		}
	}
	return 0;
}

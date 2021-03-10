//推期望倒推，概率正推 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>

const int maxn=100005;
using namespace std;

int n,m;
int du[maxn],ru[maxn];
double vis[maxn],vis2[maxn];
vector<int>ma[maxn],mb[maxn];
void dp(int s)
{
	int tot;
	queue<int>q;
	q.push(s);
	while(!q.empty())
	{
		int k=q.front();q.pop();
		tot=ma[k].size();
		for(int i=0;i<tot;i++)
		{
			vis[k]+=1.0/tot*vis[ma[k][i]];
			vis2[k]+=1.0/tot*(vis2[ma[k][i]]);
		}
		if(tot!=0)vis[k]+=(1.0+tot)/tot;
		if(tot!=0)vis2[k]+=(1.0+tot)/tot*vis[k];
		tot=mb[k].size();
		for(int i=0;i<tot;i++)
		{
			du[mb[k][i]]--;
			if(du[mb[k][i]]==0)q.push(mb[k][i]);
		}
	}
}
int main()
{
	int t;
	scanf("%d",&t);
	int ai,bi;
	while(t!=0)
	{
		t--;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
		{
			du[i]=ru[i]=0;
			vis[i]=vis2[i]=0;
			ma[i].clear();
			mb[i].clear();
		}
		for(int ii=1;ii<=m;ii++)
		{
			scanf("%d%d",&ai,&bi);
			ma[ai].push_back(bi);
			du[ai]++;
			mb[bi].push_back(ai);
			ru[bi]++;
		}
		for(int i=1;i<=n;i++)
		{
			if(du[i]==0)
			{
				vis[i]=0;
				dp(i);
				break;
			}
		}
		for(int i=1;i<=n;i++)
		{
			if(ru[i]==0)
			{
				printf("%.2lf\n",vis2[i]);
				break;
			}
		}
	}
	return 0;
}

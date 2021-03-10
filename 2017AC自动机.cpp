#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>

const int maxnode=1100005;
using namespace std;

int n,ch[maxnode][26],val[maxnode],f[maxnode],last[maxnode],np,rt,vis[maxnode];
char s[55],p[100005];
void initial()
{
	memset(ch,0,sizeof(ch));
	memset(f,0,sizeof(f));
	memset(last,0,sizeof(last));
	np=rt=0;
}
int idx(char ach)
{
	return ach-'a';
}
void insert(int &now,int i,char *s)
{
	if(!now&&i!=0)now=++np;
	
	if(!s[i])
	{
		val[now]++;
		return;
	}
	int k=idx(s[i]);
	insert(ch[now][k],i+1,s);
}
void getfail()
{
	queue<int>q;
	f[0]=0;
	for(int i=0;i<26;i++)
	{
		int u=ch[0][i];
		if(u){f[u]=0;q.push(u);last[u]=0;}
	}
	while(!q.empty())
	{
		int r=q.front();q.pop();
		for(int i=0;i<26;i++)
		{
			int u=ch[r][i];
			if(!u){ch[r][i]=ch[f[r]][i];continue;}
			q.push(u);
			f[u]=ch[f[r]][i];
			last[u]= val[f[u]] ? f[u]:last[f[u]];
		}
	}
}
int ans=0;
void add(int j)
{
	if(vis[j])return;
	ans++;
	vis[j]++;
}
void print(int j)
{
	if(!j)return;
	add(j);
	print(last[j]);
}
void find(char *t)
{
	int m=strlen(t);
	int j=0;
	for(int i=0;i<m;i++)
	{
		int c=idx(t[i]);
		j=ch[j][c];
		if(val[j])print(j);
		else if(last[j])print(last[j]);
	}
}
int main()
{
	//freopen("input.txt","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s);
		insert(rt,0,s);
	}
	getfail();
	scanf("%s",p);
	find(p);
	printf("%d\n",ans);
	return 0;
}


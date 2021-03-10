#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=1000005;
using namespace std;

int n,T;
struct state
{
	//par��par���еıߣ���ʾright��,par�����γ�һ���� 
	//go����ʵ��ת�Ʊ� 
	int par,go[26];
	int val;//val�����ĳ��� 
}c[maxn];
struct SAM
{
	long long vis[maxn],ww[maxn];int v[maxn],wh[maxn];
	int rt,last,np;
	SAM(){rt=last=++np;}
	void extend(int w)//һ��һ������������ 
	{
		int p=last;//�ҵ���β,Ϊ����λ�õĺ�׺ 
		c[last=++np].val=c[p].val+1;//�½�np,Ϊ�µĽ���λ�õĺ�׺ 
		int now=np;
		ww[np]=1;
		while(p&&c[p].go[w]==0)//����û�б��Ϊx�ıߵ����ȣ���һ���� 
		{
			c[p].go[w]=np;
			p=c[p].par;
		}
		if(p==0)//�����ȶ�û��ȥx�ıߣ���һ������now�ı� 
			c[now].par=rt;
		else
		{
			int q=c[p].go[w];//�ҳ�������ȥx�ı� 
			if(c[p].val+1==c[q].val)//��ǡ�ó����Ǻϣ�ֱ�ӽ���ȥ���� 
				c[now].par=q;
			else
			{
				c[++np].val=c[p].val+1;
				int nq=np;//�½�һ���ڵ���������ĳ���Ϊԭ���Ǻϳ��� 
				memcpy(c[nq].go,c[q].go,sizeof(c[q].go));//���� 
				c[nq].par=c[q].par;//ȡ��q 
				c[q].par=nq;//��q��faΪnq 
				c[now].par=nq;//�ֳ�������
				while(p&&c[p].go[w]==q)//�ı��������� 
					c[p].go[w]=nq,p=c[p].par;
			}
			last=now;
		}
	}
	void pre()
	{
		//��������Ϊ�˰�ÿ���㰴�������򣬳�����ͬ���Ⱥ������ 
		for(int i=1;i<=np;i++)v[c[i].val]++;
		for(int i=1;i<=n;i++)v[i]+=v[i-1];
		for(int i=np;i>=1;i--)wh[v[c[i].val]--]=i;
		
		//ww������right���ϵĴ�С
		ww[1]=0;
		for(int i=np;i>=2;i--)
		{
			int t=wh[i];
			if(T==1)ww[c[t].par]+=ww[t];
			else ww[t]=1;
		}
		ww[1]=0;
		
		//vis�ǵ�ǰ�ڵ��·���� 
		for(int i=np;i>=1;i--)
		{
			int t=wh[i];vis[t]=ww[t];
			for(int ii=0;ii<26;ii++)
				if(c[t].go[ii])vis[t]+=vis[c[t].go[ii]];
		}
	}
	void dfs(int now,int k)//�ݹ���𰸡� 
	{
		if(k<=ww[now])return;
		k-=ww[now];
		for(int i=0;i<26;i++)
		{
			if(c[now].go[i])
			{
				if(k<=vis[c[now].go[i]])
				{
					putchar(i+'a');
					dfs(c[now].go[i],k);
					return;
				}
				k-=vis[c[now].go[i]];
			}
		}
	}
}sam;
char s[500005];
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	gets(s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
		sam.extend(s[i]-'a');
	int k;
	scanf("%d%d",&T,&k);
	sam.pre();
	if(k>sam.vis[1])printf("-1\n");
	else sam.dfs(sam.rt,k),putchar('\n');
	return 0;
}

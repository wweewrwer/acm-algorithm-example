#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxn=15;
const int maxm=50005;
using namespace std;

struct edge
{
	int to;
	int next;
}e[maxm];
int n,m,first[99993],hashnum=99991,np=0,inqf[99993];
int state[2][maxm],cur,tot[2],cb[15][15],lastv=0;
long long vis[2][maxm];
char s[15];
void ins(int now,long long d,int i)
{
	int k=now%hashnum;
	if(inqf[k]!=i)first[k]=0;
	for(int p=first[k];p!=0;p=e[p].next)
	{
		int j=e[p].to;
		if(state[cur][j]==now)
		{
			vis[cur][j]+=d;
			return;
		}
	}
	state[cur][++tot[cur]]=now;
	vis[cur][tot[cur]]=d;
	e[++np]=(edge){tot[cur],first[k]};
	first[k]=np;
	inqf[k]=i;
}
void dp()
{
	ins(0,1,0);
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		for(int ii=1;ii<=m;ii++)
		{
			cur=cur^1;
			tot[cur]=0;
			np=0;
			for(int i3=1;i3<=tot[cur^1];i3++)
			{
				int now=state[cur^1][i3];
				long long v=vis[cur^1][i3];
				int isup=(now>>(m*2));
				int isleft=now%4;
				if(!cb[i][ii])
				{
					now=now-isleft-(isup<<(m*2));
					now=(now<<2);
					ins(now,v,(i-1)*m+ii);
					continue;
				}
				if(!isup&&!isleft)//new
				{
					int now2=((now+1)<<2)+2;
					if(cb[i][ii+1]&&cb[i+1][ii])ins(now2,v,(i-1)*m+ii);
				}
				else if(!isup&&isleft)//
				{
					int now2=(now-isleft)<<2;
					if(cb[i][ii+1])ins(now2+isleft,v,(i-1)*m+ii);//continue left;
					if(cb[i+1][ii])ins(now2+(isleft<<2),v,(i-1)*m+ii);//left turn down;
				}
				else if(isup&&!isleft)
				{
					int now2=now-(isup<<(m*2));
					if(cb[i][ii+1])ins((now2<<2)+isup,v,(i-1)*m+ii);
					if(cb[i+1][ii])ins((now2+isup)<<2,v,(i-1)*m+ii);
				}
				else if(isup==1&&isleft==2)
				{
					int now2=(now-(isup<<(m*2))-isleft)<<2;
					ins(now2,v,(i-1)*m+ii);
				}
				else if(isup==2&&isleft==1)
				{
					int now2=(now-(isup<<(m*2))-isleft)<<2;
					if((i-1)*m+ii!=lastv)continue;
					ans+=v;
					ins(now2,v,(i-1)*m+ii);
				}
				else if(isup==1&&isleft==1)
				{
					int now2=(now-(isup<<(m*2))-isleft);
					int tmp=1;
					for(int i3=(m-1)*2;i3>=2;i3-=2)
					{
						if((now2>>i3)&2)tmp--;
						if((now2>>i3)&1)tmp++;
						if(tmp==0)
						{
							now2=(now2-(2<<i3)+(1<<i3));
							break;
						}
					}
					if(tmp==0)ins(now2<<2,v,(i-1)*m+ii);
				}
				else if(isup==2&&isleft==2)
				{
					int now2=(now-(isup<<(m*2))-isleft);
					int tmp=1;
					for(int i3=2;i3<=2*(m-1);i3+=2)
					{
						if((now2>>i3)&1)tmp--;
						if((now2>>i3)&2)tmp++;
						if(tmp==0)
						{
							now2=(now2-(1<<i3)+(2<<i3));
							break;
						}
					}
					if(tmp==0)ins(now2<<2,v,(i-1)*m+ii);
				}
			}
		}
	}
	cout<<ans<<'\n';
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		for(int ii=1;ii<=m;ii++)
		{
			if(s[ii]=='*')cb[i][ii]=0;
			else cb[i][ii]=1,lastv=(i-1)*m+ii;
		}
	}
	dp();
	return 0;
}

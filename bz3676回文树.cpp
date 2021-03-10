//回文树可以解决的问题：回文串的个数（本质不同的和位置不同的都可以），每个回文串的长度和等价的问题 
//每个回文串出现的次数，倘若要动态询问就需要lct来维护fail树，为了区间修改。 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
 
const int maxn=300005;
using namespace std;

struct mytree
{
	//每个点都至少代表一个回文。 
    int to[maxn][26],fail[maxn],val[maxn],len[maxn],s[maxn],np,n,last;
    int newnode(int r)
    {
        memset(to[np],0,sizeof(to[np]));
        //这里fail的含义是以该节点结束的回文（即fail下去的首先是它的后缀，然后是它的回文） 
        fail[np]=0;
        val[np]=0;//val表示的是出现的次数 
        len[np]=r;//len可以替换为其他可以求的。 
        return np++;
    }
    mytree()
    {
    	//首先初始化，建立两个起点，一个奇数回文起点，一个偶数回文起点 
        //其中为了方便奇数回文len为-1,偶数回文len为1，将s[0]设为-1，fail[0]设为1 
		np=0; n=0; last=0;
        memset(s,0,sizeof(s));
        newnode(0); newnode(-1);
        s[0]=-1; fail[0]=1;
    }
    int getfail(int x)
    {
    	//倘若构不成回文就持续fail 
        while(s[n-len[x]-1]!=s[n])x=fail[x];
        return x;
    }
    void insert(int x)
    {
        s[++n]=x;
        //找到当前的可以匹配的点，若一直找不到就会到奇数回文起点导致s[n]=s[n]即可。 
        int cur=getfail(last);
        if(!to[cur][x])
        {
        	//若没有走到该边的 
            int p=newnode(len[cur]+2);
            //找到它失配后到达的位置 
            fail[p]=to[getfail(fail[cur])][x];
            to[cur][x]=p;//连上。 
        }
        last=to[cur][x];
        val[last]++;//更新val值，当当前回文出现时意味着它的fail回文均出现过，每次更新的是它的最长回文 
    }
    long long dp()
    {
        long long ans=0;
        for(int i=np-1;i>=0;i--)val[fail[i]]+=val[i];//累加上去 
        for(int i=0;i<np;i++)ans=max(ans,(long long)val[i]*len[i]);
        return ans;
    }
}c;
int n;
char s[maxn];
int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;i++)
    {
        c.insert(s[i]-'a');
    }
    cout<<c.dp()<<'\n';
    return 0;
}

//���������Խ�������⣺���Ĵ��ĸ��������ʲ�ͬ�ĺ�λ�ò�ͬ�Ķ����ԣ���ÿ�����Ĵ��ĳ��Ⱥ͵ȼ۵����� 
//ÿ�����Ĵ����ֵĴ���������Ҫ��̬ѯ�ʾ���Ҫlct��ά��fail����Ϊ�������޸ġ� 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
 
const int maxn=300005;
using namespace std;

struct mytree
{
	//ÿ���㶼���ٴ���һ�����ġ� 
    int to[maxn][26],fail[maxn],val[maxn],len[maxn],s[maxn],np,n,last;
    int newnode(int r)
    {
        memset(to[np],0,sizeof(to[np]));
        //����fail�ĺ������Ըýڵ�����Ļ��ģ���fail��ȥ�����������ĺ�׺��Ȼ�������Ļ��ģ� 
        fail[np]=0;
        val[np]=0;//val��ʾ���ǳ��ֵĴ��� 
        len[np]=r;//len�����滻Ϊ����������ġ� 
        return np++;
    }
    mytree()
    {
    	//���ȳ�ʼ��������������㣬һ������������㣬һ��ż��������� 
        //����Ϊ�˷�����������lenΪ-1,ż������lenΪ1����s[0]��Ϊ-1��fail[0]��Ϊ1 
		np=0; n=0; last=0;
        memset(s,0,sizeof(s));
        newnode(0); newnode(-1);
        s[0]=-1; fail[0]=1;
    }
    int getfail(int x)
    {
    	//���������ɻ��ľͳ���fail 
        while(s[n-len[x]-1]!=s[n])x=fail[x];
        return x;
    }
    void insert(int x)
    {
        s[++n]=x;
        //�ҵ���ǰ�Ŀ���ƥ��ĵ㣬��һֱ�Ҳ����ͻᵽ����������㵼��s[n]=s[n]���ɡ� 
        int cur=getfail(last);
        if(!to[cur][x])
        {
        	//��û���ߵ��ñߵ� 
            int p=newnode(len[cur]+2);
            //�ҵ���ʧ��󵽴��λ�� 
            fail[p]=to[getfail(fail[cur])][x];
            to[cur][x]=p;//���ϡ� 
        }
        last=to[cur][x];
        val[last]++;//����valֵ������ǰ���ĳ���ʱ��ζ������fail���ľ����ֹ���ÿ�θ��µ������������ 
    }
    long long dp()
    {
        long long ans=0;
        for(int i=np-1;i>=0;i--)val[fail[i]]+=val[i];//�ۼ���ȥ 
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

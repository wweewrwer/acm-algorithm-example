long long qkpow(long long x,int t,long long mod)
{
    if(t<0)return qkpow(qkpow(x,mod-2,mod),-t,mod);
    long long w=1;
    while(t)
    {
        if(t&1)
        {
            w=(w*x)%mod;
        }
        x=(x*x)%mod;
        t=(t>>1);
    }
    return w;
}
long long getg(int n)//求原根g，g^k mod modnum 的值域为[modnum-1,1],定义域为[1,modnum-1] 
{
    int tmp=0;
    int x=n-1;
    for(int i=2;x!=1;i++)
    {
        if(x%i==0)a[++tmp]=i;
        while(x%i==0)x=x/i;
    }
    for(int i=2;;i++)
    {
        int isok=1;
        for(int ii=1;ii<=tmp;ii++)
        {
            long long anum=qkpow(i,(n-1)/a[ii],n);
            if(anum==1)
            {
                isok=0;
                break;
            }
        }
        if(isok)return i;
    }
}
void ntt(long long *c,int f)
{
    for(int i=0;i<n;i++)if(i<r[i])swap(c[i],c[r[i]]);
     
    for(int i=1;i<n;i=(i<<1))
    {
        long long wn=qkpow(3,f*(modnum-1)/(i<<1),modnum),x,y;//3为modnum的原根 
        for(int ii=0;ii<n;ii+=(i<<1))
        {
            long long w=1;
            for(int i3=0;i3<i;i3++,w=w*wn%modnum)
            {
                x=c[ii+i3],y=w*c[i+ii+i3]%modnum;
                c[ii+i3]=(x+y)%modnum;
                c[i+ii+i3]=(x-y+modnum)%modnum;
            }
        }
    }
}


scanf("%d",&n);	//a,b为目标数组,下面不变即可。 
_scanf(t1,n);
_scanf(t2,n);
m=n*2;
for(n=1;n<m;n=(n<<1))l++;
for(int i=0;i<n;i++)r[i]=((r[i>>1]>>1)|((i&1)<<(l-1)));
ntt(t1,1);
ntt(t2,1);
for(int i=0;i<n;i++)c[i]=t1[i]*t2[i]%modnum;
ntt(c,-1);
nt=qkpow(n,modnum-2,modnum);
for(int i=0;i<n;i++)c[i]=c[i]*nt%modnum;
//此时c便为新函数的值。 

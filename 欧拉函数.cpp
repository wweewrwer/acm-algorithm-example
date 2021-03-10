long long eular(long long n)
{
    long long ans = n;
    for(int i = 2; i*i <= n; i++)
    {
        if(n % i == 0)
        {
            ans -= ans/i; //等价于通项，把n乘进去
            while(n % i == 0) //确保下一个i是n的素因数
                n /= i;
        }
    }
    if(n > 1)ans -= ans/n; //最后可能还剩下一个素因数没有除
    return ans;
}

//打表求欧拉 
void euler()  
{  
	phi[1]=1;
    for(int i=2;i<maxn;i++){  
        if(!phi[i])  
        for(int j=i;j<maxn;j+=i){  
            if(!phi[j]) phi[j]=j;  
            phi[j]=phi[j]/i*(i-1);  
        }  
    }  
}

    //方法3： 欧拉筛素数同时求欧拉函数

    void get_phi()  
    {  
    	phi[1]=1;
        int i, j, k;  
        k = 0;  
        for(i = 2; i < maxn; i++)  
        {  
            if(is_prime[i] == false)  
            {  
                prime[k++] = i;  
                phi[i] = i-1;  
            }  
            for(j = 0; j<k && i*prime[j]<maxn; j++)  
            {  
                is_prime[ i*prime[j] ] = true;  
                if(i%prime[j] == 0)  
                {  
                    phi[ i*prime[j] ] = phi[i] * prime[j];  
                    break;  
                }  
                else  
                {  
                    phi[ i*prime[j] ] = phi[i] * (prime[j]-1);  
                }  
            }  
        }  
    }  


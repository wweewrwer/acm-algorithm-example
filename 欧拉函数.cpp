long long eular(long long n)
{
    long long ans = n;
    for(int i = 2; i*i <= n; i++)
    {
        if(n % i == 0)
        {
            ans -= ans/i; //�ȼ���ͨ���n�˽�ȥ
            while(n % i == 0) //ȷ����һ��i��n��������
                n /= i;
        }
    }
    if(n > 1)ans -= ans/n; //�����ܻ�ʣ��һ��������û�г�
    return ans;
}

//�����ŷ�� 
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

    //����3�� ŷ��ɸ����ͬʱ��ŷ������

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


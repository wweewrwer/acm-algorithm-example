#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue> 
#include<vector>
#include<string>

const int maxn=515;
const int readLen=1024;
using namespace std;

//����������һ���ڵ� 
struct btNode
{
	int lc,rc;
	int fa;
	int w;
};
//�������� 
struct huffmanTree
{
	int n;
	int rt;
	btNode node[maxn];
	string table[maxn];
};
//���Բ�����������ʱ�����ȶ��� 
struct cmp
{
	int id;
	int w;
	friend bool operator<(cmp one,cmp two)
	{
		return one.w>two.w;
	}
};
//�����½ڵ� 
void newNode(huffmanTree *T,int lc,int rc,int w,int np);
//�ϲ�
void mergeTree(huffmanTree *T,int tree1,int tree2,int np);
//���ɹ������� 
void crtTree(huffmanTree *T);
//���ɱ���� 
void crtEncoderTable(huffmanTree *T);
//�������� 
void inputData(huffmanTree *T,char *fileNameIn);
//���Ա�������е���� 
void pushBit(FILE *fptr,unsigned char w,unsigned char &ch,int &offset);
//�ڱ����ļ��д洢�����
void writeTable(FILE *fptr,huffmanTree *T); 
//���� 
void encoder(huffmanTree *T,char *fileNameIn,char *fileNameOut);
//��������н������������������
void readTable(FILE *fptr,huffmanTree *T); 
//���� 
void decoder(huffmanTree *T,char *fileNameIn,char *fileNameOut);

int main()
{
	int flag;
	char fileNameIn[55];
	char fileNameOut[55];
	huffmanTree T;
	
	printf("������1��ʾ��ѹ��������0��ʾ����ѹ\n");
	scanf("%d",&flag);
	printf("������������ļ�����������׺�������뱣֤���ļ���ó�����ͬһ���ļ����У���\n");
	scanf("%s",fileNameIn);
	printf("������������ļ�����������׺������\n");
	scanf("%s",fileNameOut);
	if(flag==1)
	{
		inputData(&T,fileNameIn);
		crtTree(&T);
		crtEncoderTable(&T);
		encoder(&T,fileNameIn,fileNameOut);
	}
	else
	{
		decoder(&T,fileNameIn,fileNameOut);
	}
	printf("��ѹ����ɣ�\n");
	return 0;
}

void newNode(huffmanTree *T,int lc,int rc,int w,int np)
{
	T->node[np]=(btNode){lc,rc,-1,w};
}

void mergeTree(huffmanTree *T,int tree1,int tree2,int np)
{
	newNode(T,tree1,tree2,T->node[tree1].w+T->node[tree2].w,np);
	T->node[tree1].fa=np;
	T->node[tree2].fa=np;
}

void crtTree(huffmanTree *T)
{
	int n = T->n;
	priority_queue<cmp>q;
	for(int i=0;i<n;i++)
	{
		q.push((cmp){i,T->node[i].w});
	}
	for(int i=n;i<2*n-1;i++)
	{
		//ѡ��Ȩֵ��С�Ľ��кϲ� 
		int tree1=q.top().id; q.pop();
		int tree2=q.top().id; q.pop();
		mergeTree(T, tree1, tree2, i);
		q.push((cmp){i,T->node[i].w});
	}
	T->rt = 2*n-2;
}
void crtEncoderTable(huffmanTree *T)
{
	queue<int>q;
	q.push(T->rt);
	while(!q.empty())
	{
		int np = q.front(); q.pop();
		int lc = T->node[np].lc;
		int rc = T->node[np].rc;
		if(lc!=-1){T->table[lc] = T->table[np]+"0";q.push(lc);}
		if(rc!=-1){T->table[rc] = T->table[np]+"1";q.push(rc);}
	}
}
void inputData(huffmanTree *T,char *fileNameIn)
{
	FILE *fptr = fopen(fileNameIn,"rb");
	unsigned char s[readLen];
	T->n = 256;
	//������ʼ��Ҷ�ӽڵ� 
	for(int i=0;i<256;i++)
	{
		newNode(T, -1, -1, 0, i);
	}
	while(!feof(fptr))
	{
		//ͳ�Ƴ��ִ��� 
		int size = fread(s,sizeof(unsigned char),readLen,fptr);
		for(int i=0;i<size;i++)
			T->node[s[i]].w++;
	}
	fclose(fptr);
}
void pushBit(FILE *fptr,unsigned char w,unsigned char &ch,int &offset)
{
	ch = (ch<<1)+w;
	offset++;
	//���������ִﵽ8λʱ�����һ���ֽ� 
	if(offset==8)
	{
		offset=0;
		fwrite(&ch,sizeof(unsigned char),1,fptr);
		ch=0;
	}
}
void writeTable(FILE *fptr,huffmanTree *T)
{
	for(int i = 0;i < 256;i++)
	{
		fwrite(&T->node[i].w,sizeof(int),1,fptr);
	}
}
void encoder(huffmanTree *T,char *fileNameIn,char *fileNameOut)
{
	FILE *fptrIn = fopen(fileNameIn,"rb");
	FILE *fptrOut = fopen(fileNameOut,"wb");
	int offset = 0;
	int sLen;
	unsigned char ch;
	unsigned char chOut = 0;
	//���һ���������ֽ�ռλ����������������������һ�ֽ���Чλ�� 
	fwrite(&chOut,sizeof(unsigned char),1,fptrOut);
	//��ԭ�ļ�ÿ���ַ��ĳ��ִ�������ѹ���ļ��У����Խ�����̽���
	writeTable(fptrOut, T); 
	while(fread(&ch,sizeof(unsigned char),1,fptrIn))
	{
		sLen = T->table[ch].size();
		for(int i = 0; i < sLen; i++)
		{
			if(T->table[ch][i]=='1')
				pushBit(fptrOut,1,chOut,offset);
			else
				pushBit(fptrOut,0,chOut,offset);
		}
	}
	//�����ʣ�µ��ֲ���Ϊһ���ֽ� 
	for(int i=0;i<8-offset;i++)
		chOut<<=1;
	fwrite(&chOut,sizeof(unsigned char),1,fptrOut);
	//�����һ���ֽ���Чλ��������ļ��� 
	rewind(fptrOut);
	chOut=offset;
	fwrite(&chOut,sizeof(unsigned char),1,fptrOut);
	fclose(fptrIn);
	fclose(fptrOut);
}
void readTable(FILE *fptr,huffmanTree *T)
{
	int w;
	T->n=256;
	for(int i=0;i<256;i++)
	{
		fread(&w,sizeof(int),1,fptr);
		newNode(T,-1,-1,w,i);
	}
	crtTree(T);
}
void decoder(huffmanTree *T,char *fileNameIn,char *fileNameOut)
{
	FILE *fptrIn = fopen(fileNameIn,"rb");
	FILE *fptrOut = fopen(fileNameOut,"wb");
	 
	unsigned char lastLen;//��ʾ���һ�ֽ���Чλ�� 
	unsigned char ch,chOut,lastch;
	fread(&lastLen,sizeof(unsigned char),1,fptrIn);
	
	//���������������Խ��� 
	readTable(fptrIn, T);
	int nowNode = T -> rt;
	fread(&lastch,sizeof(unsigned char),1,fptrIn);
	while(!feof(fptrIn))
	{
		ch=lastch;
		fread(&lastch,sizeof(unsigned char),1,fptrIn);
		//����������һ�ֽ�ʱ��������ܶ�����Чλ���� 
		for(int i = 7; i >= 0 && ((!feof(fptrIn))||i >= 8-lastLen); i--)
		{
			if((ch>>i)&1)
				nowNode = T->node[nowNode].rc;
			else
				nowNode = T->node[nowNode].lc;
			//����Ҷ�ӽڵ㣬��� 
			if(nowNode<T->n)
			{
				chOut = (unsigned char)nowNode;
				fwrite(&chOut,sizeof(unsigned char),1,fptrOut);
				nowNode = T -> rt;
			}
		}
	}
	fclose(fptrIn);
	fclose(fptrOut);
}

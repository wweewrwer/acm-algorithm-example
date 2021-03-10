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

//哈夫曼树的一个节点 
struct btNode
{
	int lc,rc;
	int fa;
	int w;
};
//哈夫曼树 
struct huffmanTree
{
	int n;
	int rt;
	btNode node[maxn];
	string table[maxn];
};
//用以产生哈夫曼树时的优先队列 
struct cmp
{
	int id;
	int w;
	friend bool operator<(cmp one,cmp two)
	{
		return one.w>two.w;
	}
};
//产生新节点 
void newNode(huffmanTree *T,int lc,int rc,int w,int np);
//合并
void mergeTree(huffmanTree *T,int tree1,int tree2,int np);
//生成哈夫曼树 
void crtTree(huffmanTree *T);
//生成编码表 
void crtEncoderTable(huffmanTree *T);
//输入数据 
void inputData(huffmanTree *T,char *fileNameIn);
//用以编码过程中的输出 
void pushBit(FILE *fptr,unsigned char w,unsigned char &ch,int &offset);
//在编码文件中存储编码表
void writeTable(FILE *fptr,huffmanTree *T); 
//编码 
void encoder(huffmanTree *T,char *fileNameIn,char *fileNameOut);
//解码过程中建立哈夫曼树用以输出
void readTable(FILE *fptr,huffmanTree *T); 
//解码 
void decoder(huffmanTree *T,char *fileNameIn,char *fileNameOut);

int main()
{
	int flag;
	char fileNameIn[55];
	char fileNameOut[55];
	huffmanTree T;
	
	printf("请输入1表示将压缩，输入0表示将解压\n");
	scanf("%d",&flag);
	printf("请输入输入的文件名（包括后缀名）（请保证该文件与该程序在同一个文件夹中）：\n");
	scanf("%s",fileNameIn);
	printf("请输入输出的文件名（包括后缀名）：\n");
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
	printf("解压缩完成！\n");
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
		//选出权值最小的进行合并 
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
	//产生初始的叶子节点 
	for(int i=0;i<256;i++)
	{
		newNode(T, -1, -1, 0, i);
	}
	while(!feof(fptr))
	{
		//统计出现次数 
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
	//当产生的字达到8位时，输出一个字节 
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
	//输出一个无意义字节占位，用以最后输出编码过后最后一字节有效位数 
	fwrite(&chOut,sizeof(unsigned char),1,fptrOut);
	//将原文件每个字符的出现次数存入压缩文件中，用以解码过程建树
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
	//将最后剩下的字补足为一个字节 
	for(int i=0;i<8-offset;i++)
		chOut<<=1;
	fwrite(&chOut,sizeof(unsigned char),1,fptrOut);
	//将最后一个字节有效位数输出在文件首 
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
	 
	unsigned char lastLen;//表示最后一字节有效位数 
	unsigned char ch,chOut,lastch;
	fread(&lastLen,sizeof(unsigned char),1,fptrIn);
	
	//建立哈夫曼树用以解码 
	readTable(fptrIn, T);
	int nowNode = T -> rt;
	fread(&lastch,sizeof(unsigned char),1,fptrIn);
	while(!feof(fptrIn))
	{
		ch=lastch;
		fread(&lastch,sizeof(unsigned char),1,fptrIn);
		//当如果是最后一字节时，输出不能多于有效位数数 
		for(int i = 7; i >= 0 && ((!feof(fptrIn))||i >= 8-lastLen); i--)
		{
			if((ch>>i)&1)
				nowNode = T->node[nowNode].rc;
			else
				nowNode = T->node[nowNode].lc;
			//到达叶子节点，输出 
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

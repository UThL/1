#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100

typedef struct TNode{
	char data;
	struct TNode *lchild;
	struct TNode *rchild;
}*BinTree;

typedef struct QNode{
	struct TNode *data[MAXSIZE];
	int front;
	int rear;
}*Queue;

Queue CreatQ()//����һ���ն��� 
{
	Queue Q=(struct QNode*)malloc(sizeof(struct QNode));
	Q->front=0;
	Q->rear=0;
	return Q;
}
int IsEmpty(Queue q)//�ж϶����Ƿ�Ϊ��
{
	return(q->front==q->rear);
}
void AddQ(Queue q,BinTree T)//��t��� 
{
	if((q->rear+1)%MAXSIZE==q->front){
		printf("OVERFLOW!");
	}
	q->rear=(q->rear+1)%MAXSIZE;//ѭ������ 
	q->data[q->rear]=T;//T�ĵ�ַ��������� 
}

BinTree DeleteQ(Queue q){//���ӣ������ض�ͷ
	struct TNode *T;
	q->front=(q->front+1)%MAXSIZE;//ѭ������ 
	T=q->data[q->front];//����ͷ�ĵ�ַ��ֵ��T 
	return T;
}
BinTree CreatBintree()//�����˳�򴴽�һ�ö������������ظ��ڵ�
{
	char data;
	struct TNode *BT,*T;
	struct QNode *Q;
	Q=CreatQ();
	scanf("%c",&data);//������ڵ� 
	getchar();//ȥ�س�
	if(data!='#')
	{
		BT=(struct TNode*)malloc(sizeof(struct TNode));
		BT->data=data;
		BT->lchild=BT->rchild=NULL;
		AddQ(Q,BT);
	}
	else return NULL;
	while(!IsEmpty(Q)){
		T=DeleteQ(Q);//����һ������ �����ҷ��ض�ͷ��������һ���Ķ����ǵǳ��������� 
		scanf("%c",&data);//�����
		getchar();
		if(data=='#') T->lchild=NULL;//��ʾû����� 
		else{
			T->lchild=(struct TNode*)malloc(sizeof(struct TNode));
			T->lchild->data=data;//����Ӹ�ֵ 
			T->lchild->lchild=T->lchild->rchild=NULL;//�����Ӻ�������Ϊ�� 
			AddQ(Q,T->lchild);//�������� 
		}
		scanf("%c",&data);//�Ҷ��� 
		getchar();
		if(data=='#') T->rchild=NULL;//��ʾû�Ҷ��� 
		else{
			T->rchild=(struct TNode*)malloc(sizeof(struct TNode));
			T->rchild->data=data;
			T->rchild->lchild=T->rchild->rchild=NULL;//�����Ӻ�������Ϊ�� 
			AddQ(Q,T->rchild);//�Ҷ������ 
		}
	}
	return BT;
}

void Preorder(BinTree T) { //������� 
 if(T == NULL)
 return; 
 else {
  printf("%c ",T->data);
  Preorder(T->lchild);
  Preorder(T->rchild);
 }
}

int TreeDeep(BinTree T) {
 int deep=0;
 if(T)
 {
  int leftdeep = TreeDeep(T->lchild);
  int rightdeep = TreeDeep(T->rchild);
  deep = leftdeep+1 > rightdeep+1 ? leftdeep+1 : rightdeep+1; 
 }
 return deep;
}
 
int Leafcount(BinTree T, int &num) {
 if(T)
 {
  if(T->lchild ==NULL && T->rchild==NULL) 
  {
   num++;
   printf("%c ",T->data);
  }   
  Leafcount(T->lchild,num);
  Leafcount(T->rchild,num);
 
 }
 return num;
}

int main(void)
{
 BinTree T;
 BinTree *p = (BinTree*)malloc(sizeof(BinTree));
 int deepth,num=0 ;
 BinTree CreatBintree(&T);
 printf("�������������:\n");
 deepth=TreeDeep(T);
 printf("�������Ϊ:%d",deepth);
 printf("\n");
 printf("����Ҷ�ӽ��Ϊ:");
 Leafcount(T,num);
 printf("\\n����Ҷ�ӽ�����Ϊ:%d",num);
 return 0;
}

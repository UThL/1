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

Queue CreatQ()//创建一个空队列 
{
	Queue Q=(struct QNode*)malloc(sizeof(struct QNode));
	Q->front=0;
	Q->rear=0;
	return Q;
}
int IsEmpty(Queue q)//判断队列是否为空
{
	return(q->front==q->rear);
}
void AddQ(Queue q,BinTree T)//将t入队 
{
	if((q->rear+1)%MAXSIZE==q->front){
		printf("OVERFLOW!");
	}
	q->rear=(q->rear+1)%MAXSIZE;//循环队列 
	q->data[q->rear]=T;//T的地址存入队列中 
}

BinTree DeleteQ(Queue q){//出队，并返回队头
	struct TNode *T;
	q->front=(q->front+1)%MAXSIZE;//循环队列 
	T=q->data[q->front];//队列头的地址赋值给T 
	return T;
}
BinTree CreatBintree()//按层次顺序创建一棵二叉树，并返回根节点
{
	char data;
	struct TNode *BT,*T;
	struct QNode *Q;
	Q=CreatQ();
	scanf("%c",&data);//造个根节点 
	getchar();//去回车
	if(data!='#')
	{
		BT=(struct TNode*)malloc(sizeof(struct TNode));
		BT->data=data;
		BT->lchild=BT->rchild=NULL;
		AddQ(Q,BT);
	}
	else return NULL;
	while(!IsEmpty(Q)){
		T=DeleteQ(Q);//把上一个出队 ，并且返回队头，就是上一个的儿子们登场，依次推 
		scanf("%c",&data);//左儿子
		getchar();
		if(data=='#') T->lchild=NULL;//表示没左儿子 
		else{
			T->lchild=(struct TNode*)malloc(sizeof(struct TNode));
			T->lchild->data=data;//左儿子赋值 
			T->lchild->lchild=T->lchild->rchild=NULL;//左孙子和右孙子为空 
			AddQ(Q,T->lchild);//左儿子入队 
		}
		scanf("%c",&data);//右儿子 
		getchar();
		if(data=='#') T->rchild=NULL;//表示没右二子 
		else{
			T->rchild=(struct TNode*)malloc(sizeof(struct TNode));
			T->rchild->data=data;
			T->rchild->lchild=T->rchild->rchild=NULL;//左孙子和右孙子为空 
			AddQ(Q,T->rchild);//右儿子入队 
		}
	}
	return BT;
}

void Preorder(BinTree T) { //先序遍历 
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
 printf("先序遍历二叉树:\n");
 deepth=TreeDeep(T);
 printf("树的深度为:%d",deepth);
 printf("\n");
 printf("树的叶子结点为:");
 Leafcount(T,num);
 printf("\\n树的叶子结点个数为:%d",num);
 return 0;
}

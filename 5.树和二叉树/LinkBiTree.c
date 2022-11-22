#include <stdio.h>
#include <stdlib.h>

//函数结果状态代码
#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define INFEASIBLE -1 // infeasible
#define OVERFLOW   -2
#define MAXSIZE    100

//Status是函数的类型，其值是函数结果状态代码
typedef int Status;

//树结点中的元素
typedef struct {
	int n;
	char ch;
} TElemType;

//双叉链表
typedef struct biTree {
	TElemType data;
	struct biTree *lchild, *rchild;		//左孩子右孩子指针
} BiTNode, *BiTree;

//三叉链表
typedef struct triTree {
	TElemType data;
	struct triTree *lchild, *rchild, *parent;		//左孩子右孩子指针 双亲指针
} TriTNode, *TriTree;

//顺序栈 非递归遍历
typedef struct {
	BiTNode *top;
	BiTNode *base;
	int stackSize;
} SqStack;

//顺序队列 层次遍历
typedef struct {
	BiTree base[MAXSIZE];
	int front, rear;
} SqQueue;

Status CreateBiTree(BiTNode *T);
BiTree createBiTree();				//建立二叉树(先序)
BiTree copyBiTree(BiTree T, BiTree newT); 	//复制二叉树
Status levelOrder(BiTree T);		//层次遍历
Status orderTraverse(BiTree T);     //非递归中序遍历
Status preOrderTraverse(BiTree T);	//递归前序遍历
Status inOrderTraverse(BiTree T);	//递归中序遍历
Status postOrderTraverse(BiTree T); //递归后序遍历
int depth(BiTree T);				//求二叉树深度
int countNode(BiTree T);			//计算二叉树结点总数
int leafNode(BiTree T);				//计算二叉树叶子结点

Status initStack(SqStack *S);
Status stackEmpty(SqStack S);
Status pushStack(SqStack *S, BiTree data);
BiTree popStack(SqStack *S);

Status initQueue(SqQueue *Q);
Status queueEmpty(SqQueue Q);
Status enQueue(SqQueue *Q, BiTree data);
BiTree deQueue(SqQueue *Q);


//int main() {
////	BiTNode t;
////	BiTNode *T = &t;
////	createBiTree(T);
////	printf("T=%p\n", T);
//	BiTree t = NULL, T = NULL;
//	t = createBiTree();
//	T = copyBiTree(t, T);
//	printf("depth = %d\n", depth(T));
//	printf("leafNode = %d\n", leafNode(T));
//	printf("countNode = %d\n", countNode(T));
////	printf("层次遍历\n");
////	levelOrder(T);
////	printf("\n");
////	printf("非递归中序遍历\n");
////	orderTraverse(T);
////	printf("\n");
////	printf("前序遍历\n");
////	preOrderTraverse(T);
////	printf("\n");
////	printf("中序遍历\n");
////	inOrderTraverse(T);
////	printf("\n");
////	printf("后序遍历\n");
////	postOrderTraverse(T);
////	printf("\n");
//	return 0;
//}

//计算二叉树叶子结点
int leafNode(BiTree T) {
	int l, r;
	if (T == NULL) {
		return 0;
	}
	if (T->lchild == NULL && T->rchild == NULL) {
		return 1;					//如果左右子树都为空则返回1
	} else {
		l = leafNode(T->lchild);	//计算左子树叶子结点总数
		r = leafNode(T->rchild);	//计算右子树叶子结点总数
		return (l + r);				//返回左子树+右子树
	}
}

//计算二叉树结点总数
int countNode(BiTree T) {
	int l, r;
	if (T == NULL) {
		return 0;
	} else {
		l = countNode(T->lchild);	//计算左子树结点总数
		r = countNode(T->rchild);	//计算右子树结点总数
		return (l + r + 1);			//返回左子树+右子树+1
	}
}

//求树的深度
int depth(BiTree T) {
	int l, r;
	if (T == NULL) {
		return 0;
	} else {
		l = depth(T->lchild);	//求左子树的深度
		r = depth(T->rchild);	//求右子树的深度
		if (l > r) {
			return (l + 1);
		} else {
			return (r + 1);
		}
	}
}

//建立二叉树(先序)
BiTree createBiTree() {
	BiTree T;
	int n;
	printf("请输入:");
	scanf("%d", &n);
	if (n == 0) {
		T = NULL;
	} else {
		T = (BiTNode *)malloc(sizeof(BiTNode));
		T->data.n = n;
		T->lchild = createBiTree();
		T->rchild = createBiTree();
	}
	return T;
}

//复制二叉树
BiTree copyBiTree(BiTree T, BiTree newT) {
	if (T == NULL) {
		newT = NULL;
	} else {
		newT = (BiTNode *)malloc(sizeof(BiTNode));
		newT->data = T->data;
		newT->lchild = copyBiTree(T->lchild, newT->lchild);
		newT->rchild = copyBiTree(T->rchild, newT->rchild);
	}
}

//层次遍历
Status levelOrder(BiTree T) {
	BiTree p = NULL;
	SqQueue q;
	initQueue(&q);
	enQueue(&q, T);
	while (!queueEmpty(q)) {
		p = deQueue(&q);
		printf("%d", p->data.n);
		if (p->lchild) {
			enQueue(&q, p->lchild);
		}
		if (p->rchild) {
			enQueue(&q, p->rchild);
		}
	}
	return OK;
}

//非递归中序遍历
Status orderTraverse(BiTree T) {
	//构造一个栈存放结点
	SqStack S;
	initStack(&S);
	BiTree p = T, q = NULL;
	while (p || !stackEmpty(S)) {
		if (p) {
			pushStack(&S, p);
			p = p->lchild;
		} else {
			q = popStack(&S);
			printf("%d", q->data.n);
			p = q->rchild;
		}
	}
	return OK;
}

//递归遍历
Status preOrderTraverse(BiTree T) {
	if (T == NULL) {
		return OK;
	} else {
		printf("%d", T->data.n);
		preOrderTraverse(T->lchild);
		preOrderTraverse(T->rchild);
	}
}

Status inOrderTraverse(BiTree T) {
	if (T == NULL) {
		return OK;
	} else {
		inOrderTraverse(T->lchild);
		printf("%d", T->data.n);
		inOrderTraverse(T->rchild);
	}
}

Status postOrderTraverse(BiTree T) {
	if (T == NULL) {
		return OK;
	} else {
		postOrderTraverse(T->lchild);
		postOrderTraverse(T->rchild);
		printf("%d", T->data.n);
	}
}

Status initStack(SqStack *S) {
	//初始化分配空间
	S->base = (BiTNode *)malloc(sizeof(BiTNode) * MAXSIZE);
	if (!S->base)
		exit(OVERFLOW);
	S->top = S->base;
	S->stackSize = MAXSIZE;
	return OK;
}

Status stackEmpty(SqStack S) {
	if (S.top == S.base) {
		return TRUE;
	} else {
		return FALSE;
	}
}

Status pushStack(SqStack *S, BiTree data) {
	if (S->top - S->base == S->stackSize) {
		return ERROR;
	}
	//*S->top = e, S->top++
	*(S->top++) = *data;
	return OK;
}

BiTree popStack(SqStack *S) {
	if (S->top - S->base == 0) {
		return ERROR;
	}
	--S->top;
	return S->top;
	//void类型传进去指针但指针的值没有修改？队列也是一样
}

Status initQueue(SqQueue *Q) {
//	Q->base = (BiTNode *)malloc(sizeof(BiTNode));
	if (!Q->base) {
		exit(OVERFLOW);
	}
	//头尾指针为0 队列为空
	Q->front = Q->rear = 0;
	return OK;
}

Status queueEmpty(SqQueue Q) {
	if (Q.front == Q.rear) {
		return TRUE;
	} else {
		return FALSE;
	}
}

Status enQueue(SqQueue *Q, BiTree data) {
	if ((Q->rear + 1) % MAXSIZE == Q->front) {	//保留一个内存空间 方便判断队满
		exit(ERROR);
	}
	Q->base[Q->rear] = data;
	Q->rear = (Q->rear + 1) % MAXSIZE;
	return OK;
}

BiTree deQueue(SqQueue *Q) {
	BiTree T = NULL;
	if (Q->front == Q->rear) {
		exit(ERROR);
	}
	T = Q->base[Q->front];
	//头指针往前移一位
	Q->front = (Q->front + 1) % MAXSIZE;
	return T;
}

Status CreateBiTree(BiTNode *T) {
	//有问题
	printf("请输入结点数据元素");
	int n;
	scanf("%d", &n);
	if (n == 0) {
		T = NULL;		//输入 # 代表空结点
	} else {
		T = (BiTNode *)malloc(sizeof(BiTNode));
//		T->lchild = T->rchild = NULL;
		T->data.n = n;
		CreateBiTree(T->lchild);	//建立左子树结点
		CreateBiTree(T->rchild);	//建立右子树结点
	}
	return OK;
}
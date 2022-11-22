#include <stdio.h>
#include <stdlib.h>

//�������״̬����
#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define INFEASIBLE -1 // infeasible
#define OVERFLOW   -2
#define MAXSIZE    100

//Status�Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int Status;

//������е�Ԫ��
typedef struct {
	int n;
	char ch;
} TElemType;

//˫������
typedef struct biTree {
	TElemType data;
	struct biTree *lchild, *rchild;		//�����Һ���ָ��
} BiTNode, *BiTree;

//��������
typedef struct triTree {
	TElemType data;
	struct triTree *lchild, *rchild, *parent;		//�����Һ���ָ�� ˫��ָ��
} TriTNode, *TriTree;

//˳��ջ �ǵݹ����
typedef struct {
	BiTNode *top;
	BiTNode *base;
	int stackSize;
} SqStack;

//˳����� ��α���
typedef struct {
	BiTree base[MAXSIZE];
	int front, rear;
} SqQueue;

Status CreateBiTree(BiTNode *T);
BiTree createBiTree();				//����������(����)
BiTree copyBiTree(BiTree T, BiTree newT); 	//���ƶ�����
Status levelOrder(BiTree T);		//��α���
Status orderTraverse(BiTree T);     //�ǵݹ��������
Status preOrderTraverse(BiTree T);	//�ݹ�ǰ�����
Status inOrderTraverse(BiTree T);	//�ݹ��������
Status postOrderTraverse(BiTree T); //�ݹ�������
int depth(BiTree T);				//����������
int countNode(BiTree T);			//����������������
int leafNode(BiTree T);				//���������Ҷ�ӽ��

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
////	printf("��α���\n");
////	levelOrder(T);
////	printf("\n");
////	printf("�ǵݹ��������\n");
////	orderTraverse(T);
////	printf("\n");
////	printf("ǰ�����\n");
////	preOrderTraverse(T);
////	printf("\n");
////	printf("�������\n");
////	inOrderTraverse(T);
////	printf("\n");
////	printf("�������\n");
////	postOrderTraverse(T);
////	printf("\n");
//	return 0;
//}

//���������Ҷ�ӽ��
int leafNode(BiTree T) {
	int l, r;
	if (T == NULL) {
		return 0;
	}
	if (T->lchild == NULL && T->rchild == NULL) {
		return 1;					//�������������Ϊ���򷵻�1
	} else {
		l = leafNode(T->lchild);	//����������Ҷ�ӽ������
		r = leafNode(T->rchild);	//����������Ҷ�ӽ������
		return (l + r);				//����������+������
	}
}

//����������������
int countNode(BiTree T) {
	int l, r;
	if (T == NULL) {
		return 0;
	} else {
		l = countNode(T->lchild);	//�����������������
		r = countNode(T->rchild);	//�����������������
		return (l + r + 1);			//����������+������+1
	}
}

//���������
int depth(BiTree T) {
	int l, r;
	if (T == NULL) {
		return 0;
	} else {
		l = depth(T->lchild);	//�������������
		r = depth(T->rchild);	//�������������
		if (l > r) {
			return (l + 1);
		} else {
			return (r + 1);
		}
	}
}

//����������(����)
BiTree createBiTree() {
	BiTree T;
	int n;
	printf("������:");
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

//���ƶ�����
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

//��α���
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

//�ǵݹ��������
Status orderTraverse(BiTree T) {
	//����һ��ջ��Ž��
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

//�ݹ����
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
	//��ʼ������ռ�
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
	//void���ʹ���ȥָ�뵫ָ���ֵû���޸ģ�����Ҳ��һ��
}

Status initQueue(SqQueue *Q) {
//	Q->base = (BiTNode *)malloc(sizeof(BiTNode));
	if (!Q->base) {
		exit(OVERFLOW);
	}
	//ͷβָ��Ϊ0 ����Ϊ��
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
	if ((Q->rear + 1) % MAXSIZE == Q->front) {	//����һ���ڴ�ռ� �����ж϶���
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
	//ͷָ����ǰ��һλ
	Q->front = (Q->front + 1) % MAXSIZE;
	return T;
}

Status CreateBiTree(BiTNode *T) {
	//������
	printf("������������Ԫ��");
	int n;
	scanf("%d", &n);
	if (n == 0) {
		T = NULL;		//���� # ����ս��
	} else {
		T = (BiTNode *)malloc(sizeof(BiTNode));
//		T->lchild = T->rchild = NULL;
		T->data.n = n;
		CreateBiTree(T->lchild);	//�������������
		CreateBiTree(T->rchild);	//�������������
	}
	return OK;
}
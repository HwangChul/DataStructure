#include <stdio.h>
#include <stdlib.h>

//函数结果状态代码
#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define INFEASIBLE -1 // infeasible
#define OVERFLOW   -2

//Status是函数的类型，其值是函数结果状态代码
typedef int Status;

typedef struct {
	int n;
} QElemType;

typedef struct Qnode {
	QElemType data;
	struct Qnode *next;
} QNode, *QPtr;

typedef struct {
	QPtr front;//队头指针
	QPtr rear;//队尾指针
} LinkQueue;

Status initQueue(LinkQueue *Q);
Status destroyQueue(LinkQueue *Q);
Status enQueue(LinkQueue *Q, QElemType data);
Status deQueue(LinkQueue *Q, QElemType *data);

int main() {
	return 0;
}

Status deQueue(LinkQueue *Q, QElemType *data) {
	if (Q->front == Q->rear) {
		return ERROR;
	}
	QPtr p;
	//队头删除
	p = Q->front->next;
	*data = p->data;
	Q->front->next = p->next;
	if (Q->rear == p) {
		Q->rear = Q->front;
	}
	free(p);
	return OK;
}

Status enQueue(LinkQueue *Q, QElemType data) {
	//类似尾插法  后面进前面出 先进先出
	QPtr p;
	p = (QPtr)malloc(sizeof(QNode));
	p->data = data;
	p->next = NULL;
	//队尾插入
	Q->rear->next = p;
	Q->rear = p;
	return OK;
}

Status destroyQueue(LinkQueue *Q) {
	while (Q->front) {
		//用队尾指针当做临时指针
		Q->rear = Q->front;
		Q->front = Q->front->next;
		free(Q->rear);
	}
	return OK;
}

Status initQueue(LinkQueue *Q) {
	Q->front = Q->rear = (QPtr)malloc(sizeof(QNode));
	Q->front = NULL;
	return OK;
}




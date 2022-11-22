#include <stdio.h>
#include <stdlib.h>

#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW   -2
#define MAXQSIZE   20

typedef int Status;

typedef struct {
	int n;
	char ch;
} QElemType;

typedef struct sqQueue {
	QElemType *base;
	int front;
	int rear;
} SqQueue;

Status initQueue(SqQueue *Q);
int queueLen(SqQueue Q);
Status enQueue(SqQueue *Q, QElemType e);
Status deQueue(SqQueue *Q, QElemType *e);
Status queueEmpty(SqQueue Q);
Status destroySqQueue(SqQueue *Q);

int main() {
	SqQueue Q;
	initQueue(&Q);
	QElemType e;
	e.n = 1;
	enQueue(&Q, e);
	e.n = 2;
	enQueue(&Q, e);
	e.n = 3;
	enQueue(&Q, e);
	e.n = 4;
	enQueue(&Q, e);
	e.n = 5;
	enQueue(&Q, e);
	printf("f=%d\tr=%d\n", Q.front, Q.rear);
	deQueue(&Q, &e);
	for (int i = (Q.front % MAXQSIZE); i < 5; i++) {
		printf("%d\n", Q.base[i]);
	}
	printf("f=%d\tr=%d\n", Q.front, Q.rear);
	destroySqQueue(&Q);
	return 0;
}

Status destroySqQueue(SqQueue *Q) {
	if (Q->base) {
		free(Q->base);
	}
}

Status queueEmpty(SqQueue Q) {
	if (Q.front == Q.rear) {
		return TRUE;
	} else {
		return FALSE;
	}
}

Status deQueue(SqQueue *Q, QElemType *e) {
	if (Q->front == Q->rear) {
		exit(ERROR);
	}
	*e = Q->base[Q->front];
	//头指针往前移一位
	Q->front = (Q->front + 1) % MAXQSIZE;
	return OK;
}

Status enQueue(SqQueue *Q, QElemType e) {
	if ((Q->rear + 1) % MAXQSIZE == Q->front) {	//保留一个内存空间 方便判断队满
		exit(ERROR);
	}
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXQSIZE;
	return OK;
}

int queueLen(SqQueue Q) {
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

Status initQueue(SqQueue *Q) {
	Q->base = (QElemType *)malloc(sizeof(QElemType));
	if (!Q->base) {
		exit(OVERFLOW);
	}
	//头尾指针为0 队列为空
	Q->front = Q->rear = 0;
	return OK;
}


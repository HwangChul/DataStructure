#include <stdio.h>
#include <stdlib.h>

//�������״̬����
#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define INFEASIBLE -1 // infeasible
#define OVERFLOW   -2

//Status�Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int Status;

typedef struct {
	int n;
} QElemType;

typedef struct Qnode {
	QElemType data;
	struct Qnode *next;
} QNode, *QPtr;

typedef struct {
	QPtr front;//��ͷָ��
	QPtr rear;//��βָ��
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
	//��ͷɾ��
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
	//����β�巨  �����ǰ��� �Ƚ��ȳ�
	QPtr p;
	p = (QPtr)malloc(sizeof(QNode));
	p->data = data;
	p->next = NULL;
	//��β����
	Q->rear->next = p;
	Q->rear = p;
	return OK;
}

Status destroyQueue(LinkQueue *Q) {
	while (Q->front) {
		//�ö�βָ�뵱����ʱָ��
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




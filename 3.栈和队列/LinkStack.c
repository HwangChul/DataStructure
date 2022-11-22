#include <stdio.h>
#include <stdlib.h>

#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW   -2

typedef int Status;

typedef struct {
	int n;
} SElemType;

typedef struct stackNode {
	SElemType data;
	struct stackNode *next;
} StackNode, *LinkStack;

Status pushStack(LinkStack S, SElemType e);
Status initStack(StackNode *S);
Status popStack(LinkStack S, SElemType *data);
SElemType getTop(LinkStack S);

int main() {
	LinkStack LS;
	LS = (LinkStack)malloc(sizeof(StackNode));
	initStack(LS);//��ʼ��LS
	printf("%p\n", LS->next);

	SElemType data, data1;
	data.n = 5;
	pushStack(LS, data);//ѹջ
	printf("LS->data.n=%d\n", LS->next->data.n);
	data1 = getTop(LS);
	printf("data1.n=%d\n", data1.n);
	return 0;
}

SElemType getTop(LinkStack S) {
	if (S != NULL) {
		return S->next->data;
	}
}

Status initStack(StackNode *S) {
	S->next = NULL;
	return OK;
}

Status pushStack(LinkStack S, SElemType data) {
	//����ͷ�巨  ͷ���Ϊջ��  ǰ���ǰ��� ����ȳ�
	StackNode *p;
	p = (LinkStack)malloc(sizeof(StackNode));
	p->data = data;
	p->next = S->next;
	S->next = p;
	return OK;
}

Status popStack(LinkStack S, SElemType *data) {
	if (S->next == NULL) {
		return ERROR;
	}
	StackNode *p, *top;
	top = S->next;	//ջ��
	*data = top->data;
	p = top;
	top = top->next;
	S->next = top;
	free(p);
	return OK;
}



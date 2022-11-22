#include <stdio.h>
#include <stdlib.h>

//函数结果状态代码
#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define INFEASIBLE -1 // infeasible
#define OVERFLOW   -2
#define MAXSIZE    20

//Status是函数的类型，其值是函数结果状态代码
typedef int Status;

typedef struct {
	int n;
} SElemType;

typedef struct {
	SElemType *top;
	SElemType *base;
	int stackSize;
} SqStack;

Status initStack(SqStack *S);
Status destroyStack(SqStack *S);
Status pushStack(SqStack *S, SElemType e);
Status popStack(SqStack *S, SElemType *e);
Status stackEmpty(SqStack S);

int main() {
	SqStack s1;
	initStack(&s1);
	SElemType e, e1;
	e.n = 1;
	pushStack(&s1, e);
	e1.n = 2;
	pushStack(&s1, e1);
	popStack(&s1, &e);
	printf("e.n=%d\n", e.n);
	printf("%d\n", (s1.top - 1)->n);
	printf("元素个数=%d\n", s1.top - s1.base);
	destroyStack(&s1);
	return 0;
}

Status stackEmpty(SqStack S) {
	if (S.top == S.base) {
		return TRUE;
	} else {
		return FALSE;
	}
}

Status popStack(SqStack *S, SElemType *e) {
	if (S->top - S->base == 0) {
		return ERROR;
	}
	//先减再用  --S->top, *e = S->top
	*e = *(--S->top);
	return OK;
}

Status pushStack(SqStack *S, SElemType e) {
	if (S->top - S->base == S->stackSize) {
		return ERROR;
	}
	//*S->top = e, S->top++
	*(S->top++) = e;
	return OK;
}

Status initStack(SqStack *S) {
	//初始化分配空间
	S->base = (SElemType *)malloc(sizeof(SElemType) * MAXSIZE);
	if (!S->base)
		exit(OVERFLOW);
	S->top = S->base;
	S->stackSize = MAXSIZE;
	return OK;
}

Status destroyStack(SqStack *S) {
	if (S->base) {
		free(S->base);
		S->base = S->top = NULL;
		S->stackSize = 0;
	}
	return OK;
}







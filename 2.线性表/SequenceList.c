#include <stdio.h>
#include <stdlib.h>

//�������״̬����
#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define INFEASIBLE -1 // infeasible
#define OVERFLOW   -2
#define MAXSIZE    20

//Status�Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int Status;
typedef char Elemtype;

typedef struct {
	int n;
} ElemType;

typedef struct {
	ElemType *elem;
	int len;
} SqList;

Status InitList_Sq(SqList *L, int *a, int len) {			//��ʼ��һ��˳���
	L->elem = (ElemType *)malloc(sizeof(ElemType) * MAXSIZE);	//Ϊ˳������ռ�
	if (!L->elem) {		//����洢����ʧ�� ���
		exit(OVERFLOW);
	}
	for (int i = 0; i < len; i++) {
		L->elem[i].n = a[i];
	}
	L->len = len;		//�ձ���Ϊ0
	return OK;
}

void DestroyList(SqList *L) {		//�������Ա�
	if (L->elem) {
		free(L->elem);	//�ͷ�L->elem�Ĵ洢�ռ�(��Ϊ�Ǹ�L->elem����Ŀռ�)
	}
}

void ClearList(SqList *L) {		//���һ�����Ա�
	L->len = 0;		//�����Ա�ĳ�������Ϊ0
}

int GetLen(SqList *L) {		//�������Ա�L�ĳ���
	return L->len;
}

int IsEmpty(SqList *L) {		//�ж����Ա�L�Ƿ�Ϊ��
	if (L->len == 0) {
		return 1;
	} else {
		return 0;
	}
}

int GetElem(SqList L, int i, ElemType *elem) {		//�õ�iλ�õ�Ԫ��
	if (i < 1 || i > L.len) {
		return ERROR;
	}
	*elem = L.elem[i - 1];
	return OK;
}

int LocateElem(SqList L, ElemType elem) {		//����elem���ڵ�λ��
	for (int i = 0; i < L.len; i++) {
		if (L.elem[i].n == elem.n) {
			return i + 1;
		}
	}
	return 0;
}

Status InsertSqList(SqList *L, int x, ElemType elem) {		//��xλ�ò���һ��Ԫ��
	if (x < 1 || x > L->len + 1 || L->len == MAXSIZE) {		//�ж�Ҫ�����λ���Ƿ�Ϸ�
		return ERROR;
	}
	for (int i = (L->len - 1); i >= x - 1; i--) {
		L->elem[i + 1] = L->elem[i];			//�ѵ�i��Ԫ�ظ�ֵ��i+1(�Ӻ���ǰ ������һλ)
	}
	L->elem[x - 1] = elem;
	L->len++;
	return OK;
}

Status DeleteSqList(SqList *L, int x, ElemType *e) {		//ɾ�����Ա��е�һ��Ԫ�ز����ظ�Ԫ��
	if (x < 1 || x > L->len) {								//�ж�����λ���Ƿ�Ϸ�
		return ERROR;
	}
	(*e).n = L->elem[x - 1].n;
	for (int i = x; i < L->len; i++) {
		L->elem[i - 1] = L->elem[i];			//�ѵ�i��Ԫ�ظ�ֵ��i-1(��ǰ���� ��ǰ��һλ)
	}
	L->len--;
	return OK;
}

void unionSqList(SqList *La, SqList Lb) {
	int La_len;
	La_len = La->len;
	for (int i = 1; i < Lb.len; i++) {
		ElemType elem;
		GetElem(Lb, i, &elem);
		if (!LocateElem(*La, elem)) {
			InsertSqList(La, ++La_len, elem);
		}
	}
}

void displayList(SqList L) {
	for (int i = 0; i < L.len; i++) {
		printf("L.elem[%d].n = %d;\n", i, L.elem[i].n);
	}
}

void mergeSqList(SqList La, SqList Lb, SqList *Lc) {
	ElemType *pa, *pb, *pc, *pa_last, *pb_last;
	pa = La.elem;
	pb = Lb.elem;
	//Lc˳����ʼ��
	Lc->len = La.len + Lb.len;
	Lc->elem = (ElemType *)malloc(sizeof(ElemType) * (Lc->len + 1));
	pc = Lc->elem;
	pa_last = La.elem + La.len - 1;
	pb_last = Lb.elem + Lb.len - 1;
	while (pa <= pa_last && pb <= pb_last) {
		//pa��pb����Ϊ��
		if (pa->n <= pb->n) {
			//�Ƚ�pa��pb�Ĵ�С
			*pc++ = *pa++;
		} else {
			*pc++ = *pb++;
		}
	}
	//������һ����Ϊ��ʱ ����һ�����ֵд��Lc
	while (pa <= pa_last)
		*pc++ = *pa++;
	while (pb <= pb_last)
		*pc++ = *pb++;
}

int main () {
	int a[] = {1, 7, 8};
	int b[] = {2, 4, 6, 8, 10, 11};
	SqList ploy1, ploy2, ploy3;
	InitList_Sq(&ploy1, a, 3);
	InitList_Sq(&ploy2, b, 6);
	mergeSqList(ploy1, ploy2, &ploy3);
	displayList(ploy3);
	DestroyList(&ploy1);
	DestroyList(&ploy2);
	DestroyList(&ploy3);
	return 0;
}



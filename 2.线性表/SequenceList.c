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
typedef char Elemtype;

typedef struct {
	int n;
} ElemType;

typedef struct {
	ElemType *elem;
	int len;
} SqList;

Status InitList_Sq(SqList *L, int *a, int len) {			//初始化一个顺序表
	L->elem = (ElemType *)malloc(sizeof(ElemType) * MAXSIZE);	//为顺序表分配空间
	if (!L->elem) {		//如果存储分配失败 溢出
		exit(OVERFLOW);
	}
	for (int i = 0; i < len; i++) {
		L->elem[i].n = a[i];
	}
	L->len = len;		//空表长度为0
	return OK;
}

void DestroyList(SqList *L) {		//销毁线性表
	if (L->elem) {
		free(L->elem);	//释放L->elem的存储空间(因为是给L->elem分配的空间)
	}
}

void ClearList(SqList *L) {		//清空一个线性表
	L->len = 0;		//将线性表的长度重置为0
}

int GetLen(SqList *L) {		//返回线性表L的长度
	return L->len;
}

int IsEmpty(SqList *L) {		//判断线性表L是否为空
	if (L->len == 0) {
		return 1;
	} else {
		return 0;
	}
}

int GetElem(SqList L, int i, ElemType *elem) {		//得到i位置的元素
	if (i < 1 || i > L.len) {
		return ERROR;
	}
	*elem = L.elem[i - 1];
	return OK;
}

int LocateElem(SqList L, ElemType elem) {		//返回elem所在的位置
	for (int i = 0; i < L.len; i++) {
		if (L.elem[i].n == elem.n) {
			return i + 1;
		}
	}
	return 0;
}

Status InsertSqList(SqList *L, int x, ElemType elem) {		//在x位置插入一个元素
	if (x < 1 || x > L->len + 1 || L->len == MAXSIZE) {		//判断要插入的位置是否合法
		return ERROR;
	}
	for (int i = (L->len - 1); i >= x - 1; i--) {
		L->elem[i + 1] = L->elem[i];			//把第i个元素赋值给i+1(从后往前 往后移一位)
	}
	L->elem[x - 1] = elem;
	L->len++;
	return OK;
}

Status DeleteSqList(SqList *L, int x, ElemType *e) {		//删除线性表中的一个元素并返回该元素
	if (x < 1 || x > L->len) {								//判断输入位置是否合法
		return ERROR;
	}
	(*e).n = L->elem[x - 1].n;
	for (int i = x; i < L->len; i++) {
		L->elem[i - 1] = L->elem[i];			//把第i个元素赋值给i-1(从前往后 往前移一位)
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
	//Lc顺序表初始化
	Lc->len = La.len + Lb.len;
	Lc->elem = (ElemType *)malloc(sizeof(ElemType) * (Lc->len + 1));
	pc = Lc->elem;
	pa_last = La.elem + La.len - 1;
	pb_last = Lb.elem + Lb.len - 1;
	while (pa <= pa_last && pb <= pb_last) {
		//pa和pb都不为空
		if (pa->n <= pb->n) {
			//比较pa和pb的大小
			*pc++ = *pa++;
		} else {
			*pc++ = *pb++;
		}
	}
	//当其中一个表为空时 把另一个表的值写入Lc
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



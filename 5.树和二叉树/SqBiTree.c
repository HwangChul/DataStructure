#include <stdio.h>
#include <stdlib.h>

#define OK 		1
#define ERROR 	0
#define TRUE    1
#define FALSE   0
#define INFEASIBLE -1
#define OVERFLOW   -2
#define MAXTSIZE   15

typedef int Status;

typedef struct {
	int n;
} TElemType;

//����ȫ��������ŵ����±���˳���洢������һ��������ر��ǵ�֧�����Ѻ�
typedef struct {
	TElemType *elem;
} SqBiTree;

int main() {
	SqBiTree bt;
	TElemType elem;
	bt.elem = (TElemType *)malloc(sizeof(TElemType) * MAXTSIZE);
	for (int i = 1; i < MAXTSIZE + 1; i++) {
		elem.n = i;
		bt.elem[i] = elem;
		printf("bt.elem[%d]=%d\n", i, bt.elem[i]);
	}
	return 0;
}




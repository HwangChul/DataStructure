#include <stdio.h>
#include <stdlib.h>

//�������״̬����
#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define INFEASIBLE -1 // infeasible
#define OVERFLOW   -2
#define CHUNKSIZE  80

//Status�Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int Status;

typedef struct chunkNode {
	//�����ṹ ��ڵ�
	char ch[CHUNKSIZE];
	struct chunkNode *next;
} ChunkNode;

typedef struct {
	//����ͷָ�� βָ��
	ChunkNode *head, *tail;
	int curlen;		//���ĵ�ǰ����
} LString;

int main() {
	return 0;
}




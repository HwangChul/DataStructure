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

typedef struct {
	int n;
	char ch;
} TElemType;

//˫�ױ�ʾ��
typedef struct PTNode {
	TElemType data;
	int parent;				//���˫�׽����±�
} PTNode;

typedef struct {
	PTNode nodes[MAXSIZE];	//���˫�׽��
	int r, n;				//������λ�úͽ�����
} PTree;

//���ӱ�ʾ��
typedef struct CTNode {		//���ӽ��
	int child;
	struct CTNode *next;	//ָ����һ�����ӽ��
} *ChildPtr;

typedef struct {			//˫�׽��
	TElemType data;
	ChildPtr firstChild;	//ָ���һ�����ӽ��
} CTBox;

typedef struct {			//���ṹ
	CTBox nodes[MAXSIZE];	//���˫�׽��
	int r, n;				//������λ�úͽ�����
} CTree;

//�����ֵܱ�ʾ��(��������ʾ��)
typedef struct CSNode {
	TElemType data;
	struct CSNode *firstChild, *nextSibling;//��ŵ�һ�����ӽ�����һ���ֵܽ��
} CSNode, *CSTree;

int main() {
	return 0;
}


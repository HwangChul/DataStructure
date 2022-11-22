#include <stdio.h>
#include <stdlib.h>

//函数结果状态代码
#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define INFEASIBLE -1 // infeasible
#define OVERFLOW   -2
#define MAXSIZE    100

//Status是函数的类型，其值是函数结果状态代码
typedef int Status;

typedef struct {
	int n;
	char ch;
} TElemType;

//双亲表示法
typedef struct PTNode {
	TElemType data;
	int parent;				//存放双亲结点的下标
} PTNode;

typedef struct {
	PTNode nodes[MAXSIZE];	//存放双亲结点
	int r, n;				//根结点的位置和结点个数
} PTree;

//孩子表示法
typedef struct CTNode {		//孩子结点
	int child;
	struct CTNode *next;	//指向下一个孩子结点
} *ChildPtr;

typedef struct {			//双亲结点
	TElemType data;
	ChildPtr firstChild;	//指向第一个孩子结点
} CTBox;

typedef struct {			//树结构
	CTBox nodes[MAXSIZE];	//存放双亲结点
	int r, n;				//根结点的位置和结点个数
} CTree;

//孩子兄弟表示法(二叉树表示法)
typedef struct CSNode {
	TElemType data;
	struct CSNode *firstChild, *nextSibling;//存放第一个孩子结点和下一个兄弟结点
} CSNode, *CSTree;

int main() {
	return 0;
}


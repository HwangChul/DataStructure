#include <stdio.h>
#include <stdlib.h>

//函数结果状态代码
#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define INFEASIBLE -1 // infeasible
#define OVERFLOW   -2
#define CHUNKSIZE  80

//Status是函数的类型，其值是函数结果状态代码
typedef int Status;

typedef struct chunkNode {
	//块链结构 块节点
	char ch[CHUNKSIZE];
	struct chunkNode *next;
} ChunkNode;

typedef struct {
	//串的头指针 尾指针
	ChunkNode *head, *tail;
	int curlen;		//串的当前长度
} LString;

int main() {
	return 0;
}




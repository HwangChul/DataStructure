#include <stdio.h>
#include <stdlib.h>
//函数结果状态代码
#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define INFEASIBLE -1 // infeasible
#define OVERFLOW   -2
//Status是函数的类型，其值是函数结果状态代码
typedef int Status;

typedef struct node {
	int data;
	struct node *next;
} Node, *Link;

typedef struct douNode {
	int data;
	struct douNode *next, *prior;
} DouNode, *DouLink;

Link rearList(int *a, int n);
void displayList(Link linkList, Node *rear);
Status destroyList(Link linkList, Node *rear);
Status insertList(Link linkList, int i, int elem);
Status deleteList(Link linkList, int i, int *elem);
Link rearNode(Link linkList);
Node *connectionList(Node *a, Node *b);
DouLink rearDouList(int *a, int n);
void displayDouList(DouLink linkList);
Status insertDouList(DouLink linkList, int i, int elem);
Status deleteDouList(DouLink linkList, int i, int *elem);
Status destroyDouList(DouLink linkList);

int main() {
	int a[] = {0, 1, 2, 3, 4, 5};
	int b[] = {6, 7, 8, 9, 10, 11};
	Link head, link, headRear, linkRear, con;
	head = rearList(a, 6);
	link = rearList(b, 6);
	headRear = rearNode(head);
	linkRear = rearNode(link);
	con = connectionList(headRear, linkRear);
	//displayList(con->next, con);
	//只需要销毁合并后的链表或者销毁第一个链表就可以
	destroyList(con->next, con);
	DouLink douHead;
	douHead = rearDouList(a, 6);
	insertDouList(douHead, 3, 8);
	int elem;
	deleteDouList(douHead, 3, &elem);
	printf("elem=%d\n", elem);
	displayDouList(douHead);
	destroyDouList(douHead);
	return 0;
}

Status destroyDouList(DouLink linkList) {
	//销毁链表的每一个结点
	DouNode *p;
	while (linkList) {
		p = linkList;
		linkList = linkList->next;
		free(p);
	}
	return OK;
}

Status insertDouList(DouLink linkList, int i, int elem) {
	int j = 0;
	while (linkList && (i - 1) > j) {
		linkList = linkList->next;
		j++;
	}
	if (!linkList || (i - 1) < j)
		return ERROR;
	DouLink douNode;
	douNode = (DouNode *)malloc(sizeof(DouNode));
	douNode->data = elem;
	//新结点的地址给i+1的prior	i+1的地址给新结点的next
	linkList->next->prior = douNode;
	douNode->next = linkList->next;
	//再把新结点的地址给i-1的next   i-1地址给新结点的prior
	linkList->next = douNode;
	douNode->prior = linkList;
	return OK;
}

Status deleteDouList(DouLink linkList, int i, int *elem) {
	//双向链表的结点删除
	int j = 0;
	while (linkList && i > j) {
		linkList = linkList->next;
		j++;
	}
	if (!linkList || i < j)
		return ERROR;
	*elem = linkList->data;
	linkList->next->prior = linkList->prior;
	linkList->prior->next = linkList->next;
	free(linkList);
	return OK;
}

void displayDouList(DouLink linkList) {
	//双向链表和单链表一样
	while (linkList->next != NULL) {
		//因为头结点的data没有初始化所以从第二个结点开始
		linkList = linkList->next;
		printf("%d\n", linkList->data);
	}
}

DouLink rearDouList(int *a, int n) {
	//尾插法
	DouNode *head, *rear;
	head = (DouNode *)malloc(sizeof(DouNode));
	head->data = 6;
	head->next = head->prior = NULL;
	rear = head;
	for (int i = 0; i < n; i++) {
		DouNode *douNode;
		douNode = (DouNode *)malloc(sizeof(DouNode));
		douNode->data = a[i];
		douNode->next = NULL;
		//新结点的prior指向前一个结点
		//前一个结点的next指向新结点
		douNode->prior = rear;
		rear->next = douNode;
		rear = douNode;
	}
	return head;
}

Node *connectionList(Node *a, Node *b) {
	//合并循环链表
	Node *p;
	//保存头结点
	p = a->next;
	a->next = b->next->next;
	free(b->next);
	b->next = p;
	return b;
	//合并之后只有返回的链表，传入的两个链表没了
}

Status deleteList(Link linkList, int i, int *elem) {
	//删除第i个结点
	Node *node;
	int j = 0;
	//找到第i结点的前驱
	while (linkList && (i - 1) > j) {
		linkList = linkList->next;
		j++;
	}
	if (!linkList || (i - 1) < j)
		return ERROR;
	node = linkList->next;
	//让i结点的前驱指向i结点的后继 然后释放i结点的空间
	linkList->next = node->next;
	*elem = node->data;
	free(node);
	return OK;
}

Status insertList(Link linkList, int i, int elem) {
	//把elem插入到第i个位置
	int j = 0;
	while (linkList && (i - 1) > j) {
		linkList = linkList->next;
		j++;
	}
	if (!linkList || (i - 1) < j)
		return ERROR;
	Node *node;
	node = (Link)malloc(sizeof(Node));
	node->data = elem;
	//i-1号的next赋值给node->next
	//再把i-1的next指向node
	node->next = linkList->next;
	linkList->next = node;
	return OK;
}

Status destroyList(Link linkList, Node *rear) {
	//销毁链表的每一个结点
	Node *p;
	while (linkList != rear) {
		p = linkList;
		linkList = linkList->next;
		free(p);
	}
	free(rear);
	return OK;
}

Link rearList(int *a, int n) {
	//创建头结点
	Link head;
	head = (Link)malloc(sizeof(Node));
	head->next = NULL;
	Node *rear;
	rear = head;
	//创建后续结点
	for (int i = 0; i < n; i++) {
		Node *node;
		node = (Link)malloc(sizeof(Node));
		//尾插法
		node->data = a[i];
		node->next = NULL;
		rear->next = node;
		rear = node;
	}
	// 这里返回head结点，因为rear结点在链表的结尾next指向NULL
	return head;
}

void displayList(Link linkList, Node *rear) {
	while (linkList != rear) {
		//因为头结点的data没有初始化所以从第二个结点开始
		linkList = linkList->next;
		printf("%d\n", linkList->data);
	}
}

Link rearNode(Link linkList) {
	//求尾结点
	Node *node;
	node = linkList;
	while (node->next != NULL) {
		node = node->next;
		if (node->next == NULL) {
			node->next = linkList;
			return node;
		}
	}
}








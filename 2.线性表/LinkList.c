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

Link headList(int *a, int n);
Link rearList(Link head, int *a, int n);
void displayList(Link linkList);
int isEmpty(Link linkList);
Status destroyList(Link linkList);
Status emptyList(Link linkList);
int lenList(Link linkList);
Status getElem(Link linkList, int i, int *elem);
Node *locateElem(Link linkList, int i, int *loc);
Status insertList(Link linkList, int i, int elem);
Status deleteList(Link linkList, int i, int *elem);
Link rearNode(Link linkList);
void unionList(Link La, Link Lb, Link La_rear);
void mergeLinkList(Link La, Link Lb, Link Lm);
void sortList(Link L, Link L_n);

int main() {
	int a[] = {1, 7, 8};
	int b[] = {2, 4, 6, 8, 10, 11};
	Link head, link, head_rear, merge;
	head = (Link)malloc(sizeof(Node));
	link = (Link)malloc(sizeof(Node));
	merge = (Link)malloc(sizeof(Node));
	head_rear = rearList(head, a, 3);
	rearList(link, b, 6);
	displayList(link);
//	unionList(head, link, head_rear);
	mergeLinkList(head, link, merge);
	//displayList(merge);
	destroyList(merge);
//	displayList(head);
//	destroyList(head);
	return 0;
}

void mergeLinkList(Link La, Link Lb, Link Lm) {
	//有序表合并链表实现  生成一个新的链表
	//La, Lb的结点都移到了Lm 只需要free头结点
	Node *pa, *pb, *pm;
	pa = La->next;
	pb = Lb->next;
//	Lm = La;
	/*将La赋值给Lm有bug
	此时应该Lm La指向同一个链表
	打印数据和销毁应该两个都可以
	但只能用La
	*/
	Lm->next = NULL;
	pm = Lm;
	while (pa && pb ) {
		if (pa->data <= pb->data) {
			pm->next = pa;
			pm = pa;
			pa = pa->next;
		} else {
			pm->next = pb;
			pm = pb;
			pb = pb->next;
		}
	}
	pm->next = pa ? pa : pb;
	free(La);
	free(Lb);
}

void unionList(Link La, Link Lb, Link La_rear) {
	//合并线性表 并去除一样的元素
	//Lb没有变化
	int La_len, Lb_len, loc;
	La_len = lenList(La);
	Lb_len = lenList(Lb);
	for (int i = 0; i < Lb_len; i++) {
		Lb = Lb->next;
		if (!locateElem(La, Lb->data, &loc)) {
			Node *node;
			node = (Link)malloc(sizeof(Node));
			node->data = Lb->data;
			node->next = La_rear->next;
			La_rear->next = node;
			La_rear = node;
		}
	}
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

Node *locateElem(Link linkList, int i, int *loc) {
	//查找i所在的地址和序号loc(通过地址返回)
	Node *p, *q;
	q = NULL;
	p = linkList->next;
	int j = 1;
	while (p && p->data != i) {
		p = p->next;
		j++;
	}
	if (p) {
		//loc返回序号 p返回i所在结点的地址
		*loc = j;
		return p;
	} else
		return q;
}

Status getElem(Link linkList, int i, int *elem) {
	//查询第i个位置的元素
	Node *p;
	int j = 1;
	p = linkList->next;
	//先判断要查询的位置是否大于j 且结点的next不为NULL
	while (i > j && (p->next != NULL)) {
		p = p->next;
		j++;
	}
	//当循环结束 结点的next为NULL时 或查询位置小于j时
	if (i < j || !(p->next)) {
		return ERROR;
	}
	*elem = p->data;
	return OK;
}

Status emptyList(Link linkList) {
	//重置linkList为空表
	Node *p, *q;
	p = linkList->next;
	while (p) {
		q = p->next;
		free(p);
		p = q;
	}
	//把头结点的指针域设为NULL
	linkList->next = NULL;
	return OK;
}

Status destroyList(Link linkList) {
	//销毁链表的每一个结点
	Node *p;
	while (linkList) {
		p = linkList;
		linkList = linkList->next;
		free(p);
	}
	return OK;
}

int isEmpty(Link linkList) {
	//判断是否为空表 是返回1 不是返回0
	if (linkList->next)
		return 0;
	else
		return 1;
}

Link rearList(Link head, int *a, int n) {
	//传入头结点 返回的是尾节点
//	Link head;
//	head = (Link)malloc(sizeof(Node));
	head->data = n;
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
//	return head;
	return rear;
}

Link headList(int *a, int n) {
	//创建头结点
	Link head;
	head = (Link)malloc(sizeof(Node));
	head->data = n;
	head->next = NULL;
	for (int i = n; i > 0; i--) {
		//头插法
		Node *node;
		node = (Link)malloc(sizeof(Node));
		node->data = a[i - 1];
		node->next = head->next;
		head->next = node;
	}
	return head;
}

void displayList(Link linkList) {
	while (linkList->next != NULL) {
		//因为头结点的data没有初始化所以从第二个结点开始
		linkList = linkList->next;
		printf("%d\n", linkList->data);
	}
}

int lenList(Link linkList) {
	int i = 0;
	while (linkList->next != NULL) {
		i++;
		linkList = linkList->next;
	}
	return i;
}

Link rearNode(Link linkList) {
	Node *node;
	node = linkList;
	while (node->next != NULL) {
		//因为头结点的data没有初始化所以从第二个结点开始
		node = node->next;
		if (node->next == NULL) {
			node->next = linkList;
			return node;
		}
	}
}

void sortList(Link L, Link L_n) {
	//递归查找最大值
	if (L_n != NULL) {
		if (L->data > L_n->data) {
			sortList(L, L_n->next);
		} else {
			sortList(L_n, L_n->next);
		}
	} else {
		printf("max = %d\n", L->data);
	}
}




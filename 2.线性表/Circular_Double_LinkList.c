#include <stdio.h>
#include <stdlib.h>
//�������״̬����
#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define INFEASIBLE -1 // infeasible
#define OVERFLOW   -2
//Status�Ǻ��������ͣ���ֵ�Ǻ������״̬����
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
	//ֻ��Ҫ���ٺϲ��������������ٵ�һ������Ϳ���
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
	//���������ÿһ�����
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
	//�½��ĵ�ַ��i+1��prior	i+1�ĵ�ַ���½���next
	linkList->next->prior = douNode;
	douNode->next = linkList->next;
	//�ٰ��½��ĵ�ַ��i-1��next   i-1��ַ���½���prior
	linkList->next = douNode;
	douNode->prior = linkList;
	return OK;
}

Status deleteDouList(DouLink linkList, int i, int *elem) {
	//˫������Ľ��ɾ��
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
	//˫������͵�����һ��
	while (linkList->next != NULL) {
		//��Ϊͷ����dataû�г�ʼ�����Դӵڶ�����㿪ʼ
		linkList = linkList->next;
		printf("%d\n", linkList->data);
	}
}

DouLink rearDouList(int *a, int n) {
	//β�巨
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
		//�½���priorָ��ǰһ�����
		//ǰһ������nextָ���½��
		douNode->prior = rear;
		rear->next = douNode;
		rear = douNode;
	}
	return head;
}

Node *connectionList(Node *a, Node *b) {
	//�ϲ�ѭ������
	Node *p;
	//����ͷ���
	p = a->next;
	a->next = b->next->next;
	free(b->next);
	b->next = p;
	return b;
	//�ϲ�֮��ֻ�з��ص������������������û��
}

Status deleteList(Link linkList, int i, int *elem) {
	//ɾ����i�����
	Node *node;
	int j = 0;
	//�ҵ���i����ǰ��
	while (linkList && (i - 1) > j) {
		linkList = linkList->next;
		j++;
	}
	if (!linkList || (i - 1) < j)
		return ERROR;
	node = linkList->next;
	//��i����ǰ��ָ��i���ĺ�� Ȼ���ͷ�i���Ŀռ�
	linkList->next = node->next;
	*elem = node->data;
	free(node);
	return OK;
}

Status insertList(Link linkList, int i, int elem) {
	//��elem���뵽��i��λ��
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
	//i-1�ŵ�next��ֵ��node->next
	//�ٰ�i-1��nextָ��node
	node->next = linkList->next;
	linkList->next = node;
	return OK;
}

Status destroyList(Link linkList, Node *rear) {
	//���������ÿһ�����
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
	//����ͷ���
	Link head;
	head = (Link)malloc(sizeof(Node));
	head->next = NULL;
	Node *rear;
	rear = head;
	//�����������
	for (int i = 0; i < n; i++) {
		Node *node;
		node = (Link)malloc(sizeof(Node));
		//β�巨
		node->data = a[i];
		node->next = NULL;
		rear->next = node;
		rear = node;
	}
	// ���ﷵ��head��㣬��Ϊrear���������Ľ�βnextָ��NULL
	return head;
}

void displayList(Link linkList, Node *rear) {
	while (linkList != rear) {
		//��Ϊͷ����dataû�г�ʼ�����Դӵڶ�����㿪ʼ
		linkList = linkList->next;
		printf("%d\n", linkList->data);
	}
}

Link rearNode(Link linkList) {
	//��β���
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








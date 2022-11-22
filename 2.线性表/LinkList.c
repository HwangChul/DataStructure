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
	//�����ϲ�����ʵ��  ����һ���µ�����
	//La, Lb�Ľ�㶼�Ƶ���Lm ֻ��Ҫfreeͷ���
	Node *pa, *pb, *pm;
	pa = La->next;
	pb = Lb->next;
//	Lm = La;
	/*��La��ֵ��Lm��bug
	��ʱӦ��Lm Laָ��ͬһ������
	��ӡ���ݺ�����Ӧ������������
	��ֻ����La
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
	//�ϲ����Ա� ��ȥ��һ����Ԫ��
	//Lbû�б仯
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

Node *locateElem(Link linkList, int i, int *loc) {
	//����i���ڵĵ�ַ�����loc(ͨ����ַ����)
	Node *p, *q;
	q = NULL;
	p = linkList->next;
	int j = 1;
	while (p && p->data != i) {
		p = p->next;
		j++;
	}
	if (p) {
		//loc������� p����i���ڽ��ĵ�ַ
		*loc = j;
		return p;
	} else
		return q;
}

Status getElem(Link linkList, int i, int *elem) {
	//��ѯ��i��λ�õ�Ԫ��
	Node *p;
	int j = 1;
	p = linkList->next;
	//���ж�Ҫ��ѯ��λ���Ƿ����j �ҽ���next��ΪNULL
	while (i > j && (p->next != NULL)) {
		p = p->next;
		j++;
	}
	//��ѭ������ ����nextΪNULLʱ ���ѯλ��С��jʱ
	if (i < j || !(p->next)) {
		return ERROR;
	}
	*elem = p->data;
	return OK;
}

Status emptyList(Link linkList) {
	//����linkListΪ�ձ�
	Node *p, *q;
	p = linkList->next;
	while (p) {
		q = p->next;
		free(p);
		p = q;
	}
	//��ͷ����ָ������ΪNULL
	linkList->next = NULL;
	return OK;
}

Status destroyList(Link linkList) {
	//���������ÿһ�����
	Node *p;
	while (linkList) {
		p = linkList;
		linkList = linkList->next;
		free(p);
	}
	return OK;
}

int isEmpty(Link linkList) {
	//�ж��Ƿ�Ϊ�ձ� �Ƿ���1 ���Ƿ���0
	if (linkList->next)
		return 0;
	else
		return 1;
}

Link rearList(Link head, int *a, int n) {
	//����ͷ��� ���ص���β�ڵ�
//	Link head;
//	head = (Link)malloc(sizeof(Node));
	head->data = n;
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
//	return head;
	return rear;
}

Link headList(int *a, int n) {
	//����ͷ���
	Link head;
	head = (Link)malloc(sizeof(Node));
	head->data = n;
	head->next = NULL;
	for (int i = n; i > 0; i--) {
		//ͷ�巨
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
		//��Ϊͷ����dataû�г�ʼ�����Դӵڶ�����㿪ʼ
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
		//��Ϊͷ����dataû�г�ʼ�����Դӵڶ�����㿪ʼ
		node = node->next;
		if (node->next == NULL) {
			node->next = linkList;
			return node;
		}
	}
}

void sortList(Link L, Link L_n) {
	//�ݹ�������ֵ
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




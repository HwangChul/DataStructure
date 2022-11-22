#include <stdio.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW   -2
#define MaxInt  32767			//��ʾ���ֵ ����
#define MVNum     100			//��󶥵���
#define MAXQSIZE   20			//�������洢����

typedef int Status;
typedef int QElemType;			//������������
typedef int ArcType;			//��ߵ�ȨֵΪ����
typedef char VertexType;		//�趥�����������Ϊ�ַ���

typedef struct sqQueue {
	QElemType *base;
	int front;
	int rear;
} SqQueue;						//˳�����


//�ڽӾ���
typedef struct {
	VertexType vexs[MVNum];		//�����
	ArcType arcs[MVNum][MVNum];	//�ڽӾ���
	int vexnum, arcnum;			//ͼ�ĵ�ǰ�������ͱ���
} AMGraph;						//Adjacency Matrix Graph �ڽӾ���ͼ

//�ڽӱ�
typedef struct ArcNode {		//�߽��
	int adjvex;					//����ָ��Ķ����λ��
	struct ArcNode *nextarc;	//ָ����һ���ߵ�ָ��
	int info;					//�ͱ���ص���Ϣ
} ArcNode;

typedef struct {
	int in;						//�������
	VertexType data;			//������Ϣ
	ArcNode *firstArc;			//ָ�������ö���ıߵ�ָ��
} VNode, AdjList[MVNum];		//AdjList��ʾ�ڽӱ�����

typedef struct {
	AdjList vertices;			//��Ŷ�������ڽӱ�
	int vexnum, arcnum;			//ͼ�ĵ�ǰ�������ͻ���
} ALGraph;						//Adjacency List Graph �ڽӱ�ͼ

//����ԭ��
Status initQueue(SqQueue *Q);
Status enQueue(SqQueue *Q, QElemType e);
Status deQueue(SqQueue *Q, QElemType *e);
Status createUDN(AMGraph *G);				//����������G Undirected Net
int locateVex(AMGraph G, VertexType v);		//����v��G.vexs�е�λ�ò�����
void DFS(AMGraph G, int v, int *visited);	//���������������
void BFS(ALGraph G, int v, int *visited);	//���������������
Status topoGraph(ALGraph *G);				//�������� �ؼ�·���� ����ͼ
Status TopologicalSort(ALGraph G, int *visited, int *topo);//��������
Status CriticalPath(ALGraph G, int *visited);//�ؼ�·��

int main() {
	int n = 100, visited[n];
	for (int i = 0; i < n; i++) {
		visited[i] = 0;				//ȫ����ʼ��Ϊ0
	}
//	AMGraph *G;
//	G = (AMGraph *)malloc(sizeof(AMGraph));
//	DFS(*G, 1, visited);

	ALGraph *G;
	G = (ALGraph *)malloc(sizeof(ALGraph));
	topoGraph(G);
	CriticalPath(*G, visited);
//	BFS(*G, 0, visited);//�����û���� ����main��������ֵ����
	return 0;
}

Status CriticalPath(ALGraph G, int *visited) {	//�ؼ�·��
	int n = G.vexnum;
	int ve[n], vl[n], e, l;//�¼�������ٷ���ʱ�� �������ٷ���ʱ��
	int k, j;
	ArcNode *p;
	p = (ArcNode *)malloc(sizeof(ArcNode));
	int topo[n];
	//�������������㷨���������б�����topo�� ������ʧ�������������� ����ERROR
	if (!TopologicalSort(G, visited, topo)) {
		return ERROR;
	}
	for (int i = 0; i < n; i++) {				//��ÿ���¼������緢��ʱ�丳��ֵ
		ve[i] = 0;
	}
	/*�������������������������˴�����ÿ���¼������緢��ʱ�䣭������������������*/
	for (int i = 0; i < n; i++) {
		k = topo[i];				//ȡ�����������еĶ������k
		p = G.vertices[k].firstArc;	//pָ��k�ĵ�һ���ڽӶ���
		while (p) {					//���θ���k�������ڽӶ�������緢��ʱ��
			j = p->adjvex;			//jΪ�ڽӶ�������
			if (ve[j] < ve[k] + p->info) {//���¶���j�����緢��ʱ��ve[j]
				ve[j] = ve[k] + p->info;
			}
			p = p->nextarc;			//pָ��k����һ���ڽӶ���
		}//while
	}//for
	for (int i = 0; i < n; i++) {		//��ÿ���¼�����ٷ���ʱ�丳��ֵve[n-1]
		vl[i] = ve[n - 1];
	}
	/*���������������������������˴�����ÿ���¼�����ٷ���ʱ�䣭������������������*/
	for (int i = n - 1; i >= 0; i--) {
		k = topo[i];				//ȡ�����������еĶ������k
		p = G.vertices[k].firstArc;	//pָ��k�ĵ�һ���ڽӶ���
		while (p) {					//����k���ڽӵ� �����¼�k����ٷ���ʱ��
			j = p->adjvex;			//jΪ�ڽӶ�������
			if (vl[k] > vl[j] - p->info) { //���¶���k����ٷ���ʱ��vl[k]
				vl[k] = vl[j] - p->info;
			}
			p = p->nextarc;			//pָ��k����һ���ڽӶ���
		}//while
	}//for
	/*���������������������ж�ÿһ���Ƿ�Ϊ�ؼ����������������������*/
	for (int i = 0; i < n; i++) {			//ÿ��ѭ�����viΪ���ʼ������л
		p = G.vertices[i].firstArc;	//pָ��i�ĵ�һ���ڽӶ���
		while (p) {
			j = p->adjvex;			//jΪi���ڽӶ�������
			e = ve[i];				//����<vi��vj>�����翪ʼʱ��
			l = vl[j] - p->info;	//����<vi��vj>����ٿ�ʼʱ��
			if (e == l) {
				printf("%c %c\n", G.vertices[i].data, G.vertices[j].data);
			}
			p = p->nextarc;
		}//while
	}//for
}

Status TopologicalSort(ALGraph G, int *visited, int *topo) {		//��������
	SqQueue Q;
	initQueue(&Q);				//��ʼ������Q
	QElemType data;				//�����������
	int count = 0, index;		//��ʼ�������� indexΪѰ���ڽӵ������
	ArcNode *p;					//ָ��pָ���ڽӱ�
	p = (ArcNode *)malloc(sizeof(ArcNode));
	for (int i = 0; i < G.vexnum; i++) {		//ɨ�趥��� ��û��ǰ����δ����Ķ������
		if (G.vertices[i].in == 0 && visited[i] == 0) {
			visited[i] = 1;
			enQueue(&Q, i);
		}
	}
	while (!(Q.front == Q.rear)) {				//�ӷǿ�ʱѭ��
		deQueue(&Q, &data);						//ȡ��ͷԪ��Vj
//		printf("%c ", G.vertices[data].data);
		topo[count++] = data;					//������������
		p = G.vertices[data].firstArc;			//׼��������Vj���ڽӵ�����-1
		while (p) {
			index = p->adjvex;
			G.vertices[index].in--;
			p = p->nextarc;
		}
		for (int i = 0; i < G.vexnum; i++) {	//�ٴ�ɨ�趥������Ϊ0��δ����Ķ������
			if (G.vertices[i].in == 0 && visited[i] == 0) {
				visited[i] = 1;
				enQueue(&Q, i);
			}
		}
	}
	if (count < G.vexnum) {						//������ͼ�л�·
		return ERROR;
	} else {
		return OK;
	}
}

void BFS(ALGraph G, int v, int *visited) {	//���������������
	printf("%c\t", G.vertices[v].data);
	visited[v] = 1;
	SqQueue Q;
	QElemType data;
	initQueue(&Q);
	data = v;
	enQueue(&Q, data);				//v����
	while (!(Q.front == Q.rear)) {	//���зǿ�
		deQueue(&Q, &data);			//��ͷԪ�س���
		ArcNode *p;
		p = G.vertices[data].firstArc;		//�ӵ�һ���ڽӵ㿪ʼ����
		while (p) {
			if (!visited[p->adjvex]) {
				printf("%c\t", G.vertices[p->adjvex].data);
				visited[p->adjvex] = 1;
				data = p->adjvex;
				enQueue(&Q, data);
			}
			p = p->nextarc;					//��һ���ڽӵ�
//			p = G.vertices[data].firstArc;//��ȣ���
		}
	}
}

void DFS(AMGraph G, int v, int *visited) {			//���������������
	//�ڽӾ���ͼ
	printf("%c\t", G.vexs[v]);
	visited[v] = 1;
	for (int w = 0; w < G.vexnum; w++) {
		//��һ���ڵ����������һ���ڽ���û�б����ʹ��Ľڵ�
		//Ȼ����ڽӵ������������
		//û��δ���ʵĽڵ�֮����ݵ���һ���ڵ�ȥ������һ���ڽӵ�
		//ֱ������Ľڵ�������ٽ�㶼�������
		if ((G.arcs[v][w] != 0) && (!visited[w])) {
			DFS(G, w, visited);
		}
	}
}

Status createUDN(AMGraph *G) {	//���������� Undirected Net
	printf("���뼸������:");
	scanf("%d", &G->vexnum);
	printf("���뼸����:");
	scanf("%d", &G->arcnum);

	for (int i = 0; i < G->vexnum; i++) {
		printf("������Ϣ:");
		scanf("%s", &G->vexs[i]);			//��������Ϣ
	}

	for (int i = 0; i < G->vexnum; i++) {	//��ʼ���ڽӾ���
		for (int j = 0; j < G->vexnum; j++) {
//			G->arcs[i][j] = MaxInt;			//�ߵ�Ȩֵ��Ϊ����ֵ
			G->arcs[i][j] = 0;
		}
	}

	char v1, v2;
	int i, j, w;
	for (int k = 0; k < G->arcnum; k++) {	//�����ڽӾ����е�ֵ
		printf("����һ���������������������Լ��ߵ�Ȩֵ(�س����ո�����):\n");
		scanf("%s", &v1);
		i = locateVex(*G, v1);				//ȷ��v1��G->vexs�е�λ��

		scanf("%s", &v2);
		j = locateVex(*G, v2);				//ȷ��v2��G->vexs�е�λ��

//		printf("v1 = %c\n", v1);			//v1 v2������ûֵ�ˣ�����
//		scanf("%d", &w);
//		G->arcs[i][j] = G->arcs[j][i] = w;	//<v1, v2>�ͶԳƱ�<v2, v1>��ȨֵΪw
		G->arcs[i][j] = G->arcs[j][i] = 1;
	}
}

int locateVex(AMGraph G, char v) {			//����v��G.vexs�е�λ�ò�����
	for (int i = 0; i < G.vexnum; i++) {
		if (v == G.vexs[i]) {
			return i;
		}
	}
	return -1;
}

Status topoGraph(ALGraph *G) {				//�������� �ؼ�·���� �����ڽ�����ͼ
	G->vexnum = 9;
	G->arcnum = 11;
	char spot[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
	for (int i = 0; i < G->vexnum; i++) {	//�����ͷ����
		G->vertices[i].data = spot[i];
		G->vertices[i].firstArc = NULL;		//��ʼ����ͷ����ָ����
		G->vertices[i].in = 0;
	}
	int i, j, w;
	ArcNode *p1, *p2;
	char edge[11][3] = {{0, 1, 6}, {0, 2, 4}, {0, 3, 5}, {1, 4, 1}, {2, 4, 1}, {3, 5, 2}, {4, 6, 9}, {4, 7, 7}, {5, 7, 4}, {6, 8, 2}, {7, 8, 4}};
	for (int k = 0; k < G->arcnum; k++) {
		i = edge[k][0];
		j = edge[k][1];
		w = edge[k][2];
		p1 = (ArcNode *)malloc(sizeof(ArcNode));
		p2 = (ArcNode *)malloc(sizeof(ArcNode));
		p1->adjvex = j;
		p1->info = w;
		p1->nextarc = G->vertices[i].firstArc;	//ͷ�巨
		G->vertices[i].firstArc = p1;
		//����ͼ
//		p2->adjvex = i;
//		p2->info = w;
//		p2->nextarc = G->vertices[j].firstArc;
//		G->vertices[j].firstArc = p2;
	}

	ArcNode *p;
	p = (ArcNode *)malloc(sizeof(ArcNode));
	for (int i = 0; i < G->vexnum; i++) {
		if (G->vertices[i].firstArc == NULL) {
			continue;
		} else {
			p = G->vertices[i].firstArc;
			while (p) {
				G->vertices[p->adjvex].in++;
				p = p->nextarc;
			}
		}
	}
}

Status deQueue(SqQueue *Q, QElemType *e) {
	if (Q->front == Q->rear) {
		exit(ERROR);
	}
	*e = Q->base[Q->front];
	//ͷָ����ǰ��һλ
	Q->front = (Q->front + 1) % MAXQSIZE;
	return OK;
}

Status enQueue(SqQueue *Q, QElemType e) {
	if ((Q->rear + 1) % MAXQSIZE == Q->front) {	//����һ���ڴ�ռ� �����ж϶���
		exit(ERROR);
	}
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXQSIZE;
	return OK;
}

Status initQueue(SqQueue *Q) {
	Q->base = (QElemType *)malloc(sizeof(QElemType));
	if (!Q->base) {
		exit(OVERFLOW);
	}
	//ͷβָ��Ϊ0 ����Ϊ��
	Q->front = Q->rear = 0;
	return OK;
}

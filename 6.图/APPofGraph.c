#include <stdio.h>
#include <stdlib.h>


#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW   -2
#define MaxInt  30000			//��ʾ���ֵ ���� 32767
#define MVNum     100			//��󶥵���
#define MaxEdge   100			//������

typedef int Status;
typedef int ArcType;			//��ߵ�ȨֵΪ����
typedef char VertexType;		//�趥�����������Ϊ�ַ���

//��С������
typedef struct {
	int from, to;				//��ʼ��
	int weight;					//Ȩֵ
} EdgeType;						//��űߵ���������

typedef struct {
	VertexType vertex[MVNum];	//��Ŷ�������
	EdgeType egde[MaxEdge];		//��űߵ�����
	int vertexNum, edgeMum;		//ͼ�Ķ������ͱ���
} EdgeGraph;

typedef struct {
	int adjvex;
	int lowcost;
} ShortEdge;					//��С��������������

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
Status createUDG(ALGraph *G);					//�����ڽӱ��ʾ�� ��������ͼG
int LocateVex(ALGraph G, char v);				//����v��G.vertices�е�λ�ò�����
int findMinDist(int *S, int *dist, AMGraph G);	//dist�в���S=0����Сֵ
void Dijkstra(AMGraph G, int starV);			//�Ͻ�˹�����㷨
void printPath(int *dist, int *path, AMGraph G, int starV);//��ӡ���·��
void Floyd(AMGraph G);							//���������㷨 path����û��ʵ��
void Prim(AMGraph G, int start);				//����ķ�㷨
int minEdge(ShortEdge *se, AMGraph G);			//������shortEdge��ѡ����С�ı�
Status MST(AMGraph *G);							//����ķ�㷨 �Ͻ�˹�����㷨��ͼ
Status EG(EdgeGraph *eg);						//�����߼�����洢��ͼ
void Kruskal(EdgeGraph G);						//��³˹�����㷨
int findRoot(int *parent, int v);				//�ҵ������������ĸ��ڵ�

int main() {
	AMGraph *G;
	G = (AMGraph *)malloc(sizeof(AMGraph));
	MST(G);
	Prim(*G, 0);
//	Dijkstra(*G, 0);
	printf("\n");
	EdgeGraph *eg;
	eg = (EdgeGraph *)malloc(sizeof(EdgeGraph));
	EG(eg);
	Kruskal(*eg);
	return 0;
}

void Floyd(AMGraph G) {
	int dist[G.vexnum][G.vexnum];
//	char path[G.vexnum][G.vexnum][G.vexnum];		//path���鲻��
	for (int i = 0; i < G.vexnum; i++) {			//��ʼ��dist
		for (int j = 0; j < G.vexnum; j++) {
			dist[i][j] = G.arcs[i][j];
//			for (int k = 0; k < G.vexnum; k++) {
//				path[i][j][k] = '-';
//			}
//			if (dist[i][j] != MaxInt && dist[i][j] != 0) {
//				path[i][j][0] = G.vexs[i];
//				path[i][j][1] = G.vexs[j];
//			}
		}
	}
	for (int k = 0; k < G.vexnum; k++) {
		for (int i = 0; i < G.vexnum; i++) {
			for (int j = 0; j < G.vexnum; j++) {
				int n = 0;
				if (dist[i][j] > dist[i][k] + dist[k][j]) {		//��i j���𲽼����м䶥��k��
					dist[i][j] = dist[i][k] + dist[k][j];		//���i��j�Ķ����̾͸���
//					for (n; n < G.vexnum; n++) {
//						if (path[i][k][n] != '-') {
//							path[i][j][n] = path[i][k][n];
//						} else {
//							break;
//						}
//					}
//					for (n; n < G.vexnum; n++) {
//						path[i][j][n] =  path[j][k][n];
//					}
				}
			}
		}
	}
}

void Dijkstra(AMGraph G, int starV) {
	int S[G.vexnum], dist[G.vexnum], path[G.vexnum];
	//����S��ֵΪ1������±�ָ�Ķ��� ��ʾ�ڼ����� �Ѿ��滮���
	//dist�����е�ֵΪ�����±���ָ�Ķ���ľ���(Ȩֵ)
	//path������Ϊʼ�㵽�յ�����·�� �Ӻ���ǰ��
	for (int i = 0; i < G.vexnum; i++) {
		S[i] = 0;								//��ʼ��S ��ֵ��Ϊ0
		dist[i] = G.arcs[starV][i];				//��ʼ��dist ֵΪʼ�㵽������������·��
		if (dist[i] !=  MaxInt) {
			path[i] = starV;					//��ʼ��path ���ʼ���е�ĳ������Ļ���path[i]Ϊ��ʼ�� ����Ϊ-1
		} else {
			path[i] = -1;
		}
	}
	S[starV] = 1;								//ʼ����뼯��S ��ʾ�Ѿ��滮���
	int num = 1, min;							//�Ѿ��滮�Ķ���num = 1��
	while (num < G.vexnum) {
		min = findMinDist(S, dist, G);			//dist�в���S=0����Сֵ
		S[min] = 1;								//��Сֵ����S
		for (int i = 0; i < G.vexnum; i++) {	//���´�ʼ����������ж�������·������
			if ((S[i] == 0) && (dist[i] > dist[min] + G.arcs[min][i])) {
				dist[i] = dist[min] + G.arcs[min][i];		//���ҵ������·���޸Ķ�Ӧ��dist
				path[i] = min;					//�޸Ķ�Ӧ��path
			}
		}
		num++;
	}
	printPath(dist, path, G, starV);
}


void printPath(int *dist, int *path, AMGraph G, int starV) {
	//��starV�ڵ㵽�����ڵ�����·�����浽index_path��Ȼ���ʽ��������·��
	int index_path[G.vexnum], count, min;
	for (int i = 0; i < G.vexnum; i++) {	//i�����յ�
		if (i == starV) {					//�����ʼ��һ��������
			continue;
		}
		count = 0;
		min = path[i];
		index_path[count++] = min;
		while (min != starV) {
			min = path[min];
			index_path[count++] = min;
		}
		printf("��ʼ��%d��ʼ�������յ�%d��", G.vexs[starV], G.vexs[i]);
		for (--count; count >= 0; count--) {
			printf("%d--->", G.vexs[index_path[count]]);
		}
		printf("%d����Ȩֵ��%d\n", G.vexs[i], dist[i]);
	}
}

int findMinDist(int *S, int *dist, AMGraph G) {
	int min;
	for (int i = 0; i < G.vexnum; i++) {
		if (S[i] == 0 ) {
			for (int j = 0; j < G.vexnum; j++) {
				if (S[j] == 0 ) {
					if (dist[i] < dist[j]) {
						min = i;
					} else {
						min = j;
						i = j;//��Ϊi����ǰ��
					}//if
				}//if
			}//for j
			break;
		}//if
	}//for i
	return min;
}

Status createUDG(ALGraph *G) {				//�����ڽӱ��ʾ�� ��������ͼG
	printf("���뼸������:");
	scanf("%d", &G->vexnum);
	printf("���뼸����:");
	scanf("%d", &G->arcnum);
	for (int i = 0; i < G->vexnum; i++) {	//�����ͷ����
		printf("������Ϣ:");
		scanf("%s", &G->vertices[i].data);	//��������Ϣ
		G->vertices[i].firstArc = NULL;		//��ʼ����ͷ����ָ����
		G->vertices[i].in = 0;
	}
	char v1, v2;
	int i, j, w;
	ArcNode *p1, *p2;
	for (int k = 0; k < G->arcnum; k++) {
		printf("����һ���������������������Լ��ߵ�Ȩֵ(�س����ո�����):\n");
		scanf("%s", &v1);
		i = LocateVex(*G, v1);				//ȷ��v1��G->vertices�е�λ��
		scanf("%s", &v2);
		j = LocateVex(*G, v2);				//ȷ��v2��G->vertices�е�λ��
//		scanf("%d", &w);

		p1 = (ArcNode *)malloc(sizeof(ArcNode));
		p2 = (ArcNode *)malloc(sizeof(ArcNode));
//		p1->info = p2->info = w;
		//����ͼ
		p1->adjvex = j;						//i�ڽӵ�����Ϊj ��ͷ�巨���뵽G->vertices.firstArc
		p1->nextarc = G->vertices[i].firstArc;
		G->vertices[i].firstArc = p1;
		//����ͼ
		p2->adjvex = i;						//����ͼ��һ����ͬ�ı� j�ڽӵ�����Ϊi
		p2->nextarc = G->vertices[j].firstArc;
		G->vertices[j].firstArc = p2;
	}

	ArcNode *p;
	p = (ArcNode *)malloc(sizeof(ArcNode));
	for (int i = 0; i < G->vexnum; i++) {		//����ÿ����������
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

int LocateVex(ALGraph G, char v) {			//����v��G.vertices�е�λ�ò�����
	for (int i = 0; i < G.vexnum; i++) {
		if (v == G.vertices[i].data) {
			return i;
		}
	}
	return -1;
}

void Prim(AMGraph G, int start) {				//��С������
	ShortEdge se[G.vexnum];
	for (int i = 0; i < G.vexnum; i++) {		//��ʼ����������shortEdge
		se[i].adjvex = start;
		se[i].lowcost = G.arcs[start][i];
	}
	se[start].lowcost = 0;						//���start���뼯��U

	int k;
	for (int i = 0; i < G.vexnum - 1; i++) {
		k = minEdge(se, G);						//Ѱ����̱ߵ��ڽӵ�
		printf("(%d, %d, %d) ", se[k].adjvex, k, se[k].lowcost);//�����С������·��
		se[k].lowcost = 0;						//����k���뼯��U
		for (int j = 0; j < G.vexnum; j++) {	//��������shortEdge
			if (G.arcs[k][j] < se[j].lowcost) {	//�¼���Ķ��㵽���ߵľ����ԭ�������
				se[j].lowcost = G.arcs[k][j];
				se[j].adjvex = k;
			}
		}
	}
}

int minEdge(ShortEdge *se, AMGraph G) {			//������shortEdge��ѡ����С�ı�
	int min;
	for (int i = 0; i < G.vexnum; i++) {
		if (se[i].lowcost != 0) {
			for (int j = 0; j < G.vexnum; j++) {
				if (se[j].lowcost != 0 ) {
					if (se[i].lowcost < se[j].lowcost) {
						min = i;
					} else {
						min = j;
						i = j;
					}//if
				}//if
			}//for j
			break;
		}//if
	}//for i
	return min;
}

Status MST(AMGraph *G) {					//����ķ�㷨 �Ͻ�˹�����㷨
	G->vexnum = 8;
	G->arcnum = 14;

	char spot[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	for (int i = 0; i < G->vexnum; i++) {
		G->vexs[i] = spot[i];
	}
	for (int i = 0; i < G->vexnum; i++) {
		for (int j = 0; j < G->vexnum; j++) {
			G->arcs[i][j] = MaxInt;
		}
	}

	char v1, v2;
	int i, j, w;
	char arc[14][3] = {{0, 1, 4}, {0, 2, 6}, {0, 3, 6}, {1, 4, 7}, {1, 2, 1}, {3, 2, 2}, {3, 5, 6}, {2, 4, 5}, {2, 5, 3}, {5, 6, 1}, {6, 4, 1}, {4, 7, 6}, {5, 7, 8}, {6, 7, 5}};
	for (int k = 0; k < G->arcnum; k++) {
		i = arc[k][0];
		j = arc[k][1];
		w = arc[k][2];
		G->arcs[i][j] = G->arcs[j][i] = w;
	}
}

void Kruskal(EdgeGraph G) {
	int vex1, vex2, count;
	int parent[G.vertexNum];						//�ж����������Ƿ�����һ�����ڵ�(�Ƿ񹹳ɻ�)
	for (int i = 0; i < G.vertexNum; i++) {			//parent�����ʼ��
		parent[i] = -1;
	}
	for (int i = 0; i < G.edgeMum; i++) {
		vex1 = findRoot(parent, G.egde[i].from);	//�ҵ������������ĸ��ڵ�
		vex2 = findRoot(parent, G.egde[i].to);
		if (vex1 != vex2) {							//�ҵ����������ڵ㲻һ�� ���ṹ�ɻ�
			printf("(%d, %d, %d) ", G.egde[i].from, G.egde[i].to, G.egde[i].weight);//�����С������·��
			parent[vex2] = vex1;					//�ϲ�������
			count++;
			if (count == G.vertexNum - 1) {			//�Ѿ����� ��ǰ����
				return;
			}
		}
	}
}

int findRoot(int *parent, int v) {					//�ҵ������������ĸ��ڵ�
	int t = v;
	while (parent[t] > -1) {
		t = parent[t];
	}
	return t;
}

Status EG(EdgeGraph *eg) {					//�����߼�����洢��ͼ ��³˹�����㷨
	eg->vertexNum = 6;
	eg->edgeMum = 9;
	char spot[6] = {0, 1, 2, 3, 4, 5};
	for (int i = 0; i < eg->vertexNum; i++) {
		eg->vertex[i] = spot[i];
	}
	int edge[9][3] = {{1, 4, 12}, {2, 3, 17}, {0, 5, 19}, {2, 5, 25}, {3, 5, 25}, {4, 5, 26}, {0, 1, 34}, {3, 4, 38}, {0, 2, 46}};
	for (int i = 0; i < eg->edgeMum; i++) {
		eg->egde[i].from = edge[i][0];
		eg->egde[i].to = edge[i][1];
		eg->egde[i].weight = edge[i][2];
	}
}

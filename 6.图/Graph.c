#include <stdio.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW   -2
#define MaxInt  32767			//表示最大值 即∞
#define MVNum     100			//最大顶点数
#define MAXQSIZE   20			//队列最大存储数量

typedef int Status;
typedef int QElemType;			//队列数据类型
typedef int ArcType;			//设边的权值为整数
typedef char VertexType;		//设顶点的数据类型为字符型

typedef struct sqQueue {
	QElemType *base;
	int front;
	int rear;
} SqQueue;						//顺序队列


//邻接矩阵
typedef struct {
	VertexType vexs[MVNum];		//顶点表
	ArcType arcs[MVNum][MVNum];	//邻接矩阵
	int vexnum, arcnum;			//图的当前顶点数和边数
} AMGraph;						//Adjacency Matrix Graph 邻接矩阵图

//邻接表
typedef struct ArcNode {		//边结点
	int adjvex;					//边所指向的顶点的位置
	struct ArcNode *nextarc;	//指向下一个边的指针
	int info;					//和边相关的信息
} ArcNode;

typedef struct {
	int in;						//代表入度
	VertexType data;			//顶点信息
	ArcNode *firstArc;			//指向依附该顶点的边的指针
} VNode, AdjList[MVNum];		//AdjList表示邻接表类型

typedef struct {
	AdjList vertices;			//存放顶点结点的邻接表
	int vexnum, arcnum;			//图的当前顶点数和弧数
} ALGraph;						//Adjacency List Graph 邻接表图

//函数原型
Status initQueue(SqQueue *Q);
Status enQueue(SqQueue *Q, QElemType e);
Status deQueue(SqQueue *Q, QElemType *e);
Status createUDN(AMGraph *G);				//构建无向网G Undirected Net
int locateVex(AMGraph G, VertexType v);		//查找v在G.vexs中的位置并返回
void DFS(AMGraph G, int v, int *visited);	//深度优先搜索遍历
void BFS(ALGraph G, int v, int *visited);	//广度优先搜索遍历
Status topoGraph(ALGraph *G);				//拓扑排序 关键路径用 构造图
Status TopologicalSort(ALGraph G, int *visited, int *topo);//拓扑排序
Status CriticalPath(ALGraph G, int *visited);//关键路径

int main() {
	int n = 100, visited[n];
	for (int i = 0; i < n; i++) {
		visited[i] = 0;				//全部初始化为0
	}
//	AMGraph *G;
//	G = (AMGraph *)malloc(sizeof(AMGraph));
//	DFS(*G, 1, visited);

	ALGraph *G;
	G = (ALGraph *)malloc(sizeof(ALGraph));
	topoGraph(G);
	CriticalPath(*G, visited);
//	BFS(*G, 0, visited);//结点少没问题 结点多main函数返回值出错
	return 0;
}

Status CriticalPath(ALGraph G, int *visited) {	//关键路径
	int n = G.vexnum;
	int ve[n], vl[n], e, l;//事件最早最迟发生时间 活动最早最迟发生时间
	int k, j;
	ArcNode *p;
	p = (ArcNode *)malloc(sizeof(ArcNode));
	int topo[n];
	//调用拓扑排序算法将拓扑序列保存在topo中 若调用失败则代表存在有向环 返回ERROR
	if (!TopologicalSort(G, visited, topo)) {
		return ERROR;
	}
	for (int i = 0; i < n; i++) {				//给每个事件的最早发生时间赋初值
		ve[i] = 0;
	}
	/*－－－－－－－－－－按拓扑次序求每个事件的最早发生时间－－－－－－－－－－*/
	for (int i = 0; i < n; i++) {
		k = topo[i];				//取得拓扑序列中的顶点序号k
		p = G.vertices[k].firstArc;	//p指向k的第一个邻接顶点
		while (p) {					//依次更新k的所有邻接顶点的最早发生时间
			j = p->adjvex;			//j为邻接顶点的序号
			if (ve[j] < ve[k] + p->info) {//更新顶点j的最早发生时间ve[j]
				ve[j] = ve[k] + p->info;
			}
			p = p->nextarc;			//p指向k的下一个邻接顶点
		}//while
	}//for
	for (int i = 0; i < n; i++) {		//给每个事件的最迟发生时间赋初值ve[n-1]
		vl[i] = ve[n - 1];
	}
	/*－－－－－－－－－－按逆拓扑次序求每个事件的最迟发生时间－－－－－－－－－－*/
	for (int i = n - 1; i >= 0; i--) {
		k = topo[i];				//取得拓扑序列中的顶点序号k
		p = G.vertices[k].firstArc;	//p指向k的第一个邻接顶点
		while (p) {					//根据k的邻接点 更新事件k的最迟发生时间
			j = p->adjvex;			//j为邻接顶点的序号
			if (vl[k] > vl[j] - p->info) { //更新顶点k的最迟发生时间vl[k]
				vl[k] = vl[j] - p->info;
			}
			p = p->nextarc;			//p指向k的下一个邻接顶点
		}//while
	}//for
	/*－－－－－－－－－－判断每一项活动是否为关键活动－－－－－－－－－－*/
	for (int i = 0; i < n; i++) {			//每次循环针对vi为活动开始点的所有活动
		p = G.vertices[i].firstArc;	//p指向i的第一个邻接顶点
		while (p) {
			j = p->adjvex;			//j为i的邻接顶点的序号
			e = ve[i];				//计算活动<vi，vj>的最早开始时间
			l = vl[j] - p->info;	//计算活动<vi，vj>的最迟开始时间
			if (e == l) {
				printf("%c %c\n", G.vertices[i].data, G.vertices[j].data);
			}
			p = p->nextarc;
		}//while
	}//for
}

Status TopologicalSort(ALGraph G, int *visited, int *topo) {		//拓扑排序
	SqQueue Q;
	initQueue(&Q);				//初始化队列Q
	QElemType data;				//保存出队数据
	int count = 0, index;		//初始化计数器 index为寻找邻接点的索引
	ArcNode *p;					//指针p指向邻接边
	p = (ArcNode *)malloc(sizeof(ArcNode));
	for (int i = 0; i < G.vexnum; i++) {		//扫描顶点表 将没有前驱且未排序的顶点入队
		if (G.vertices[i].in == 0 && visited[i] == 0) {
			visited[i] = 1;
			enQueue(&Q, i);
		}
	}
	while (!(Q.front == Q.rear)) {				//队非空时循环
		deQueue(&Q, &data);						//取队头元素Vj
//		printf("%c ", G.vertices[data].data);
		topo[count++] = data;					//存入拓扑序列
		p = G.vertices[data].firstArc;			//准备将顶点Vj的邻接点的入度-1
		while (p) {
			index = p->adjvex;
			G.vertices[index].in--;
			p = p->nextarc;
		}
		for (int i = 0; i < G.vexnum; i++) {	//再次扫描顶点表将入度为0且未排序的顶点入队
			if (G.vertices[i].in == 0 && visited[i] == 0) {
				visited[i] = 1;
				enQueue(&Q, i);
			}
		}
	}
	if (count < G.vexnum) {						//该有向图有回路
		return ERROR;
	} else {
		return OK;
	}
}

void BFS(ALGraph G, int v, int *visited) {	//广度优先搜索遍历
	printf("%c\t", G.vertices[v].data);
	visited[v] = 1;
	SqQueue Q;
	QElemType data;
	initQueue(&Q);
	data = v;
	enQueue(&Q, data);				//v进队
	while (!(Q.front == Q.rear)) {	//队列非空
		deQueue(&Q, &data);			//队头元素出队
		ArcNode *p;
		p = G.vertices[data].firstArc;		//从第一个邻接点开始遍历
		while (p) {
			if (!visited[p->adjvex]) {
				printf("%c\t", G.vertices[p->adjvex].data);
				visited[p->adjvex] = 1;
				data = p->adjvex;
				enQueue(&Q, data);
			}
			p = p->nextarc;					//下一个邻接点
//			p = G.vertices[data].firstArc;//深度？？
		}
	}
}

void DFS(AMGraph G, int v, int *visited) {			//深度优先搜索遍历
	//邻接矩阵图
	printf("%c\t", G.vexs[v]);
	visited[v] = 1;
	for (int w = 0; w < G.vexnum; w++) {
		//从一个节点出发找它的一个邻接且没有被访问过的节点
		//然后从邻接点出发继续访问
		//没有未访问的节点之后回溯到上一个节点去访问另一个邻接点
		//直到传入的节点的所有临界点都访问完毕
		if ((G.arcs[v][w] != 0) && (!visited[w])) {
			DFS(G, w, visited);
		}
	}
}

Status createUDN(AMGraph *G) {	//构建无向网 Undirected Net
	printf("输入几个顶点:");
	scanf("%d", &G->vexnum);
	printf("输入几个边:");
	scanf("%d", &G->arcnum);

	for (int i = 0; i < G->vexnum; i++) {
		printf("顶点信息:");
		scanf("%s", &G->vexs[i]);			//输入点的信息
	}

	for (int i = 0; i < G->vexnum; i++) {	//初始化邻接矩阵
		for (int j = 0; j < G->vexnum; j++) {
//			G->arcs[i][j] = MaxInt;			//边的权值设为极大值
			G->arcs[i][j] = 0;
		}
	}

	char v1, v2;
	int i, j, w;
	for (int k = 0; k < G->arcnum; k++) {	//构造邻接矩阵中的值
		printf("输入一条边所依附的两个顶点以及边的权值(回车，空格区分):\n");
		scanf("%s", &v1);
		i = locateVex(*G, v1);				//确定v1在G->vexs中的位置

		scanf("%s", &v2);
		j = locateVex(*G, v2);				//确定v2在G->vexs中的位置

//		printf("v1 = %c\n", v1);			//v1 v2到这里没值了？？？
//		scanf("%d", &w);
//		G->arcs[i][j] = G->arcs[j][i] = w;	//<v1, v2>和对称边<v2, v1>的权值为w
		G->arcs[i][j] = G->arcs[j][i] = 1;
	}
}

int locateVex(AMGraph G, char v) {			//查找v在G.vexs中的位置并返回
	for (int i = 0; i < G.vexnum; i++) {
		if (v == G.vexs[i]) {
			return i;
		}
	}
	return -1;
}

Status topoGraph(ALGraph *G) {				//拓扑排序 关键路径用 构造邻接链表图
	G->vexnum = 9;
	G->arcnum = 11;
	char spot[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
	for (int i = 0; i < G->vexnum; i++) {	//构造表头结点表
		G->vertices[i].data = spot[i];
		G->vertices[i].firstArc = NULL;		//初始化表头结点的指针域
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
		p1->nextarc = G->vertices[i].firstArc;	//头插法
		G->vertices[i].firstArc = p1;
		//无向图
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
	//头指针往前移一位
	Q->front = (Q->front + 1) % MAXQSIZE;
	return OK;
}

Status enQueue(SqQueue *Q, QElemType e) {
	if ((Q->rear + 1) % MAXQSIZE == Q->front) {	//保留一个内存空间 方便判断队满
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
	//头尾指针为0 队列为空
	Q->front = Q->rear = 0;
	return OK;
}

#include <stdio.h>
#include <stdlib.h>


#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW   -2
#define MaxInt  30000			//表示最大值 即∞ 32767
#define MVNum     100			//最大顶点数
#define MaxEdge   100			//最大边数

typedef int Status;
typedef int ArcType;			//设边的权值为整数
typedef char VertexType;		//设顶点的数据类型为字符型

//最小生成树
typedef struct {
	int from, to;				//起始点
	int weight;					//权值
} EdgeType;						//存放边的数据类型

typedef struct {
	VertexType vertex[MVNum];	//存放顶点数据
	EdgeType egde[MaxEdge];		//存放边的数组
	int vertexNum, edgeMum;		//图的顶点数和边数
} EdgeGraph;

typedef struct {
	int adjvex;
	int lowcost;
} ShortEdge;					//最小生成树辅助数组

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
Status createUDG(ALGraph *G);					//采用邻接表表示法 创建无向图G
int LocateVex(ALGraph G, char v);				//查找v在G.vertices中的位置并返回
int findMinDist(int *S, int *dist, AMGraph G);	//dist中查找S=0的最小值
void Dijkstra(AMGraph G, int starV);			//迪杰斯特拉算法
void printPath(int *dist, int *path, AMGraph G, int starV);//打印最短路径
void Floyd(AMGraph G);							//弗洛伊德算法 path数组没有实现
void Prim(AMGraph G, int start);				//普利姆算法
int minEdge(ShortEdge *se, AMGraph G);			//在数组shortEdge中选择最小的边
Status MST(AMGraph *G);							//普利姆算法 迪杰斯特拉算法的图
Status EG(EdgeGraph *eg);						//构建边集数组存储的图
void Kruskal(EdgeGraph G);						//克鲁斯卡尔算法
int findRoot(int *parent, int v);				//找到所在生成树的根节点

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
//	char path[G.vexnum][G.vexnum][G.vexnum];		//path数组不会写π__π
	for (int i = 0; i < G.vexnum; i++) {			//初始化dist
		for (int j = 0; j < G.vexnum; j++) {
			dist[i][j] = G.arcs[i][j];
		}
	}
	for (int k = 0; k < G.vexnum; k++) {
		for (int i = 0; i < G.vexnum; i++) {
			for (int j = 0; j < G.vexnum; j++) {
				int n = 0;
				if (dist[i][j] > dist[i][k] + dist[k][j]) {		//在i j中逐步加入中间顶点k，
					dist[i][j] = dist[i][k] + dist[k][j];		//如果i到j的顶点变短就更新
				}
			}
		}
	}
}

void Dijkstra(AMGraph G, int starV) {
	int S[G.vexnum], dist[G.vexnum], path[G.vexnum];
	//数组S中值为1的这个下标指的顶点 表示在集合中 已经规划完毕
	//dist数组中的值为到该下标所指的顶点的距离(权值)
	//path数组中为始点到终点的最短路径 从后往前推
	for (int i = 0; i < G.vexnum; i++) {
		S[i] = 0;								//初始化S 其值都为0
		dist[i] = G.arcs[starV][i];				//初始化dist 值为始点到各个顶点的最短路径
		if (dist[i] !=  MaxInt) {
			path[i] = starV;					//初始化path 如果始点有到某个顶点的弧则path[i]为该始点 否则为-1
		} else {
			path[i] = -1;
		}
	}
	S[starV] = 1;								//始点放入集合S 表示已经规划完毕
	int num = 1, min;							//已经规划的顶点num = 1个
	while (num < G.vexnum) {
		min = findMinDist(S, dist, G);			//dist中查找S=0的最小值
		S[min] = 1;								//最小值加入S
		for (int i = 0; i < G.vexnum; i++) {	//更新从始点出发到所有顶点的最短路径长度
			if ((S[i] == 0) && (dist[i] > dist[min] + G.arcs[min][i])) {
				dist[i] = dist[min] + G.arcs[min][i];		//用找到的最短路径修改对应的dist
				path[i] = min;					//修改对应的path
			}
		}
		num++;
	}
	printPath(dist, path, G, starV);
}


void printPath(int *dist, int *path, AMGraph G, int starV) {
	//把starV节点到其他节点的最短路径保存到index_path，然后格式化输出最短路径
	int index_path[G.vexnum], count, min;
	for (int i = 0; i < G.vexnum; i++) {	//i代表终点
		if (i == starV) {					//如果起始点一样就跳过
			continue;
		}
		count = 0;
		min = path[i];
		index_path[count++] = min;
		while (min != starV) {
			min = path[min];
			index_path[count++] = min;
		}
		printf("从始点%d开始出发到终点%d：", G.vexs[starV], G.vexs[i]);
		for (--count; count >= 0; count--) {
			printf("%d--->", G.vexs[index_path[count]]);
		}
		printf("%d共计权值：%d\n", G.vexs[i], dist[i]);
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
						i = j;//因为i还在前面
					}//if
				}//if
			}//for j
			break;
		}//if
	}//for i
	return min;
}

Status createUDG(ALGraph *G) {				//采用邻接表表示法 创建无向图G
	printf("输入几个顶点:");
	scanf("%d", &G->vexnum);
	printf("输入几个边:");
	scanf("%d", &G->arcnum);
	for (int i = 0; i < G->vexnum; i++) {	//构造表头结点表
		printf("顶点信息:");
		scanf("%s", &G->vertices[i].data);	//输入点的信息
		G->vertices[i].firstArc = NULL;		//初始化表头结点的指针域
		G->vertices[i].in = 0;
	}
	char v1, v2;
	int i, j, w;
	ArcNode *p1, *p2;
	for (int k = 0; k < G->arcnum; k++) {
		printf("输入一条边所依附的两个顶点以及边的权值(回车，空格区分):\n");
		scanf("%s", &v1);
		i = LocateVex(*G, v1);				//确定v1在G->vertices中的位置
		scanf("%s", &v2);
		j = LocateVex(*G, v2);				//确定v2在G->vertices中的位置
//		scanf("%d", &w);

		p1 = (ArcNode *)malloc(sizeof(ArcNode));
		p2 = (ArcNode *)malloc(sizeof(ArcNode));
//		p1->info = p2->info = w;
		//有向图
		p1->adjvex = j;						//i邻接点的序号为j 用头插法插入到G->vertices.firstArc
		p1->nextarc = G->vertices[i].firstArc;
		G->vertices[i].firstArc = p1;
		//无向图
		p2->adjvex = i;						//无向图有一条相同的边 j邻接点的序号为i
		p2->nextarc = G->vertices[j].firstArc;
		G->vertices[j].firstArc = p2;
	}

	ArcNode *p;
	p = (ArcNode *)malloc(sizeof(ArcNode));
	for (int i = 0; i < G->vexnum; i++) {		//计算每个顶点的入度
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

int LocateVex(ALGraph G, char v) {			//查找v在G.vertices中的位置并返回
	for (int i = 0; i < G.vexnum; i++) {
		if (v == G.vertices[i].data) {
			return i;
		}
	}
	return -1;
}

void Prim(AMGraph G, int start) {				//最小生成树
	ShortEdge se[G.vexnum];
	for (int i = 0; i < G.vexnum; i++) {		//初始化辅助数组shortEdge
		se[i].adjvex = start;
		se[i].lowcost = G.arcs[start][i];
	}
	se[start].lowcost = 0;						//起点start放入集合U

	int k;
	for (int i = 0; i < G.vexnum - 1; i++) {
		k = minEdge(se, G);						//寻找最短边的邻接点
		printf("(%d, %d, %d) ", se[k].adjvex, k, se[k].lowcost);//输出最小生成树路径
		se[k].lowcost = 0;						//顶点k加入集合U
		for (int j = 0; j < G.vexnum; j++) {	//调整数组shortEdge
			if (G.arcs[k][j] < se[j].lowcost) {	//新加入的顶点到各边的距离和原来的相比
				se[j].lowcost = G.arcs[k][j];
				se[j].adjvex = k;
			}
		}
	}
}

int minEdge(ShortEdge *se, AMGraph G) {			//在数组shortEdge中选择最小的边
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

Status MST(AMGraph *G) {					//普利姆算法 迪杰斯特拉算法
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
	int parent[G.vertexNum];						//判断两个顶点是否属于一个根节点(是否构成环)
	for (int i = 0; i < G.vertexNum; i++) {			//parent数组初始化
		parent[i] = -1;
	}
	for (int i = 0; i < G.edgeMum; i++) {
		vex1 = findRoot(parent, G.egde[i].from);	//找到所在生成树的根节点
		vex2 = findRoot(parent, G.egde[i].to);
		if (vex1 != vex2) {							//找到的两个根节点不一样 不会构成环
			printf("(%d, %d, %d) ", G.egde[i].from, G.egde[i].to, G.egde[i].weight);//输出最小生成树路径
			parent[vex2] = vex1;					//合并生成树
			count++;
			if (count == G.vertexNum - 1) {			//已经生成 提前返回
				return;
			}
		}
	}
}

int findRoot(int *parent, int v) {					//找到所在生成树的根节点
	int t = v;
	while (parent[t] > -1) {
		t = parent[t];
	}
	return t;
}

Status EG(EdgeGraph *eg) {					//构建边集数组存储的图 克鲁斯卡尔算法
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

#include <stdio.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW   -2

typedef int Status;

typedef struct {
	int weight, parent, lch, rch;
} HTNode, *HuffmanTree;

typedef struct {
	//如何把字符数组存进去
	char *code;
} HCNode, *HuffmanCode;

void createHuffmanTree(HuffmanTree HT, int n);			//创建哈夫曼树
void selectMin(HuffmanTree HT, int n, int *s1, int *s2);//求权值的最小值和次小值
void createHuffmanCode(HuffmanTree HT, int n);			//哈夫曼编码

int main() {
	HuffmanTree HT;
	int n = 7;											//叶子结点数
	HT = (HTNode *)malloc(sizeof(HTNode) * 2 * n);
	createHuffmanTree(HT, n);
	createHuffmanCode(HT, n);
//	for (int i = 1; i <= (2 * n - 1); i++) {
//		printf("HT[%d].weight = %d\t", i, HT[i].weight);
//		printf("HT[%d].parent = %d\t", i, HT[i].parent);
//		printf("HT[%d].lch    = %d\t", i, HT[i].lch);
//		printf("HT[%d].rch    = %d\n", i, HT[i].rch);
//	}
	return 0;
}

void createHuffmanCode(HuffmanTree HT, int n) {
	//为每个字符进行哈夫曼编码并输出
	char cd[n];							//分配每个字符的哈夫曼编码的字符空间
	cd[n - 1] = '\0';
	int code, parent, start;
	for (int i = 1; i <= n; i++) {		//逐个字符求哈夫曼编码
		for (int j = 0; j < (n - 1); j++) {
			cd[j] = '-';		//把cd字符数组补满
		}
		code = i;
		parent = HT[i].parent;
		start = n - 1;
		while (parent != 0) {			//从叶子结点向上回溯 直到根结点
			start--;					//每回溯一次 从后往前写入一次cd[start]
			if (HT[parent].lch == code) {
				cd[start] = '0';		//左0右1
			} else {
				cd[start] = '1';
			}
			code = parent;				//继续往上回溯
			parent = HT[parent].parent;
		}
		printf("%s\n", cd);
	}
}

void createHuffmanTree(HuffmanTree HT, int n) {		//n为叶子结点数
	int m = 2 * n - 1, s1, s2;
//	HT = (HTNode*)malloc(sizeof(HTNode[m+1]));
	for (int i = 1; i <= m; i++) {
		if (i <= n) {
			int weight;
			printf("输入权重:");
			scanf("%d", &weight);
			HT[i].weight = weight;			//初始化权重
		}
		HT[i].parent = HT[i].lch = HT[i].rch = 0;//初始化双亲和左右孩子结点
	}
	for (int i = n + 1; i <= m; i++) {
		selectMin(HT, i - 1, &s1, &s2);		//取出双亲为0权重小的两个做孩子结点
		HT[s1].parent = HT[s2].parent = i;	//创建双亲结点结点
		HT[i].lch = s1;
		HT[i].rch = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
}

void selectMin(HuffmanTree HT, int n, int *s1, int *s2) {
	//求权值的最小值
	for (int i = 1; i <= n; i++) {		//循环i只执行一次
		if (HT[i].parent == 0) {
			for (int j = 1; j <= n; j++) {
				if (HT[j].parent == 0) {
					if (HT[i].weight < HT[j].weight)
						*s1 = i;
					else {
						*s1 = j;
						i = j;			//因为循环i只进行一次
					}
				}
			}
			break;
		}
	}
	//求权值的次小值
	for (int i = 1; i <= n; i++) {
		if (HT[i].parent == 0 && i != *s1) {
			for (int j = 1; j <= n; j++) {
				if (HT[j].parent == 0 && j != *s1) {
					if (HT[i].weight < HT[j].weight)
						*s2 = i;
					else {
						*s2 = j;
						i = j;
					}
				}
			}
			break;
		}
	}
}






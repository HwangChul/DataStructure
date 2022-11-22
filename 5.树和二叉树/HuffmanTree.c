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
	//��ΰ��ַ�������ȥ
	char *code;
} HCNode, *HuffmanCode;

void createHuffmanTree(HuffmanTree HT, int n);			//������������
void selectMin(HuffmanTree HT, int n, int *s1, int *s2);//��Ȩֵ����Сֵ�ʹ�Сֵ
void createHuffmanCode(HuffmanTree HT, int n);			//����������

int main() {
	HuffmanTree HT;
	int n = 7;											//Ҷ�ӽ����
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
	//Ϊÿ���ַ����й��������벢���
	char cd[n];							//����ÿ���ַ��Ĺ�����������ַ��ռ�
	cd[n - 1] = '\0';
	int code, parent, start;
	for (int i = 1; i <= n; i++) {		//����ַ������������
		for (int j = 0; j < (n - 1); j++) {
			cd[j] = '-';		//��cd�ַ����鲹��
		}
		code = i;
		parent = HT[i].parent;
		start = n - 1;
		while (parent != 0) {			//��Ҷ�ӽ�����ϻ��� ֱ�������
			start--;					//ÿ����һ�� �Ӻ���ǰд��һ��cd[start]
			if (HT[parent].lch == code) {
				cd[start] = '0';		//��0��1
			} else {
				cd[start] = '1';
			}
			code = parent;				//�������ϻ���
			parent = HT[parent].parent;
		}
		printf("%s\n", cd);
	}
}

void createHuffmanTree(HuffmanTree HT, int n) {		//nΪҶ�ӽ����
	int m = 2 * n - 1, s1, s2;
//	HT = (HTNode*)malloc(sizeof(HTNode[m+1]));
	for (int i = 1; i <= m; i++) {
		if (i <= n) {
			int weight;
			printf("����Ȩ��:");
			scanf("%d", &weight);
			HT[i].weight = weight;			//��ʼ��Ȩ��
		}
		HT[i].parent = HT[i].lch = HT[i].rch = 0;//��ʼ��˫�׺����Һ��ӽ��
	}
	for (int i = n + 1; i <= m; i++) {
		selectMin(HT, i - 1, &s1, &s2);		//ȡ��˫��Ϊ0Ȩ��С�����������ӽ��
		HT[s1].parent = HT[s2].parent = i;	//����˫�׽����
		HT[i].lch = s1;
		HT[i].rch = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
}

void selectMin(HuffmanTree HT, int n, int *s1, int *s2) {
	//��Ȩֵ����Сֵ
	for (int i = 1; i <= n; i++) {		//ѭ��iִֻ��һ��
		if (HT[i].parent == 0) {
			for (int j = 1; j <= n; j++) {
				if (HT[j].parent == 0) {
					if (HT[i].weight < HT[j].weight)
						*s1 = i;
					else {
						*s1 = j;
						i = j;			//��Ϊѭ��iֻ����һ��
					}
				}
			}
			break;
		}
	}
	//��Ȩֵ�Ĵ�Сֵ
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






#include <stdio.h>
#include <stdlib.h>
#include "LinkBiTree.c"

#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW   -2

typedef int Status;
typedef int KeyType;

typedef struct {
	KeyType key;			//�ؼ�����
	char name[10];
	int score;
} ElemType;

typedef struct {			//˳���ṹ���Ͷ���
	ElemType *data;			//�����ַ
	int len;				//��
} SSTable;					//Sequential Search Table˳��������

int search_Seq(SSTable ST, KeyType key);	//�����ڱ���˳�����
int search_Bin(SSTable ST, KeyType key);	//���ֲ��ҷ����ǵݼ����У�
BiTree searchBST(BiTree T, KeyType key);	//��������������

int main() {
	SSTable ST;
	BiTree T;
	return 0;
}

BiTree searchBST(BiTree T, KeyType key) {	//��������������
	if ((!T) || T->data.n == key) {			//�ҵ�key������Ϊ�շ������ĵ�ַ
		return T;
	} else if (T->data.n < key) {
		searchBST(T->lchild, key);			//����������������
	} else {
		searchBST(T->rchild, key);			//����������������
	}
}//searchBST

int search_Seq(SSTable ST, KeyType key) {	//�����ڱ���˳�����
	ST.data[0].key = key;	//�ڱ�
	int i;
	for (i = ST.len; ST.data[i].key != key; i--);
	return i;
}//search_Seq

int search_Bin(SSTable ST, KeyType key) {	//���ֲ��ҷ����ǵݼ����У�
	int low = 1, high = ST.len;				//�������ֵ
	while (low <= high) {
		int mid = (low + high) / 2;
		if (key == ST.data[mid].key) {		//�ҵ�����Ԫ��
			return mid;
		} else if (key < ST.data[mid].key) {	//��С��������
			high = mid - 1;					//��ǰ�������������
		} else {
			low = mid + 1;					//�ں�������������
		}
	}
	return 0;								//˳����в����ڴ���Ԫ��
}//search_Bin







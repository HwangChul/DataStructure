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
	KeyType key;			//关键字域
	char name[10];
	int score;
} ElemType;

typedef struct {			//顺序表结构类型定义
	ElemType *data;			//表基地址
	int len;				//表长
} SSTable;					//Sequential Search Table顺序搜索表

int search_Seq(SSTable ST, KeyType key);	//设置哨兵的顺序查找
int search_Bin(SSTable ST, KeyType key);	//二分查找法（非递减序列）
BiTree searchBST(BiTree T, KeyType key);	//二叉排序树搜索

int main() {
	SSTable ST;
	BiTree T;
	return 0;
}

BiTree searchBST(BiTree T, KeyType key) {	//二叉排序树搜索
	if ((!T) || T->data.n == key) {			//找到key或者树为空返回树的地址
		return T;
	} else if (T->data.n < key) {
		searchBST(T->lchild, key);			//在左子树继续查找
	} else {
		searchBST(T->rchild, key);			//在右子树继续查找
	}
}//searchBST

int search_Seq(SSTable ST, KeyType key) {	//设置哨兵的顺序查找
	ST.data[0].key = key;	//哨兵
	int i;
	for (i = ST.len; ST.data[i].key != key; i--);
	return i;
}//search_Seq

int search_Bin(SSTable ST, KeyType key) {	//二分查找法（非递减序列）
	int low = 1, high = ST.len;				//置区间初值
	while (low <= high) {
		int mid = (low + high) / 2;
		if (key == ST.data[mid].key) {		//找到待查元素
			return mid;
		} else if (key < ST.data[mid].key) {	//缩小待查区间
			high = mid - 1;					//在前半区间继续查找
		} else {
			low = mid + 1;					//在后半区间继续查找
		}
	}
	return 0;								//顺序表中不存在待查元素
}//search_Bin







#include <stdio.h>
#include <stdlib.h>

//函数结果状态代码
#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define INFEASIBLE -1 	//infeasible
#define OVERFLOW   -2
#define MAXSIZE    20

typedef int KeyType;		//关键字类型为int型
typedef int Status;

typedef struct {
	KeyType key;			//关键字
	int info;				//其他数据项
} RedType;					//Record Type

typedef struct {
	RedType r[MAXSIZE + 1];	//r[0]一般作为哨兵或者缓冲区
	int len;				//顺序表的长度
} SqList;

void insertSort(SqList *L);						//直接插入排序
void bInsertSort(SqList *L);					//折半插入排序
void shellSort(SqList *L, int *dt, int t);		//希尔排序
void shellInsert(SqList *L, int dk);			//希尔排序中进行增量为dk的希尔插入
void bubbleSort(SqList *L);						//冒泡排序
void QuickSort(SqList *L, int low, int high);	//快速排序
int partition(SqList *L, int low, int high);	//快排中根据中心点大小分割成左右两块
void selectSort(SqList *L);						//简单选择排序
void mergeSort(SqList *R, SqList *T, int low, int high, SqList *S);	//归并排序
void merge(SqList R, SqList *T, int low, int mid, int high);		//归并
void heapSort(SqList *L);						//堆排序
void heapAdjust(SqList *L, int k, int end);		//堆调整（大根堆）
void display(SqList L);

int main() {
	SqList L;
	int n = 13;
	int list[13] = {81, 94, 11, 96, 12, 35, 17, 95, 28, 58, 41, 75, 15};
	for (int i = 1; i < n + 1; i++) {
		L.r[i].key = list[i - 1];
	}
	L.len = n;
	display(L);

//	int dt[3] = {1, 3, 7};		//希尔排序的增量序列
//	shellSort(&L, dt, 3);
//	bubbleSort(&L);
//	QuickSort(&L, 1, L.len);
//	selectSort(&L);
//	SqList S;					//归并排序的辅助空间
//	mergeSort(&L, &L, 1, L.len, &S);
	heapSort(&L);
	display(L);
	return 0;
}

void heapSort(SqList *L) {						//堆排序
	for (int i = L->len / 2; i >= 1; i--) {		//建立大根堆
		heapAdjust(L, i, L->len);
	}

	for (int i = L->len; i > 1; i--) {
		L->r[0] = L->r[1];						//将堆顶(最大)元素与 L 中的最后一个元素交换
		L->r[1] = L->r[i];
		L->r[i] = L->r[0];
		heapAdjust(L, 1, i - 1);				//将交换后的 L 进行堆调整 每一次end都往前一位
		//除根结点外都符合大根堆 所以可以从第一位开始调整
	}
}

void heapAdjust(SqList *L, int k, int end) {	//堆调整（大根堆）
	//要筛选的结点编号为k，最后一个结点为end
	int i = k, j = 2 * i;						//完全二叉树中k的左右孩子结点为2k & 2k+1
	while (j <= end) {							//当叶子结点的编号还在树中
		if (j < end && L->r[j].key < L->r[j + 1].key) {	//叶子结点j没有出界 且右孩子大于左孩子时用右孩子和根节点比较
			j++;
		}
		if (L->r[i].key < L->r[j].key) {		//当根节点小于左右孩子时 不符合大根堆定义 进行交换
			L->r[0] = L->r[i];
			L->r[i] = L->r[j];
			L->r[j] = L->r[0];
		}
		i = j;									//沿着交换后的孩子结点检查是否是大根堆
		j = i * 2;
	}
}

void mergeSort(SqList *R, SqList *T, int low, int high, SqList *S) {//归并排序
	//S为辅助空间 存放分治后的元素，T为归并排序后元素的存储空间
	//第一次递归后T就指向了S，在对S中的两个子序列归并到T后
	//此时已经排好成的一组子序列在T(等同于S)中 即辅助空间S[low, high]中为已经排好的元素
	//等递归结束 到最初的函数调用时 T指向要排序的序列 S为两组有序序列
	if (low == high) {
		S->r[low] = R->r[low];
	} else {
		int mid = (low + high) / 2;				//将序列一分为二 求出分裂点mid
		mergeSort(R, S, low, mid, S);			//对子序列R[low, mid]递归归并排序 结果放入S[low, mid]
		mergeSort(R, S, mid + 1, high, S);		//对子序列R[mid+1, high]递归归并排序 结果放入S[mid+1, high]
		merge(*S, T, low, mid, high);			//将S[low, mid]和S[mid+1, high]归并到T[low, high]
	}
}

void merge(SqList S, SqList *T, int low, int mid, int high) {		//归并
	//将有序S[low, mid]和R[mid+1, high]归并为有序表[low, high]
	int i = low, j = mid + 1, k = low;

	while (i <= mid && j <= high) {
		if (S.r[i].key <= S.r[j].key) {			//将S中的记录从小到大并入T中
			T->r[k++] = S.r[i++];
		} else {
			T->r[k++] = S.r[j++];
		}
	}
	while (i <= mid ) {
		T->r[k++] = S.r[i++];				//将剩余的S[i, mid]复制到T中
	}
	while (j <= high ) {
		T->r[k++] = S.r[j++];				//将剩余的S[j, high]复制到T中
	}
}

void selectSort(SqList *L) {				//简单选择排序
	for (int i = 1; i <= L->len; i++) {		//从第一个元素开始选择 依次往后
		int k = i;
		L->r[0] = L->r[i];
		for (int j = i + 1; j <= L->len; j++) {
			if (L->r[k].key >= L->r[j].key) {
				k = j;						//记录最小值的位置
			}
		}
		if (k != i) {						//交换
			L->r[i] = L->r[k];
			L->r[k] = L->r[0];
		}
	}
}

void QuickSort(SqList *L, int low, int high) {	//快速排序
	int pivot;								//中心点
	if (low < high) {						//当low == high 每块只有一个元素时结束
		pivot = partition(L, low, high);	//取得中心点下标 左边比中心点小 右边大
		QuickSort(L, low, pivot - 1);			//对左边进行快排
		QuickSort(L, pivot + 1, high);			//对右边进行快排
	}
}

int partition(SqList *L, int low, int high) {//分治 快排中根据中心点大小分割成左右两块
	L->r[0] = L->r[low];					//哨兵
	int pivot_key = L->r[low].key;			//取得中心点的key 进行比较交换
	while (low < high) {					//从表两端交替向中间扫描
		for (; (low < high) && (L->r[high].key >= pivot_key); high--);
		L->r[low] = L->r[high];				//将比中心点小的元素移到low
		for (; (low < high) && (L->r[low].key <= pivot_key); low++);
		L->r[high] = L->r[low];				//将比中心点大的元素移到high
	}
	L->r[low] = L->r[0];					//中心点归位
	return low;								//返回中心点下标
}

void bubbleSort(SqList *L) {				//冒泡排序
	int n = L->len, flag = 1;				//flag标记某一次排序是否发生交换
	for (int m = 1; (m < n) && (flag == 1); m++) {	//总共需要m(n - 1)次
		flag = 0;							//flag置为0 如果本次没有发生交换则代表排序已经完成 跳出循环
		for (int j = 1; j <= n - m; j++) {	//每次排序j(n - m)个元素
			if (L->r[j].key > L->r[j + 1].key) {
				flag = 1;					//flag置为1 表示发生交换 正常进行下一次排序
				L->r[0] = L->r[j];			//交换元素
				L->r[j] = L->r[j + 1];
				L->r[j + 1] = L->r[0];
			}
		}//for j
	}//for m
}

void shellSort(SqList *L, int *dt, int t) {	//按增量序列dt[]对L做t次希尔插入排序
	for (int i = t - 1; i >= 0; i--) {		//i每次减1而不是减dk 不然最后dk为1时需要后移的次数太多
		shellInsert(L, dt[i]);				//一次增量为dt[i]的希尔插入排序
	}
}

void shellInsert(SqList *L, int dk) {		//对L做一次增量为dk的希尔插入排序
	int i, j;
	for (i = dk + 1; i <= L->len; i += dk) {
		if (L->r[i - dk].key > L->r[i].key) {	//如果前dk位比后dk位小则不需要排序
			L->r[0] = L->r[i];				//复制为哨兵
			for (j = i - dk; j > 0 && L->r[0].key < L->r[j].key; j -= dk) {
				L->r[j + dk] = L->r[j];		//元素后移
			}
			L->r[j + dk] = L->r[0];			//插入到正确位置
		}//if
	}//for i
}//shellInsert

void insertSort(SqList *L) {	//直接插入排序
	int i, j;
	for (i = 2; i <= L->len; i++) {			//第一次for循环遍历元素
		if (L->r[i - 1].key > L->r[i].key) {//如果前一位比后一位小则不需要排序
			L->r[0] = L->r[i];				//复制为哨兵
			for (j = i - 1; j > 0 && L->r[0].key < L->r[j].key; j--) {//第二次for循环交换位置
				L->r[j + 1] = L->r[j];		//元素后移
			}
			L->r[j + 1] = L->r[0];			//插入到正确位置
		}//if
	}//for i
}//insertSort

void bInsertSort(SqList *L) {	//折半插入排序
	int i, j, low, mid, high;
	for (i = 2; i <= L->len; i++) {
		if (L->r[i - 1].key > L->r[i].key) {//如果前一位比后一位小则不需要排序
			L->r[0] = L->r[i];	//复制为哨兵
			low = 1;			//二分查找法寻找插入位置
			high = i - 1;
			while (low <= high) {
				mid = (low + high) / 2;
				if (L->r[0].key < L->r[mid].key) {
					high = mid - 1;
				} else {
					low = mid + 1;
				}
			}//while					//循环结束 high+1为插入位置
			for (j = i - 1; j >= high + 1; j--) {
				L->r[j + 1] = L->r[j];	//移动元素
			}
			L->r[high + 1] = L->r[0];	//插入到正确的位置
		}//if
	}//for i
}//bInsertSort

void display(SqList L) {
	for (int i = 1; i < L.len + 1; i++) {
		printf("%d ", L.r[i].key);
	}
	printf("\n");
}







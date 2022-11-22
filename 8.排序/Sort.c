#include <stdio.h>
#include <stdlib.h>

//�������״̬����
#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define INFEASIBLE -1 	//infeasible
#define OVERFLOW   -2
#define MAXSIZE    20

typedef int KeyType;		//�ؼ�������Ϊint��
typedef int Status;

typedef struct {
	KeyType key;			//�ؼ���
	int info;				//����������
} RedType;					//Record Type

typedef struct {
	RedType r[MAXSIZE + 1];	//r[0]һ����Ϊ�ڱ����߻�����
	int len;				//˳���ĳ���
} SqList;

void insertSort(SqList *L);						//ֱ�Ӳ�������
void bInsertSort(SqList *L);					//�۰��������
void shellSort(SqList *L, int *dt, int t);		//ϣ������
void shellInsert(SqList *L, int dk);			//ϣ�������н�������Ϊdk��ϣ������
void bubbleSort(SqList *L);						//ð������
void QuickSort(SqList *L, int low, int high);	//��������
int partition(SqList *L, int low, int high);	//�����и������ĵ��С�ָ����������
void selectSort(SqList *L);						//��ѡ������
void mergeSort(SqList *R, SqList *T, int low, int high, SqList *S);	//�鲢����
void merge(SqList R, SqList *T, int low, int mid, int high);		//�鲢
void heapSort(SqList *L);						//������
void heapAdjust(SqList *L, int k, int end);		//�ѵ���������ѣ�
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

//	int dt[3] = {1, 3, 7};		//ϣ���������������
//	shellSort(&L, dt, 3);
//	bubbleSort(&L);
//	QuickSort(&L, 1, L.len);
//	selectSort(&L);
//	SqList S;					//�鲢����ĸ����ռ�
//	mergeSort(&L, &L, 1, L.len, &S);
	heapSort(&L);
	display(L);
	return 0;
}

void heapSort(SqList *L) {						//������
	for (int i = L->len / 2; i >= 1; i--) {		//���������
		heapAdjust(L, i, L->len);
	}

	for (int i = L->len; i > 1; i--) {
		L->r[0] = L->r[1];						//���Ѷ�(���)Ԫ���� L �е����һ��Ԫ�ؽ���
		L->r[1] = L->r[i];
		L->r[i] = L->r[0];
		heapAdjust(L, 1, i - 1);				//��������� L ���жѵ��� ÿһ��end����ǰһλ
		//��������ⶼ���ϴ���� ���Կ��Դӵ�һλ��ʼ����
	}
}

void heapAdjust(SqList *L, int k, int end) {	//�ѵ���������ѣ�
	//Ҫɸѡ�Ľ����Ϊk�����һ�����Ϊend
	int i = k, j = 2 * i;						//��ȫ��������k�����Һ��ӽ��Ϊ2k & 2k+1
	while (j <= end) {							//��Ҷ�ӽ��ı�Ż�������
		if (j < end && L->r[j].key < L->r[j + 1].key) {	//Ҷ�ӽ��jû�г��� ���Һ��Ӵ�������ʱ���Һ��Ӻ͸��ڵ�Ƚ�
			j++;
		}
		if (L->r[i].key < L->r[j].key) {		//�����ڵ�С�����Һ���ʱ �����ϴ���Ѷ��� ���н���
			L->r[0] = L->r[i];
			L->r[i] = L->r[j];
			L->r[j] = L->r[0];
		}
		i = j;									//���Ž�����ĺ��ӽ�����Ƿ��Ǵ����
		j = i * 2;
	}
}

void mergeSort(SqList *R, SqList *T, int low, int high, SqList *S) {//�鲢����
	//SΪ�����ռ� ��ŷ��κ��Ԫ�أ�TΪ�鲢�����Ԫ�صĴ洢�ռ�
	//��һ�εݹ��T��ָ����S���ڶ�S�е����������й鲢��T��
	//��ʱ�Ѿ��źóɵ�һ����������T(��ͬ��S)�� �������ռ�S[low, high]��Ϊ�Ѿ��źõ�Ԫ��
	//�ȵݹ���� ������ĺ�������ʱ Tָ��Ҫ��������� SΪ������������
	if (low == high) {
		S->r[low] = R->r[low];
	} else {
		int mid = (low + high) / 2;				//������һ��Ϊ�� ������ѵ�mid
		mergeSort(R, S, low, mid, S);			//��������R[low, mid]�ݹ�鲢���� �������S[low, mid]
		mergeSort(R, S, mid + 1, high, S);		//��������R[mid+1, high]�ݹ�鲢���� �������S[mid+1, high]
		merge(*S, T, low, mid, high);			//��S[low, mid]��S[mid+1, high]�鲢��T[low, high]
	}
}

void merge(SqList S, SqList *T, int low, int mid, int high) {		//�鲢
	//������S[low, mid]��R[mid+1, high]�鲢Ϊ�����[low, high]
	int i = low, j = mid + 1, k = low;

	while (i <= mid && j <= high) {
		if (S.r[i].key <= S.r[j].key) {			//��S�еļ�¼��С������T��
			T->r[k++] = S.r[i++];
		} else {
			T->r[k++] = S.r[j++];
		}
	}
	while (i <= mid ) {
		T->r[k++] = S.r[i++];				//��ʣ���S[i, mid]���Ƶ�T��
	}
	while (j <= high ) {
		T->r[k++] = S.r[j++];				//��ʣ���S[j, high]���Ƶ�T��
	}
}

void selectSort(SqList *L) {				//��ѡ������
	for (int i = 1; i <= L->len; i++) {		//�ӵ�һ��Ԫ�ؿ�ʼѡ�� ��������
		int k = i;
		L->r[0] = L->r[i];
		for (int j = i + 1; j <= L->len; j++) {
			if (L->r[k].key >= L->r[j].key) {
				k = j;						//��¼��Сֵ��λ��
			}
		}
		if (k != i) {						//����
			L->r[i] = L->r[k];
			L->r[k] = L->r[0];
		}
	}
}

void QuickSort(SqList *L, int low, int high) {	//��������
	int pivot;								//���ĵ�
	if (low < high) {						//��low == high ÿ��ֻ��һ��Ԫ��ʱ����
		pivot = partition(L, low, high);	//ȡ�����ĵ��±� ��߱����ĵ�С �ұߴ�
		QuickSort(L, low, pivot - 1);			//����߽��п���
		QuickSort(L, pivot + 1, high);			//���ұ߽��п���
	}
}

int partition(SqList *L, int low, int high) {//���� �����и������ĵ��С�ָ����������
	L->r[0] = L->r[low];					//�ڱ�
	int pivot_key = L->r[low].key;			//ȡ�����ĵ��key ���бȽϽ���
	while (low < high) {					//�ӱ����˽������м�ɨ��
		for (; (low < high) && (L->r[high].key >= pivot_key); high--);
		L->r[low] = L->r[high];				//�������ĵ�С��Ԫ���Ƶ�low
		for (; (low < high) && (L->r[low].key <= pivot_key); low++);
		L->r[high] = L->r[low];				//�������ĵ���Ԫ���Ƶ�high
	}
	L->r[low] = L->r[0];					//���ĵ��λ
	return low;								//�������ĵ��±�
}

void bubbleSort(SqList *L) {				//ð������
	int n = L->len, flag = 1;				//flag���ĳһ�������Ƿ�������
	for (int m = 1; (m < n) && (flag == 1); m++) {	//�ܹ���Ҫm(n - 1)��
		flag = 0;							//flag��Ϊ0 �������û�з�����������������Ѿ���� ����ѭ��
		for (int j = 1; j <= n - m; j++) {	//ÿ������j(n - m)��Ԫ��
			if (L->r[j].key > L->r[j + 1].key) {
				flag = 1;					//flag��Ϊ1 ��ʾ�������� ����������һ������
				L->r[0] = L->r[j];			//����Ԫ��
				L->r[j] = L->r[j + 1];
				L->r[j + 1] = L->r[0];
			}
		}//for j
	}//for m
}

void shellSort(SqList *L, int *dt, int t) {	//����������dt[]��L��t��ϣ����������
	for (int i = t - 1; i >= 0; i--) {		//iÿ�μ�1�����Ǽ�dk ��Ȼ���dkΪ1ʱ��Ҫ���ƵĴ���̫��
		shellInsert(L, dt[i]);				//һ������Ϊdt[i]��ϣ����������
	}
}

void shellInsert(SqList *L, int dk) {		//��L��һ������Ϊdk��ϣ����������
	int i, j;
	for (i = dk + 1; i <= L->len; i += dk) {
		if (L->r[i - dk].key > L->r[i].key) {	//���ǰdkλ�Ⱥ�dkλС����Ҫ����
			L->r[0] = L->r[i];				//����Ϊ�ڱ�
			for (j = i - dk; j > 0 && L->r[0].key < L->r[j].key; j -= dk) {
				L->r[j + dk] = L->r[j];		//Ԫ�غ���
			}
			L->r[j + dk] = L->r[0];			//���뵽��ȷλ��
		}//if
	}//for i
}//shellInsert

void insertSort(SqList *L) {	//ֱ�Ӳ�������
	int i, j;
	for (i = 2; i <= L->len; i++) {			//��һ��forѭ������Ԫ��
		if (L->r[i - 1].key > L->r[i].key) {//���ǰһλ�Ⱥ�һλС����Ҫ����
			L->r[0] = L->r[i];				//����Ϊ�ڱ�
			for (j = i - 1; j > 0 && L->r[0].key < L->r[j].key; j--) {//�ڶ���forѭ������λ��
				L->r[j + 1] = L->r[j];		//Ԫ�غ���
			}
			L->r[j + 1] = L->r[0];			//���뵽��ȷλ��
		}//if
	}//for i
}//insertSort

void bInsertSort(SqList *L) {	//�۰��������
	int i, j, low, mid, high;
	for (i = 2; i <= L->len; i++) {
		if (L->r[i - 1].key > L->r[i].key) {//���ǰһλ�Ⱥ�һλС����Ҫ����
			L->r[0] = L->r[i];	//����Ϊ�ڱ�
			low = 1;			//���ֲ��ҷ�Ѱ�Ҳ���λ��
			high = i - 1;
			while (low <= high) {
				mid = (low + high) / 2;
				if (L->r[0].key < L->r[mid].key) {
					high = mid - 1;
				} else {
					low = mid + 1;
				}
			}//while					//ѭ������ high+1Ϊ����λ��
			for (j = i - 1; j >= high + 1; j--) {
				L->r[j + 1] = L->r[j];	//�ƶ�Ԫ��
			}
			L->r[high + 1] = L->r[0];	//���뵽��ȷ��λ��
		}//if
	}//for i
}//bInsertSort

void display(SqList L) {
	for (int i = 1; i < L.len + 1; i++) {
		printf("%d ", L.r[i].key);
	}
	printf("\n");
}







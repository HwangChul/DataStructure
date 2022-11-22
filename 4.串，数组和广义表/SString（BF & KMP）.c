#include <stdio.h>
#include <stdlib.h>

//�������״̬����
#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define INFEASIBLE -1 // infeasible
#define OVERFLOW   -2
#define MAXSIZE    255

//Status�Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int Status;

typedef struct {
	char ch[MAXSIZE + 1];//�洢����һά����
	int len;//����ǰ�ĳ���
} SString;

int index_BF(SString S, SString T, int pos);
Status enSString(SString *S, char *s, int len);
void getNext(SString S, int *next);
void getNextval(SString S, int *next, int *nextval);
int index_KMP(SString S, SString T, int pos, int *next);
void get_nextval(SString S, int *nextval);

int main() {
	SString S, T;
	char s[] = {' ', 'a', 'a', 'a', 'b', 'a', 'a', 'a', 'a', 'b', 'c'};
	char t[] = {' ', 'a', 'a', 'a', 'a', 'b'};
//	char s[] = {' ', 'a', 'c', 'b', 'a', 'b', 'a', 'a', 'b', 'c', 'a', 'c', 'a'};
//	char t[] = {' ', 'a', 'b', 'a', 'a', 'b', 'c', 'a', 'c'};
	enSString(&S, s, sizeof(s));
	enSString(&T, t, sizeof(t));
//	printf("%d\n", index_BF(S, T, 1));
//	int next[sizeof(t)], nextval[sizeof(t)];
//	getNext(T, next);
//	getNextval(T, next, nextval);
	int nextval[sizeof(t)];
	get_nextval(T, nextval);
	printf("%d\n", index_KMP(S, T, 1, nextval));
	int chLen = sizeof(t) / sizeof(char);
	for (int i = 0; i < chLen; i++) {
		printf("%d\t", nextval[i]);
	}
	return 0;
}

int index_KMP(SString S, SString T, int pos, int *next) {
	int i = pos, j = 1;
	while (i < S.len && j < T.len) {
		//j==0��������ģʽ����һ���ַ���ƥ���next[1]=0,����i++,j++
		if (j == 0 || S.ch[i] == T.ch[j]) {
			i++;			//������ģʽ������ƥ����һ���ַ�
			j++;
		} else {
			j = next[j];	//i���� j���˵�����λ��
		}
	}
	//ƥ�����ʱ j�����
	if (j >= T.len) {
		//++i����Ϊ��ʱi�ں�ģʽ��ƥ������һλ����һλ��ȥģʽ���ĳ���
		//���ĵ�һλû��Ԫ��
		return ++i - T.len;	//ƥ��ɹ����ص�һ���ַ����±�
	} else {
		return 0;
	}
}

void get_nextval(SString S, int *nextval) {
	int next[S.len];
	nextval[1] = next[1] = 0;
	int i = 1, j = 0, n_j = 2;
	while (i < S.len) {
		if (j == 0 || S.ch[i] == S.ch[j]) {
			next[++i] = ++j;
			//�������һλnext֮��ֱ������Ӧ��nextval
			if (S.ch[n_j] != S.ch[next[n_j]]) {
				nextval[n_j] = next[n_j];
				n_j++;
			} else {
				nextval[n_j] = nextval[next[n_j]];
				n_j++;
			}
		} else {
			j = next[j];
		}
	}
}

void getNextval(SString S, int *next, int *nextval) {
	nextval[1] = 0;
	int j = 2;
	while (j < S.len) {
		//��nextval��������㷨
		if (S.ch[j] != S.ch[next[j]]) {
			nextval[j] = next[j];
			j++;
		} else {
			nextval[j] = nextval[next[j]];
			j++;
		}
	}
}

void getNext(SString S, int *next) {
	//KMP�㷨����
	/*
	next[j+1]�����ֵΪnext[j]+1;
	��next[j]=K1, ����P(1)-P(K1-1)=P(J-K1+1)-P(J-1) (ǰK1-1λ�ַ��ͺ�K1-1λ�ַ��غ�)
	���P(J)=P(K1)������P(1)-P(K1-1)P(K1)=P(J-K1+1)-P(J-1)P(J) ��next[J+1]=next[J]+1=K1+1
	����next[K1]=K2,����P(1)-P(K2-1)=   P(K1-K2+1)-P(K1-1)=P(J-K1+1)-P(K2-K1+J-1)  =P(J-K2+1)-P(J-1)
	����һ����еĵ�һС�ε��ڵڶ�����еĵڶ�С��,��ʱ���P(J)=P(K2)��next[J+1]=next[next[J]]+1=next[K1]+1=K2+1
	�������Դ�����
	���P(J)!=P(I)��ônext[J+1]���ܵĴδ�ֵΪnext[next[J]]+1
	���P(I)!=P(J)ֻ����J=next[J],��ȻK1��ֵ���� next����ֵÿ���������1
	*/
	next[1] = 0;
	int i = 1, j = 0;
	while (i < S.len) {
		if (j == 0 || S.ch[i] == S.ch[j]) {
			next[++i] = ++j;
		} else {
			j = next[j];
		}
	}
}

int index_BF(SString S, SString T, int pos) {
	int i = pos, j = 1;
	while (i < S.len && j < T.len) {
		if (S.ch[i] == T.ch[j]) {
			++i;			//������ģʽ������ƥ����һ���ַ�
			++j;
		} else {
			i = (i - j + 1) + 1; //���� ��������S�±�+1
			j = 1;			//����
		}
	}
	//ƥ�����ʱ j�����
	if (j >= T.len) {
		//++i����Ϊ��ʱi�ں�ģʽ��ƥ������һλ����һλ��ȥģʽ���ĳ���
		//���ĵ�һλû��Ԫ��
		return ++i - T.len;	//ƥ��ɹ����ص�һ���ַ����±�
	} else {
		return 0;
	}
}

Status enSString(SString *S, char *s, int len) {
	for (int i = 0; i < len; i++ ) {
		S->ch[i] = s[i];
	}
	S->len = len;
	return OK;
}


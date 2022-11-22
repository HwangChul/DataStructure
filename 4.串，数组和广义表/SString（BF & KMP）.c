#include <stdio.h>
#include <stdlib.h>

//函数结果状态代码
#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define INFEASIBLE -1 // infeasible
#define OVERFLOW   -2
#define MAXSIZE    255

//Status是函数的类型，其值是函数结果状态代码
typedef int Status;

typedef struct {
	char ch[MAXSIZE + 1];//存储串的一维数组
	int len;//串当前的长度
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
		//j==0是主串和模式串第一个字符不匹配而next[1]=0,所以i++,j++
		if (j == 0 || S.ch[i] == T.ch[j]) {
			i++;			//主串和模式串依次匹配下一个字符
			j++;
		} else {
			j = next[j];	//i不变 j后退到合适位置
		}
	}
	//匹配完成时 j会溢出
	if (j >= T.len) {
		//++i是因为此时i在和模式串匹配的最后一位后移一位减去模式串的长度
		//串的第一位没有元素
		return ++i - T.len;	//匹配成功返回第一个字符的下标
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
			//当求出来一位next之后直接求相应的nextval
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
		//求nextval数组核心算法
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
	//KMP算法核心
	/*
	next[j+1]的最大值为next[j]+1;
	设next[j]=K1, 则有P(1)-P(K1-1)=P(J-K1+1)-P(J-1) (前K1-1位字符和后K1-1位字符重合)
	如果P(J)=P(K1)，则有P(1)-P(K1-1)P(K1)=P(J-K1+1)-P(J-1)P(J) 则next[J+1]=next[J]+1=K1+1
	否则next[K1]=K2,则有P(1)-P(K2-1)=   P(K1-K2+1)-P(K1-1)=P(J-K1+1)-P(K2-K1+J-1)  =P(J-K2+1)-P(J-1)
	即第一大段中的第一小段等于第二大段中的第二小段,此时如果P(J)=P(K2)则next[J+1]=next[next[J]]+1=next[K1]+1=K2+1
	否则再以此类推
	如果P(J)!=P(I)那么next[J+1]可能的次大值为next[next[J]]+1
	如果P(I)!=P(J)只可让J=next[J],不然K1的值不对 next数组值每次最大增加1
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
			++i;			//主串和模式串依次匹配下一个字符
			++j;
		} else {
			i = (i - j + 1) + 1; //回溯 并且主串S下标+1
			j = 1;			//回溯
		}
	}
	//匹配完成时 j会溢出
	if (j >= T.len) {
		//++i是因为此时i在和模式串匹配的最后一位后移一位减去模式串的长度
		//串的第一位没有元素
		return ++i - T.len;	//匹配成功返回第一个字符的下标
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


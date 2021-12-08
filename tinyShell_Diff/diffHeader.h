#pragma once
#ifndef _HEADER_H_
#define _HEADER_H_
#include <iostream>
#include <fstream>
#include <cstring>
#include <stack>
#include <string>
using namespace std;
#define MAXLINE 512
#define MAXFILE 32768
#define MAX_LINE_LENGTH 4096
#define MAX_LINE_COUNT 16384
//�ṹ������
struct Terminal {
	char user[MAXLINE]; // �û���
	char mach[MAXLINE]; // �������
	char root[MAXLINE]; // ��Ŀ¼
	char wdir[MAXLINE]; // ����Ŀ¼
	char strin[MAXFILE]; // �ض����׼����
	char strout[MAXFILE]; // �ض����׼���
};
struct LineRelation {
	int x;
	int y;
	char op;
};//�����庯���жϵó����м��ϵ
struct diffios
{
	bool st = 1;//�Ƿ�Ϊ��׼���
	bool ud = 0;//�Ƿ���Դ�Сд
	bool lb = 0;//�Ƿ������ĩ�ո�
	bool wb = 0;//�Ƿ�������пո�
	bool bl = 0;//�Ƿ���Կ���
	bool qk = 0;//�Ƿ�ֻ��ʾ���޲�ͬ
	bool I = 0;//�Ƿ�ָ���ض��ַ���
	string target;
};//diff���������ʽ�ķ�װ
//ȫ�ֱ�������
extern Terminal gTerm;
//��������
int readFileByLine(ifstream*, char**);
int readStrinByLine(char**);
int customStrcmp(char*, char*, diffios);
int doDiff(int, char* []);
bool printResult(stack<LineRelation>, char**, char**, int, int, diffios);
#endif
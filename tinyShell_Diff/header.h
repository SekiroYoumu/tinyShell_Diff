#pragma once
#pragma comment(linker, "/STACK:1048576")
#ifndef _HEADER_H_
#define _HEADER_H_
#include <iostream>
#include <fstream>
#include <cstring>
#include <stack>
#include <string>
using namespace std;
#define MAXLINE 512
#define MAXFILE 16384
#define MAX_LINE_LENGTH 2048
#define MAX_LINE_COUNT 4096
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
};
extern Terminal gTerm;
extern bool diffSt; //�Ƿ�Ϊ��׼���
extern bool diffIgnoreUd;//�Ƿ���Դ�Сд
extern bool diffIgnoreLb;//�Ƿ������ĩ�ո�
extern bool diffIgnoreWb;//�Ƿ�������пո�
extern bool diffIgnoreBl;//�Ƿ���Կ���
extern bool diffQuick;//�Ƿ�ֻ��ʾ���޲�ͬ

int readFileByLine(ifstream*, char**);
int readStrinByLine(char**);
int customStrcmp(char*, char*, bool, bool, bool, bool);
int doDiff(int, char* []);
void printResult(stack<LineRelation>, char**, char**, int, int,bool);
#endif
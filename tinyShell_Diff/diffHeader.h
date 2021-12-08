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
#define MAX_LINE_COUNT 8192

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
	bool st;//�Ƿ�Ϊ��׼���
	bool ud;//�Ƿ���Դ�Сд
	bool lb;//�Ƿ������ĩ�ո�
	bool wb;//�Ƿ�������пո�
	bool bl;//�Ƿ���Կ���
	bool qk;//�Ƿ�ֻ��ʾ���޲�ͬ
	bool I;//�Ƿ�ָ���ض��ַ���
	string target;
};//diff���������ʽ�ķ�װ

extern Terminal gTerm;
int readFileByLine(ifstream*, char**);
int readStrinByLine(char**);
int customStrcmp(char*, char*,diffios);
int doDiff(int, char* []);
bool printResult(stack<LineRelation>, char**, char**, int, int,diffios);
#endif
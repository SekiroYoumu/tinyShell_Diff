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
#define MAXFILE 4096
#define MAX_LINE_LENGTH 1536
#define MAX_LINE_COUNT 1536
struct Terminal {
	char user[MAXLINE]; // �û���
	char mach[MAXLINE]; // �������
	char root[MAXLINE]; // ��Ŀ¼
	char wdir[MAXLINE]; // ����Ŀ¼
	char strin[MAXFILE]; // �ض����׼����
	char strout[MAXFILE]; // �ض����׼���
};
extern Terminal gTerm;
struct LineRelation {
	int x;
	int y;
	char op;
};
int readFileByLine(ifstream, char**);
int readStrinByLine(char**);
void copyPath(int*, int*, int);
int doDiff(int, char* []);
#endif
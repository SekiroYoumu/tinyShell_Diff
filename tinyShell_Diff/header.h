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

struct Terminal {
	char user[MAXLINE]; // �û���
	char mach[MAXLINE]; // �������
	char root[MAXLINE]; // ��Ŀ¼
	char wdir[MAXLINE]; // ����Ŀ¼
	char strin[MAXFILE]; // �ض����׼����
	char strout[MAXFILE]; // �ض����׼���
};
extern Terminal gTerm;

int readFileByLine(ifstream, char**);
void copyPath(int*, int*, int);
int doDiff(int, char* []);
#endif
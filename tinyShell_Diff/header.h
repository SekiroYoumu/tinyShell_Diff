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
	char user[MAXLINE]; // 用户名
	char mach[MAXLINE]; // 计算机名
	char root[MAXLINE]; // 根目录
	char wdir[MAXLINE]; // 工作目录
	char strin[MAXFILE]; // 重定向标准输入
	char strout[MAXFILE]; // 重定向标准输出
};
struct LineRelation {
	int x;
	int y;
	char op;
};
extern Terminal gTerm;
extern bool diffSt; //是否为标准输出
extern bool diffIgnoreUd;//是否忽略大小写
extern bool diffIgnoreLb;//是否忽略行末空格
extern bool diffIgnoreWb;//是否忽略所有空格
extern bool diffIgnoreBl;//是否忽略空行
extern bool diffQuick;//是否只显示有无不同

int readFileByLine(ifstream*, char**);
int readStrinByLine(char**);
int customStrcmp(char*, char*, bool, bool, bool, bool);
int doDiff(int, char* []);
void printResult(stack<LineRelation>, char**, char**, int, int,bool);
#endif
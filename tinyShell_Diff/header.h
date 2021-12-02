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
	char user[MAXLINE]; // 用户名
	char mach[MAXLINE]; // 计算机名
	char root[MAXLINE]; // 根目录
	char wdir[MAXLINE]; // 工作目录
	char strin[MAXFILE]; // 重定向标准输入
	char strout[MAXFILE]; // 重定向标准输出
};
extern Terminal gTerm;

int readFileByLine(ifstream, char**);
void copyPath(int*, int*, int);
int doDiff(int, char* []);
#endif
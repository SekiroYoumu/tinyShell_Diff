#pragma once
#include "header.h"
#define MAX_LINE_LENGTH 2048
#define MAX_LINE_COUNT 2048
void copyPath(int* a, int* b, int d)
{
	for (int i = -d; i <= d; i++)
	{
		b[i] = a[i];
	}
	return;
}//将路径暂存以备回溯
int readFileByLine(ifstream afile, char** a)
{
	int lineCount = 0;
	string tmp;
	a = new char* [MAX_LINE_COUNT];
	while (getline(afile, tmp))
	{
		a[lineCount] = new char[tmp.length()];
		strcpy_s(a[lineCount], tmp.length(), tmp.c_str());
		lineCount++;
	}
	return lineCount - 1;
}//按行读取文件，返回行数
int readStrinByLine(char** a)
{
	int lineCount = 0;
	char* tmp = new char[MAX_LINE_LENGTH];
	a = new char* [MAX_LINE_COUNT];
	char* ptr = gTerm.strin;
	while (*ptr != '\0')
	{
		int n = 0;
		memset(tmp, '\0', MAX_LINE_LENGTH * sizeof(char));
		while (*ptr != '\n' && n < MAX_LINE_LENGTH && *ptr != '\0')
		{
			tmp[n] = *ptr;
			n++; ptr++;
		}
		a[lineCount] = new char[strlen(tmp)];
		strcpy_s(a[lineCount],strlen(tmp),tmp);
		lineCount++;
	}
	delete[] tmp;
	return lineCount;
}//按行读取strin，返回行数
int doDiff(int argc, char* argv[])
{
	if (strcmp(argv[0], "diff") != 0)
	{
		cerr << "error:Wrong citation!" << endl;
		//return -1;
	}
	ifstream afile, bfile;
	/*afile.open(argv[argc - 2]);
	bfile.open(argv[argc-1]);*/
	char** aa=NULL;
	char** bb=NULL;
	int n, m;
	n = 7;
	m = 6;
	char* a = new char[n];
	char* b = new char[m];
	a = (char*)"ABCABBA";
	b = (char*)"CBABAC";
	int* v = new int[2 * (n + m) + 1];
	memset(v, 0, (2 * (n + m) + 1) * sizeof(int));
	v = &v[n + m];
	int x, y;
	int k, d;
	int** result = new int* [n + m];
	//1、SES计算
	for (d = 0; d <= n + m; d++)
	{
		result[d] = new int[2 * d + 1];
		memset(result[d], 0, (2 * d + 1) * sizeof(int));
		result[d] = &result[d][d];
		copyPath(v, result[d], d); //record path
		for (k = -d; k <= d; k += 2)
		{
			if (k == -d || (k != d and v[k - 1] < v[k + 1]))
				x = v[k + 1];
			else
				x = v[k - 1] + 1;
			y = x - k;
			while (x < n && y < m && a[x] == b[y])
			{
				x++;
				y++;
			}
			v[k] = x;
			if (x >= n && y >= m)
			{
				cout << "Now at " << d << " " << x << " " << y << " " << endl;
				goto loopend;
			}
		}
	}
loopend:;
	v = &v[-n - m];
	delete[] v;
	//2、回溯路线
	int last_x, last_y, last_k;
	stack<int> x_stack, y_stack;
	stack<char> oprands;
	for (; d >= 0; d--)
	{
		k = x - y;
		if (k == -d || (k != d && result[d][k - 1] < result[d][k + 1]))
		{
			last_k = k + 1; //表示这一步做了删除
		}
		else
		{
			last_k = k - 1; //表示这一步做了新增
		}
		last_x = result[d][last_k];
		last_y = last_x - last_k;
		if (d > 0)
		{
			while (last_x < x && last_y < y)
			{
				printf("(%d,%d)->(%d,%d),%d->%d,d=%d\n", x - 1, y - 1, x, y, k, k, d);
				x_stack.push(x);
				y_stack.push(y);
				oprands.push('=');
				x--;
				y--;
			}
			printf("(%d,%d)->(%d,%d),%d->%d,d=%d\n", last_x, last_y, x, y, last_k, k, d);
		}
		if (d > 0)
		{
			x_stack.push(x);
			y_stack.push(y);
			if (last_x == x)
				oprands.push('+');
			else if (last_y == y)
				oprands.push('-');
		}
		x = last_x;
		y = last_y;
		result[d] = &result[d][-d];
		delete[] result[d];
	}
	for (int i = x_stack.size(); i > 0; i--)
	{
		cout << x_stack.top() << oprands.top() << y_stack.top() << endl;
		x_stack.pop();
		y_stack.pop();
		oprands.pop();
	}
	delete[] result;
	return 0;
}
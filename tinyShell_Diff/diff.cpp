#pragma once
#include "header.h"
void copyPath(int* a, int* b, int d)
{
	for (int i = -d; i <= d; i++)
	{
		b[i] = a[i];
	}
	return;
}//将路径暂存以备回溯
int readFileByLine(ifstream* afile, char** a)
{
	int lineCount = 0;
	string tmp;
	memset(a, NULL, MAX_LINE_COUNT * sizeof(char*));
	while (getline(*afile, tmp))
	{
		int l = tmp.length() + 1;
		a[lineCount] = new char[l];
		memset(a[lineCount], '\0', l * sizeof(char));
		strcpy_s(a[lineCount], l, tmp.c_str());
		lineCount++;
	}
	return lineCount;
}//按行读取文件，返回行数
int readStrinByLine(char*** a)
{
	int lineCount = 0;
	char* tmp = new char[MAX_LINE_LENGTH];
	*a = new char* [MAX_LINE_COUNT];
	memset(*a, NULL, MAX_LINE_COUNT * sizeof(char*));
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
		int l = strlen(tmp) + 1;
		*a[lineCount] = new char[l];
		strcpy_s(*a[lineCount], l, tmp);
		lineCount++;
	}
	delete[] tmp;
	return lineCount;
}//按行读取strin，返回行数
void printResult(stack<LineRelation> line, char** a, char** b)
{
	LineRelation now;
	while (line.size() > 0)
	{
		now = line.top();
		if (now.op == 'd')
		{
			char op = 'd';
			bool dflag = 0, aflag = 0;
			LineRelation start, add_start, end, tmp;
			start = now;
			tmp = now;
			while (line.size() > 0)
			{
				now = line.top();
				if (now.op == 'd')
				{
					if(now.x!=start.x)
						dflag = 1;
				}
				else if (now.op == 'a')
				{
					if (aflag == 0)
					{
						op = 'c';
						add_start = now;
						aflag = 1;
					}
				}
				if (now.op == '=' || line.size() == 0)
				{
					end = tmp;
					break;
				}
				tmp = now;
				line.pop();
			}
			cout << start.x;
			if (dflag == 1) cout << ',' << add_start.x;
			cout << op;
			if (aflag == 1 && add_start.y != end.y) cout << add_start.y << ',';
			cout << end.y;
			cout << endl;
		}
		if (now.op == 'a')
		{
			LineRelation start, end, tmp;
			start = now;
			tmp = now;
			while (line.size() > 0)
			{
				now = line.top();
				if (now.op != 'a') break;
				tmp = now;
				if (line.size() == 0) break;
				line.pop();
			}
			cout << start.x << 'a' << start.y;
			if (tmp.y != start.y)
			{
				if (now.op == 'a') cout << ',' << now.y;
				else cout << ',' << tmp.y;
			}
			cout << endl;
		}
		if (now.op == '=');
		if (line.size() == 0) break;
		line.pop();
	}
	return;
	/*if (prev.op == 'd' && now.op == 'a')
	{
		cout << prev.x << 'c'<<now.y;
		prev = now;
		line.pop();
		now = line.top();
		while (now.op == 'a' && line.size() > 1)
		{
			cout << ',' << now.y;
			prev = now;
			line.pop();
			now = line.top();
		}
		cout << endl;
	}
	else
	{
		if(prev.op!='=')
			cout << prev.x << prev.op << prev.y << endl;
	}
	*/
}
int doDiff(int argc, char* argv[])
{
	if (strcmp(argv[1], "diff") != 0)
	{
		cerr << "error:Wrong citation!" << endl;
		return -1;
	}
	ifstream afile, bfile;
	afile.open(argv[argc - 2]);
	bfile.open(argv[argc - 1]);
	char* aa[MAX_LINE_COUNT];
	char* bb[MAX_LINE_COUNT];
	int n, m;
	n = readFileByLine(&afile, aa);
	m = readFileByLine(&bfile, bb);
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
			if (k == -d || (k != d && v[k - 1] < v[k + 1]))
				x = v[k + 1];
			else
				x = v[k - 1] + 1;
			y = x - k;
			while (x < n && y < m && strcmp(aa[x], bb[y]) == 0)
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
	stack<LineRelation> line;
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
				line.push({ x,y,'=' });
				x--;
				y--;
			}
			printf("(%d,%d)->(%d,%d),%d->%d,d=%d\n", last_x, last_y, x, y, last_k, k, d);
		}
		if (d > 0)
		{
			if (last_x == x)
				line.push({ x,y,'a' });
			else if (last_y == y)
				line.push({ x,y,'d' });
		}
		x = last_x;
		y = last_y;
		result[d] = &result[d][-d];
		delete[] result[d];
	}
	printResult(line, aa, bb);
	delete[] result;
	return 0;
}//Diff主体函数
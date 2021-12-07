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

int doDiff(int argc, char* argv[])
{
	//1、命令读取与检验
	if (strcmp(argv[1], "diff") != 0)
	{
		cerr << "Debug error:Wrong citation!" << endl;
		return -1;
	}
	if (strcmp(argv[2], "--help") == 0)
	{
		string help = "Usage: diff [OPTION]... FILES\nCompare FILES line by line.\n\nMandatory arguments to long options are mandatory for short options too.\n- q, report only when files differ\n i, ignore case differences in file contents\n - b, ignore changes in the amount of white space\n - w, ignore all white space\n - B, ignore changes where lines are all blank\n - I, ignore changes where all lines match RE\n--help               display this helpand exit\n\n% <  lines from FILE1\n%>  lines from FILE2\n\nFILES are 'FILE1 FILE2' or 'DIR1 DIR2' or 'DIR FILE' or 'FILE DIR'.\nIf a FILE is '-', read standard input.\nExit status is 0 if inputs are the same, 1 if different, -1 if trouble.\n\n";
		strcpy_s(gTerm.strout, help.length() + 1, help.c_str());
		return 2;
	}
	ifstream afile, bfile;
	char* aa[MAX_LINE_COUNT];
	char* bb[MAX_LINE_COUNT];
	int n, m;
	bool all_strin = 0;
	string filename;
	if (strcmp(argv[argc - 2], "-") != 0)
	{
		filename = gTerm.wdir;
		filename.append(argv[argc - 2]);
		afile.open(filename);
		if (afile.is_open() == false)
		{
			cerr << "diff: " << filename << ": No such file or directory" << endl;
			return -1;
		}
		n = readFileByLine(&afile, aa);
	}
	else
	{
		all_strin = 1;
		n = readStrinByLine(aa);
	}
	if (strcmp(argv[argc - 1], "-") != 0)
	{
		filename = gTerm.wdir;
		filename.append(argv[argc - 1]);
		bfile.open(filename);
		if (bfile.is_open() == false)
		{
			cerr << "diff: " << filename << ": No such file or directory" << endl;
			return -1;
		}
		m = readFileByLine(&bfile, bb);
	}
	else
	{
		if (all_strin == 1)
		{
			cerr << "diff: two files from standard input stream is not supported" << endl;
			return -1;
		}
		else m = readStrinByLine(bb);
	}
	int* v = new int[2 * (n + m) + 1];
	memset(v, 0, (2 * (n + m) + 1) * sizeof(int));
	v = &v[n + m];
	int x, y;
	int k, d;
	int** result = new int* [n + m + 1];
	//2、SES计算
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
			while (x < n && y < m && customStrcmp(aa[x], bb[y],1,0,0,0) == 0)
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
	v = NULL;
	//3、回溯路线
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
		result[d] = NULL;
	}
	printResult(line, aa, bb, n, m,diffIgnoreBl);
	delete[] result;
	return 0;
}//Diff主体函数

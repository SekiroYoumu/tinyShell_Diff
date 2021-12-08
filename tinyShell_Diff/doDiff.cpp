#pragma once
#include "diffHeader.h"
char* diffSampleA[MAX_LINE_COUNT];
char* diffSampleB[MAX_LINE_COUNT];
void copyPath(int* a, int* b, int d)
{
	for (int i = -d; i <= d; i++)
	{
		b[i] = a[i];
	}
	return;
}//��·���ݴ��Ա�����
bool checkValidity(char* last, char* check)
{
	if (check == NULL)
	{
		cerr << "diff: missing operand after '" << last << "'" << endl << "diff: Try 'diff --help' for more information." << endl;
		return 0;
	}
	return 1;
}//��鼴��ʹ�õĲ�����Ч��
int doDiff(int argc, char* argv[])
{
	//1�������ȡ�����
	diffios ios;//���ģʽ������ʼ��
	if (argv[0] == NULL)
	{
		cerr << "Debug error:invalid augment !:(" << endl;
		return -1;
	}
	if (strcmp(argv[0], "diff") != 0)
	{
		cerr << "Debug error:Wrong citation or invalid augment!:(" << endl;
		return -1;
	}
	if (!checkValidity(argv[0], argv[1])) return -1;
	if (strcmp(argv[1], "--help") == 0)
	{
		string help = "diff Usage: diff [OPTION]... FILES\nCompare FILES line by line.\n\nMandatory arguments to long options are mandatory for short options too.\n- q, report only when files differ\n i, ignore case differences in file contents\n - b, ignore changes in the amount of white space\n - w, ignore all white space\n - B, ignore changes where lines are all blank\n - I, ignore changes where all lines match RE\n--help               display this helpand exit\n\n%<  lines from FILE1\n%>  lines from FILE2\n\nFILES are 'FILE1 FILE2' or 'DIR1 DIR2' or 'DIR FILE' or 'FILE DIR'.\nIf a FILE is '-', read standard input.\nExit status is 0 if inputs are the same, 1 if different, -1 if trouble.\n\n";
		strcpy_s(gTerm.strout, help.length() + 1, help.c_str());
		return 2;
	}
	for (int i = 1; i < argc - 2; i++)//����������������Ч��
	{
		bool errorFlag = 1;
		if (!checkValidity(argv[i - 1], argv[i])) return -1;
		if (!ios.ud && (strcmp(argv[i], "-i") == 0))
		{
			ios.st = 0;
			ios.ud = 1;
			errorFlag = 0;
		}
		else if (!ios.lb && (strcmp(argv[i], "-b") == 0))
		{
			ios.st = 0;
			ios.lb = 1;
			errorFlag = 0;
		}
		else if (!ios.wb && (strcmp(argv[i], "-w") == 0))
		{
			ios.st = 0;
			ios.wb = 1;
			errorFlag = 0;
		}
		else if (!ios.bl && (strcmp(argv[i], "-B") == 0))
		{
			ios.bl = 1;
			errorFlag = 0;
		}
		else if (!ios.qk && (strcmp(argv[i], "-q") == 0))
		{
			ios.qk = 1;
			errorFlag = 0;
		}
		else if (!ios.I && (strcmp(argv[i], "-I") == 0))
		{
			ios.I = 1;
			errorFlag = 0;
			i++;
			if (i == argc - 2)
			{
				cerr << "diff: missing operand after '" << argv[i] << "'" << endl << "diff: Try 'diff --help' for more information." << endl;
				return -1;
			}
			else ios.target = argv[i];
		}
		if (errorFlag)
		{
			cerr << "diff: invalid option -- " << argv[i] << endl << "diff: Try 'diff --help' for more information." << endl;
			return -1;
		}
	}
	ifstream afile, bfile;
	int n, m;
	bool all_strin = 0;
	string filenameA, filenameB;
	if (!checkValidity(argv[argc - 3], argv[argc - 2])) return -1;
	if (strcmp(argv[argc - 2], "-") != 0)
	{
		filenameA = gTerm.root;
		filenameA.append(1, '/');
		filenameA.append(gTerm.wdir);
		filenameA.append(1, '/');
		filenameA.append(argv[argc - 2]);
		afile.open(filenameA);
		if (afile.is_open() == false)
		{
			cerr << "diff: " << filenameA << ": No such file or directory" << endl;
			return -1;
		}
		n = readFileByLine(&afile, diffSampleA);
	}
	else
	{
		all_strin = 1;
		//debug������û��strin���룬����Ҫ�Լ����룡
		memset(gTerm.strin, 0, MAXFILE * sizeof(char));
		cout << "Debug: Input strin:";
		char* px = gTerm.strin;
		while (1)
		{
			char ch = cin.get();
			if (ch == EOF) break;
			*px = ch;
			px++;
		}
		cin.clear();
		cin.sync();
		cout << "Debug: strin check:"<<endl<<gTerm.strin;

		n = readStrinByLine(diffSampleA);
	}
	if (!checkValidity(argv[argc - 2], argv[argc - 1])) return -1;
	if (strcmp(argv[argc - 1], "-") != 0)
	{
		filenameB = gTerm.root;
		filenameB.append(1, '/');
		filenameB.append(gTerm.wdir);
		filenameB.append(1, '/');
		filenameB.append(argv[argc - 1]);
		bfile.open(filenameB);
		if (bfile.is_open() == false)
		{
			cerr << "diff: " << filenameB << ": No such file or directory" << endl;
			return -1;
		}
		m = readFileByLine(&bfile, diffSampleB);
	}
	else
	{
		if (all_strin == 1)
		{
			cerr << "diff: two files from standard input stream is not supported" << endl;
			return -1;
		}
		else
		{
			//debug������û��strin���룬����Ҫ�Լ����룡
			memset(gTerm.strin, 0, MAXFILE * sizeof(char));
			cout << "Debug: Input strin:";
			char* px = gTerm.strin;
			while (1)
			{
				char ch = cin.get();
				if (ch == EOF) break;
				*px = ch;
				px++;
			}
			cout << "Debug: strin check:" << endl << gTerm.strin;
			cin.clear();
			cin.sync();

			m = readStrinByLine(diffSampleB);
		}
	}
	int* v = new int[2 * (n + m) + 1];
	memset(v, 0, (2 * (n + m) + 1) * sizeof(int));
	v = &v[n + m];
	int x, y;
	int k, d;
	int** result = new int* [n + m + 1];
	//2��SES����
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
			while (x < n && y < m && customStrcmp(diffSampleA[x], diffSampleB[y], ios) == 0)
			{
				x++;
				y++;
			}
			v[k] = x;
			if (x >= n && y >= m)
			{
				//cout << "Now at " << d << " " << x << " " << y << " " << endl;
				goto loopend;
			}
		}
	}
loopend:;
	v = &v[-n - m];
	delete[] v;
	v = NULL;
	//3������·��
	int last_x, last_y, last_k;
	stack<LineRelation> line; //����м��ϵ�����ڹ�ϵ�ǴӺ���ǰ���ݵõ��ģ��ʴ��֮ջ��
	for (; d >= 0; d--)
	{
		k = x - y;
		if (k == -d || (k != d && result[d][k - 1] < result[d][k + 1]))
		{
			last_k = k + 1; //��ʾ��һ������ɾ��
		}
		else
		{
			last_k = k - 1; //��ʾ��һ����������
		}
		last_x = result[d][last_k];
		last_y = last_x - last_k;
		if (d > 0)
		{
			while (last_x < x && last_y < y)
			{
				//printf("(%d,%d)->(%d,%d),%d->%d,d=%d\n", x - 1, y - 1, x, y, k, k, d);
				line.push({ x,y,'=' });
				x--;
				y--;
			}
			//printf("(%d,%d)->(%d,%d),%d->%d,d=%d\n", last_x, last_y, x, y, last_k, k, d);
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
	bool change = printResult(line, diffSampleA, diffSampleB, n, m, ios);
	if (change && ios.qk) //�Ƿ�Ϊ������
	{
		sprintf_s(gTerm.strout, "Files %s and %s differ\n", argv[argc - 2], argv[argc - 1]);
	}
	delete[] result;
	return change;
}//Diff���庯��,return -1����0�޲��1�в��2��--help����
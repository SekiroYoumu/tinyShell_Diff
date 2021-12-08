#include "diffHeader.h"
int readFileByLine(ifstream* afile, char** a)//按行读取文件，返回行数
{
	int lineCount = 0;
	string tmp;//tmp临时存放读入的行，根据行的长度判断后面应该申请的空间大小
	while (getline(*afile, tmp))
	{
		int l = tmp.length() + 1;
		a[lineCount] = new char[l];
		memset(a[lineCount], '\0', l * sizeof(char));
		strcpy_s(a[lineCount], l, tmp.c_str());
		lineCount++;
	}
	return lineCount;
}
int readStrinByLine(char** a)//按行读取标准输入，返回行数
{
	int lineCount = 0;
	char* tmp = new char[MAX_LINE_LENGTH];//tmp临时存放读入的行，根据行的长度判断后面应该申请的空间大小
	char* ptr = gTerm.strin;
	while (*ptr != '\0')
	{
		int n = 0;
		memset(tmp, '\0', MAX_LINE_LENGTH * sizeof(char));
		while (*ptr != '\n' && n < MAX_LINE_LENGTH - 1 && *ptr != '\0')//逐字符读取
		{
			tmp[n] = *ptr;
			n++; ptr++;
		}
		ptr++;
		int l = n + 1;
		a[lineCount] = new char[l];
		strcpy_s(a[lineCount], l, tmp);
		lineCount++;
	}
	delete[] tmp;
	return lineCount;
}
bool isSameCharacter(char a, char b)//（忽略大小写）判断是否为相同字母
{
	if (a < 65 || a>122 || (a > 90 && a < 97)) return 0;
	if (b < 65 || b>122 || (b > 90 && b < 97)) return 0;
	if (a == b || abs(a - b) == 32) return 1;
	else return 0;
}
int customStrcmp(char* a, char* b, diffios ios)//行比较，根据开关的不同决定比较方式，输出1，0，-1的方式与strcmp相近
{
	if (ios.st) return strcmp(a, b);//default
	else
	{
		int i, j;
		for (i = 0, j = 0; a[i] != '\0' && b[j] != '\0';)
		{
			if ((a[i] == b[j]) || (ios.ud && isSameCharacter(a[i], b[j])))
			{
				i++, j++;
			}
			else if (ios.wb && a[i] == 32)
				i++;
			else if (ios.wb && b[j] == 32)
				j++;
			else if (a[i] > b[j]) return 1;
			else if (a[i] < b[j]) return -1;
		}
		if (!(a[i] == '\0' && b[j] == '\0'))//若两个字符串未一同到达结尾，则需判断
		{
			if (ios.lb)//不考虑（行尾）空格
			{
				while (a[i] != '\0')
				{
					if (a[i] != 32) return 1;//若有不是空格的字符则说明两行不同，后同
					i++;
				}
				while (b[j] != '\0')
				{
					if (b[j] != 32) return -1;
					j++;
				}
				return 0;
			}
			else return (a[i] > b[j] ? 1 : -1);
		}
		else return 0;
	}
}
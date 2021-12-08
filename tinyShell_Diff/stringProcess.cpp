#include "diffHeader.h"
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
int readStrinByLine(char** a)
{
	int lineCount = 0;
	char* tmp = new char[MAX_LINE_LENGTH];
	char* ptr = gTerm.strin;
	while (*ptr != '\0')
	{
		int n = 0;
		memset(tmp, '\0', MAX_LINE_LENGTH * sizeof(char));
		while (*ptr != '\n' && n < MAX_LINE_LENGTH - 1 && *ptr != '\0')
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
}//按行读取strin，返回行数
int customStrcmp(char* a, char* b, diffios ios)
{
	bool enda, endb;
	if (ios.st) return strcmp(a, b);//Default
	else
	{
		int i, j;
		for (i = 0, j = 0; a[i] != '\0' && b[j] != '\0';)
		{
			if ((a[i] == b[j]) || (abs(a[i] - b[j]) == 32 && ios.ud))
			{
				i++, j++;
			}
			else if (a[i] == 32 && ios.wb)
				i++;
			else if (b[j] == 32 && ios.wb)
				j++;
			else if (a[i] > b[j]) return 1;
			else if (a[i] < b[j]) return -1;
			if (a[i] == '\0') enda = 1;
			if (b[j] == '\0') endb = 1;
		}
		if (i != j)
		{
			if (!ios.lb) return (i > j ? 1 : -1);
			else
			{
				if (enda == 0)
				{
					for (; a[i] != '\0'; i++)
					{
						if (a[i] != 32) return 1;
					}
				}
				if (endb == 0)
				{
					for (; b[j] != '\0'; i++)
					{
						if (b[j] != 32) return -1;
					}
				}
			}
		}
		return 0;
	}
}//根据开关的不同决定比较方式
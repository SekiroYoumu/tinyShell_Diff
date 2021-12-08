#include "diffHeader.h"
//���ж�ȡ�ļ�����������
int readFileByLine(ifstream* afile, char** a)
{
	int lineCount = 0;
	string tmp;//tmp��ʱ��Ŷ�����У������еĳ����жϺ���Ӧ������Ŀռ��С
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

//���ж�ȡ��׼���룬��������
int readStrinByLine(char** a)
{
	int lineCount = 0;
	char* tmp = new char[MAX_LINE_LENGTH];//tmp��ʱ��Ŷ�����У������еĳ����жϺ���Ӧ������Ŀռ��С
	char* ptr = gTerm.strin;
	while (*ptr != '\0')
	{
		int n = 0;
		memset(tmp, '\0', MAX_LINE_LENGTH * sizeof(char));
		while (*ptr != '\n' && n < MAX_LINE_LENGTH - 1 && *ptr != '\0')//���ַ���ȡ
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

//�����Դ�Сд���ж��Ƿ�Ϊ��ͬ��ĸ
bool isSameCharacter(char a, char b)
{
	if (a < 65 || a>122 || (a > 90 && a < 97)) return 0;
	if (b < 65 || b>122 || (b > 90 && b < 97)) return 0;
	if (a == b || abs(a - b) == 32) return 1;
	else return 0;
}

//�бȽϣ����ݿ��صĲ�ͬ�����ȽϷ�ʽ�����1��0��-1�ķ�ʽ��strcmp���
int customStrcmp(char* a, char* b, diffios ios)
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
		if (!(a[i] == '\0' && b[j] == '\0'))//�������ַ���δһͬ�����β�������ж�
		{
			if (ios.lb)//�����ǣ���β���ո�
			{
				while (a[i] != '\0')
				{
					if (a[i] != 32) return 1;//���в��ǿո���ַ���˵�����в�ͬ����ͬ
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
#include "header.h"
Terminal gTerm;
bool diffSt; //�Ƿ�Ϊ��׼���
bool diffIgnoreUd;//�Ƿ���Դ�Сд
bool diffIgnoreLb;//�Ƿ������ĩ�ո�
bool diffIgnoreWb;//�Ƿ�������пո�
bool diffIgnoreBl=1;//�Ƿ���Կ���
bool diffQuick;//�Ƿ�ֻ��ʾ���޲�ͬ
int main(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
		printf("Parameter %d is %s.\n", i, argv[i]);
	cout << "Input Work directory:";
	cin >> gTerm.wdir;
	/*
	* cout<<"Input strin:";
	char* px = gTerm.strin;
	while (1)
	{
		char ch = cin.get();
		if (ch == EOF) break;
		*px = ch;
		px++;
	}
	cout << gTerm.strin << endl;*/
	doDiff(argc, argv);
	cout << gTerm.strout << endl;
	system("pause");
	return 0;
}
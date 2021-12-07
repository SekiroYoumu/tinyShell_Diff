#include "header.h"
Terminal gTerm;
bool diffSt; //是否为标准输出
bool diffIgnoreUd;//是否忽略大小写
bool diffIgnoreLb;//是否忽略行末空格
bool diffIgnoreWb;//是否忽略所有空格
bool diffIgnoreBl=1;//是否忽略空行
bool diffQuick;//是否只显示有无不同
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
#include "diffHeader.h"
Terminal gTerm;
int main()
{
	char input_buffer[MAXLINE];//输入缓冲区的模拟
	cout << "Machine Name:";
	cin >> gTerm.mach;
	cout << "Root Directory:";
	cin >> gTerm.root;
	strcpy_s(gTerm.wdir, 2, "/");
	cout << "Login:";
	cin >> gTerm.user;
	cin.ignore();
	system("cls");
	for (;;)//简易的解释器框架，方便测试
	{
		cout << "\033[92;1m" << gTerm.user << "@" << gTerm.mach << ":";
		cout << "\033[94;1m" << gTerm.wdir << "\033[0m" << "$";
		cin.getline(input_buffer, MAXLINE);//以getline的形式读入命令(getline自带\0，故无需先初始化或清空input_buffer)
		if (strlen(input_buffer) == 0) continue;
		int argc = 0;
		char* argv[10];
		memset(argv, NULL, 10 * sizeof(char*));
		char* px = input_buffer;
		bool newarg = 1;
		while (*px != '\0')
		{
			if (newarg)
			{
				argv[argc] = px;
				argc++;
				newarg = 0;
			}
			if (*px == ' ')//如若读到空格，则代表下一个是新参数(newarg)，对应后续一系列操作
			{
				*px = '\0';
				newarg = 1;
			}
			px++;
		}
		*px = '\0';
		if (argc > 0 && strcmp(argv[0], "clear") == 0)//方便测试，引入清屏命令clear
		{
			system("cls");
			continue;
		}
		doDiff(argc, argv);//由于是简易解释器，故直接传参至doDiff处理
		cout << gTerm.strout;//标准输出至屏幕
		memset(gTerm.strout, 0, MAXFILE * sizeof(char));//清空strout
	}
	system("pause");
	return 0;
}
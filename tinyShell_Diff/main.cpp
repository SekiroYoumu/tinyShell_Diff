#include "diffHeader.h"
Terminal gTerm;
int main()
{
	char input_buffer[MAXLINE];//���뻺������ģ��
	cout << "Machine Name:";
	cin >> gTerm.mach;
	cout << "Root Directory:";
	cin >> gTerm.root;
	strcpy_s(gTerm.wdir, 2, "/");
	cout << "Login:";
	cin >> gTerm.user;
	cin.ignore();
	system("cls");
	for (;;)//���׵Ľ�������ܣ��������
	{
		cout << "\033[92;1m" << gTerm.user << "@" << gTerm.mach << ":";
		cout << "\033[94;1m" << gTerm.wdir << "\033[0m" << "$";
		cin.getline(input_buffer, MAXLINE);//��getline����ʽ��������(getline�Դ�\0���������ȳ�ʼ�������input_buffer)
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
			if (*px == ' ')//���������ո��������һ�����²���(newarg)����Ӧ����һϵ�в���
			{
				*px = '\0';
				newarg = 1;
			}
			px++;
		}
		*px = '\0';
		if (argc > 0 && strcmp(argv[0], "clear") == 0)//������ԣ�������������clear
		{
			system("cls");
			continue;
		}
		doDiff(argc, argv);//�����Ǽ��׽���������ֱ�Ӵ�����doDiff����
		cout << gTerm.strout;//��׼�������Ļ
		memset(gTerm.strout, 0, MAXFILE * sizeof(char));//���strout
	}
	system("pause");
	return 0;
}
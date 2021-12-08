#include "diffHeader.h"
Terminal gTerm;
int main()
{
	/*for (int i = 0; i < argc; i++)
		printf("Parameter %d is %s.\n", i, argv[i]);*/
	char input_buffer[MAXLINE];
	cout << "Machine Name:";
	cin >> gTerm.mach;
	cout << "Root Directory:";
	cin >> gTerm.root;
	cout << "Login:";
	cin >> gTerm.user;
	cin.ignore();
	system("cls");
	for (;;)
	{
		cout << "\033[92;1m" << gTerm.user << "@" << gTerm.mach << ":";
		cout << "\033[94;1m" << gTerm.wdir << '/' << "\033[0m" << "$";
		cin.getline(input_buffer, MAXLINE);
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
			if (*px == ' ')
			{
				*px = '\0';
				newarg = 1;
			}
			px++;
		}
		*px = '\0';
		if (argc>0&&strcmp(argv[0], "clear") == 0)
		{
			system("cls");
			continue;
		}
		doDiff(argc,argv);
		cout << gTerm.strout;
		memset(gTerm.strout, 0, MAXFILE * sizeof(char));
	}
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
	system("pause");
	return 0;
}
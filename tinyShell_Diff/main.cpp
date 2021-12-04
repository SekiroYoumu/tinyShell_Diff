#include "header.h"
Terminal gTerm;
int main(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
		printf("Parameter %d is %s.\n", i, argv[i]);
	/*char* px = gTerm.strin;
	while (1)
	{
		char ch = cin.get();
		if (ch == EOF) break;
		*px = ch;
		px++;
	}
	cout << gTerm.strin << endl;*/
	doDiff(argc, argv);
	system("pause");
	return 0;
}
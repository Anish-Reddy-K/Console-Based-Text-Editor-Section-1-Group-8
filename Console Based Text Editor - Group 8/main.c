#include "uistuff.h"
#include "backend.h"	

int main(void)
{
	printf("\nWelcome to command line text editor! Options below, enter number associated with desired option.");
	srand(time(0));
	FILE* fp = fopen(FILELIST, "r");
	if (!fp)
		createfiledirectory();
	if (fp)
		fclose(fp);
	bool run = true;
	while (run)
	{
		Mainmenu();
		int in = getmenuinput();
		switch (in) {
		case 1:
		{
			createfile();
			break;
		}
		case 2:
		{
			printfiles();
			break;
		}
		case 3:
		{
			openfile();
			break;
		}
		case 4:
		{
			deletefile();
			break;
		}
		case 5:
		{
			displayfile();
			break;
		}
		case 6:
		{
			printf("\nNot yet in use\n");
			break;
		}
		case 7:
		{
			run = false;
			break;
		}
		default:
		{
			printf("\nenter a valid number dipshit");
			break;
		}
		}
	}
	atexit((*programexit));
}

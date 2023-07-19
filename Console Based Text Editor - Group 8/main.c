#include "uistuff.h"
#include "backend.h"	

int main(void)
{
	printf("\nWelcome to command line text editor! Options below, enter number associated with desired option.");
	srand(time(0)); // Seeds rand with time since 0
	FILE* fp = fopen(FILELIST, "r");
	if (!fp)
		createfiledirectory(); // If file directory doesnt exist, call function to make one
	if (fp)
		fclose(fp);
	bool run = true;
	while (run)
	{
		Mainmenu(); // Print main menu
		int in = getmenuinput();
		switch (in) {
		case 1:
		{
			createfile(); // Begins the file creation process
			break;
		}
		case 2:
		{
			printfiles(); // Print all files in directory
			break;
		}
		case 3:
		{
			openfile(); // Begin file editing process
			break;
		}
		case 4:
		{
			deletefile(); // Begin file deletion process
			break;
		}
		case 5:
		{
			displayfile(); // Display file of user choice
			break;
		}
		case 6:
		{
			printf("\nNot yet in use\n");
			break;
		}
		case 7:
		{
			run = false; // Ends run loop before breaking
			break;
		}
		default:
		{
			printf("\nenter a valid number dipshit"); // If input isnt a valid option, inform user
			break;
		}
		}
	}
	atexit((*programexit)); // Calls programexit function before closing program
}




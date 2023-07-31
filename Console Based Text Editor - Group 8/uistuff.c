#include "backend.h"
#include "uistuff.h"


void Mainmenu(void) // Displays main menu options 
{
	printf("\n\n*********************************");
	printf("\n* 1: Create new file            *");
	printf("\n* 2: View existing files        *");
	printf("\n* 3: Open existing file         *");
	printf("\n* 4: Delete existing file       *");
	printf("\n* 5: View contents of file      *");
	/*printf("\n* 6: Settings (May be used later to shut off autocorrect but not sure yet)");*/
	printf("\n* 6: Exit program               *\n\n");
	printf("Enter here: ");
}
void displayfile(void)
{
	printf("\nEnter name of file you wish to view: ");
	char name[NAMESIZE];
	getnameinput(name);
	if (overwriteprotect(name) == true) // Checks if file with name given exists
		printf("\nFile not found with that name.");
	else
	{
		system("@cls||clear"); // Clear screen before printing file
		printf("File contents shown below:\n\n");
		FILE* fp = fopen(name, "r");
		int linecount = getlinecount(fp);
		for (int i = 0; i <= linecount; i++)
		{
			char contents[TEXTSIZE]; // Each line read from file goes into this buffer
			fgets(contents, TEXTSIZE, fp);
			printf("%s", contents); // Contents buffer displays each line
		}
		if (fp)
			fclose(fp);
	}
}
void optionsmenu(void) // Displays menu when hotkey pressed while editing a file
{
	printf("\nSelect an option from the list below.");
	printf("\n1: Save and return to main menu");
	printf("\n2: Return to main menu without saving\n");
}
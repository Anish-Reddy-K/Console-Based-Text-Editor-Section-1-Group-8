#include "backend.h"
#include "uistuff.h"

void Mainmenu(void)
{
	printf("\n1: Create new file");
	printf("\n2: View existing files");
	printf("\n3: Open existing file");
	printf("\n4: Delete existing file");
	printf("\n5: View contents of file");
	printf("\n6: Settings (May be used later to shut off autocorrect but not sure yet)");
	printf("\n7: Exit program\n");
}
void displayfile(void)
{
	printf("\nEnter name of file you wish to view: ");
	char name[NAMESIZE];
	getnameinput(name);
	if (overwriteprotect(name) == true)
		printf("\nFile not found with that name.");
	else
	{
		system("@cls||clear");
		FILE* fp = fopen(name, "r");
		int linecount = getlinecount(fp);
		for (int i = 0; i <= linecount; i++)
		{
			char contents[TEXTSIZE];
			fgets(contents, TEXTSIZE, fp);
			printf("%s", contents);
		}
		if (fp)
			fclose(fp);
	}
}
void optionsmenu(void)
{
	printf("\nSelect an option from the list below.");
	printf("\n1: Save and return to main menu");
	printf("\n2: Return to main menu without saving\n");
}
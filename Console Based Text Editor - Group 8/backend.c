#include "backend.h"
#include "editing.h"
void getnameinput(char* name)
{
	fgets(name, NAMESIZE, stdin);
	removenewline(name);
}
void removenewline(char* buffer) // removes newline to prevent errors reading and displaying data
{
	for (int i = 0; i < strlen(buffer); i++)
		if (buffer[i] == '\n')
			buffer[i] = '\0';
}
void createfiledirectory(void)
{
	FILE* fp = fopen(FILELIST, "a");
	for (int i = 0; i < FILECOUNT; i++)
	{
		fprintf(fp, "EMPTY\n");
	}
	if (fp)
		fclose(fp);
}
int getmenuinput(void)
{
	char in[NAMESIZE];
	fgets(in, NAMESIZE, stdin);
	int num = atoi(in);
	return num;
}
void printfiles(void)
{
	FILE* fp = fopen(FILELIST, "r");
	int filenum = 1;
	char filename[NAMESIZE];
	printf("\nFiles listed below:\n");
	for (int i = 0; i < FILECOUNT; i++)
	{
		fgets(filename, NAMESIZE, fp);
		removenewline(filename);
		if (strcmp(filename, "EMPTY") != 0)
			printf("%d: %s\n", filenum++, filename);

	}
	if (fp)
		fclose(fp);
}
void createfile(void)
{
	printf("\nEnter name of new file (type .txt at the end of the name to make it a notepad text file): ");
	char name[NAMESIZE];
	getnameinput(name);
	if (overwriteprotect(name) == false)
		printf("\nFile with thaat name already exists. Please delete existing file before creating new file with this name.");
	else
	{
		if (addfiletolist(name) == false)
			printf("\nFile limit of %d reached. Please delete some files in the delete menu to create a new file.", FILECOUNT);
		else
		{
			FILE* fp = fopen(name, "w");
			fprintf(fp, "%d", 0);
			fclose(fp);
		}
	}
}
bool overwriteprotect(char* name)
{
	FILE* fp = fopen(FILELIST, "r");
	for (int i = 0; i < FILECOUNT; i++)
	{
		char filecmp[NAMESIZE];
		fgets(filecmp, NAMESIZE, fp);
		removenewline(filecmp);
		if (strcmp(filecmp, name) == 0)
			return false;
	}
	return true;
}
void programexit(void)
{
	printf("Program exiting.");
}
bool addfiletolist(char* name)
{
	char filename[NAMESIZE];
	char fileduplicate[FILECOUNT][NAMESIZE];
	int num = -1;
	FILE* fp = fopen(FILELIST, "r");
	for (int i = 0; i < FILECOUNT; i++)
	{
		fgets(filename, NAMESIZE, fp);
		strcpy(fileduplicate[i], filename);
		removenewline(filename);
		if (strcmp(filename, "EMPTY") == 0)
			num = i;
	}
	if (fp)
		fclose(fp);
	if (num == -1)
		return false;
	FILE* fp2 = fopen(FILELIST, "w");
	for (int i = 0; i < FILECOUNT; i++)
	{
		if (num == i)
		{
			fprintf(fp2, name);
			fprintf(fp2, "\n");
		}
		else
			fprintf(fp2, fileduplicate[i]);
	}
	if (fp2)
		fclose(fp2);
	return true;
}
void deletefile(void)
{
	printf("\nEnter name of file to be deleted: ");
	char name[NAMESIZE];
	getnameinput(name);
	if (removefilefromlist(name) == false)
		printf("\nFile with that name not found.");
	else
	{
		removenewline(name);
		if (remove(name) != 0)
			printf("\nFile deletion error. File removed from list but may need to be deleted manually.");
		else
			printf("\nFile deleted successfully.");
	}
}
bool removefilefromlist(char* name)
{
	char filename[NAMESIZE];
	char fileduplicate[FILECOUNT][NAMESIZE];
	bool changemade = false;
	FILE* fp = fopen(FILELIST, "r");
	for (int i = 0; i < FILECOUNT; i++)
	{
		fgets(filename, NAMESIZE, fp);
		strcpy(fileduplicate[i], filename);
		if (strcmp(filename, name) == 0)
		{
			strcpy(fileduplicate[i], "EMPTY\n");
			changemade = true;
		}
	}
	if (fp)
		fclose(fp);
	if (changemade == false)
		return false;
	FILE* fp2 = fopen(FILELIST, "w");
	for (int i = 0; i < FILECOUNT; i++)
	{
		fprintf(fp2, fileduplicate[i]);
	}
	if (fp2)
		fclose(fp2);
	return true;
}
void openfile(void)
{
	printf("\nEnter the name of the file you wish to open:");
	char name[TEXTSIZE];
	getnameinput(name);
	if (overwriteprotect(name) == true)
		printf("\nFile not found with that name.");
	else
		editfile(name);

}
int getlinecount(FILE* fp)
{
	char count[LINECOUNTSIZE];
	fgets(count, LINECOUNTSIZE, fp);
	removenewline(count);
	int num = atoi(count);
	if (num < 0) {
		printf("\nError reading data from file. Program aborting.");
		exit(-1);
	}
	return num;
}
void savefile(char* name, char contents[][TEXTSIZE], int linecount)
{
	FILE* fp = fopen(name, "w");
	fprintf(fp, "%d", linecount);
	fprintf(fp, "\n");
	for (int i = 0; i <= linecount; i++)
	{
		fprintf(fp, "%s", contents[i]);
		fprintf(fp, "\n");
	}
	if (fp)
		fclose(fp);
}
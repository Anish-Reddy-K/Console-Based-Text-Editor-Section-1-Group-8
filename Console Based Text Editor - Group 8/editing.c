#include "editing.h"

void deleteSymbol(char* s, size_t position)
{
    size_t i, len = strlen(s);

    for (i = position; i < len; i++)
        s[i] = s[i + 1];
}
int insertInStr(char* s, size_t position, char c)
{
    size_t i;
    if (position == 0)
    {
        (s)[0] = c;
        s[1] = '\0';
    }

    else
        for (i = strlen(s) + 1; i >= position; i--)
            (s)[i] = i == position ? c : (s)[i - 1];
    return 1;
}
void printTextWithCursor(char* s, size_t position)
{
    size_t currPos, length = strlen(s);

    for (currPos = 0; currPos <= length; currPos++)
    {
        putchar(currPos < position ? s[currPos] : currPos == position ? SEPARATOR : s[currPos - 1]);
    }
    putchar(SEPARATOR);
}
void editfile(char* name)
{
    FILE* fp = fopen(name, "r");
    size_t pos[FILECOUNT];
    char s[FILECOUNT][TEXTSIZE];
    int maxsel = getlinecount(fp);
    if (maxsel == 0)
        strcpy(s[0], "");

    system("@cls||clear");
    printf("\nPress enter to start new line/paragraph. Traverse using the left and right arrow keys.\nEnsure you are at the end of a line to start a new line.\nTo access options, press ~ and click enter.\n\n");
    for (int i = 0; i <= maxsel; i++)
    {
        fgets(s[i], TEXTSIZE, fp);
        if (i == maxsel)
            removenewline(s[i]);
        printf("%s", s[i]);
        removenewline(s[i]);
        pos[i] = strlen(s[i]);
    }
    if (fp)
        fclose(fp);
    unsigned char c;
    int sel = maxsel;
    for (int i = 0; i <= maxsel; i++)
        pos[i] = strlen(s[i]);
    while ((c = _getch()) != HOTKEY)
    {
        putchar('\r');
        switch (c)
        {
        case ARROW://OR DELETE
            c = _getch();
            if (c == LEFT)
            {
                if (pos[sel] > 0)
                    pos[sel]--;
                else if (sel != 0)
                {
                    sel--;
                    system("@cls||clear");
                    for (int i = 0; i <= sel; i++)
                    {
                        printf(s[i]);
                        if (i != sel)
                            printf("\n");
                    }
                    putchar('\r');
                }
            }
            if (c == RIGHT)
            {
                if (pos != NULL && pos[sel] < strlen(s[sel]))
                    pos[sel]++;
                else if (sel != maxsel)
                {
                    sel++;
                    system("@cls||clear");
                    for (int i = 0; i <= sel; i++)
                    {
                        printf(s[i]);
                        if (i != sel)
                            printf("\n");
                    }
                    putchar('\r');
                }
            }
            break;
        case BACKSPACE:
            if (pos > 0)
                deleteSymbol(s[sel], --pos[sel]);

            break;
        case ENTER:
            if (pos[sel] == strlen(s[sel]))
            {
                system("@cls||clear");
                if (sel == maxsel)
                    maxsel++;
                sel++;
                strcpy(s[sel], "\0");
                pos[sel] = 0;
                for (int i = 0; i <= sel; i++)
                {
                    printf(s[i]);
                    if (i != sel)
                        printf("\n");
                }
                putchar('\r');
            }
            break;
        default:
            if (pos[sel] >= 0 && pos[sel] <= strlen(s[sel]))
                insertInStr(s[sel], pos[sel]++, c);


        }
        if (c != ENTER)
            printTextWithCursor(s[sel], pos[sel]);
    }
    bool run = true;
    while (run)
    {
        optionsmenu();
        int choice2 = getmenuinput();
        switch (choice2) {
        case 1:
        {
            savefile(name, s, maxsel);
            run = false;
            break;
        }
        case 2:
        {
            run = false;
            break;
        }
        default:
        {
            printf("\nPlease enter one of the presented options.");
            break;
        }
        }
    }
}
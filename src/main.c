#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "menu.h"

void MainDiagnosticsCounterOnExecute(tMenuInfo *info)
{
    int *counter = (int*)info->data;
    ++*counter;
}

void MainDiagnosticsCounterOnDraw(tMenuInfo *info)
{
    int *counter = (int*)info->data;
    printf("%d", *counter);
}
void MainDiagnosticsCounterExpOnExecute(tMenuInfo *info)
{
    int *counter = (int*)info->data;
    *counter *= *counter;
}

static int diagnosticsCounter = 0;
const tMenuItem menuDiagnosticsItems[] = {
    {"Counter",  MainDiagnosticsCounterOnExecute, MainDiagnosticsCounterOnDraw, &diagnosticsCounter},
    {"Counter Exp",  MainDiagnosticsCounterExpOnExecute, NULL, &diagnosticsCounter},
    {NULL}
};

tMenu menuDiagnostics = {
    "Diagnostics",
    menuDiagnosticsItems
};

const tMenuItem menuMainItems[] = {
    {"Empty Item",  NULL, NULL, NULL},
    {"Diagnostics",  MenuOnExecuteSubMenu, NULL, (void*)&menuDiagnostics},
    {NULL}
};

tMenu menuMain = {
    "Main",
    menuMainItems,
    0,
    NULL
};

void ClearScreen()
{
	printf("\033[H\033[J");
}

int main()
{
    // Modify terminal so we can read characters a single char at a time without having to press enter (unbuffered).
    system("stty cbreak");
    printf ("----- Darren's Dummy Menu -----\n\n");

    tCurrentMenu currentMenu;
    MenuInit(&currentMenu, &menuMain);
    ClearScreen();
    MenuUpdate(&currentMenu, eButtonNone);

	bool quit = false;
    do {
        int inputChar = getchar();
        if (inputChar > 0) {
            eButton buttonPress;
            switch ((char)inputChar) {
            case 'w':
                buttonPress = eButtonUp;
                break;
            case 's':
                buttonPress = eButtonDown;
                break;
            case 'a':
                buttonPress = eButtonLeft;
                break;
            case 'd':
                buttonPress = eButtonRight;
                break;
	case 'q':
		quit = true;
		break;
            default:
                buttonPress = eButtonNone;
                break;
            }
            
            MenuUpdate(&currentMenu, buttonPress);

            if (!currentMenu.menu) {
                printf ("Exiting Menu\n");
                break;
            }
        }
        else if (inputChar < 0) {
            break;
        }
    } while (!quit);


    printf ("\nExiting Program\n");

    // Return the terminal to its normal 'buffered' behaviour.
    system("stty -cbreak");

    return 0;
}

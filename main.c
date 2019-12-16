#include <stdio.h>

void MainDiagnosticsCounterOnExecute(void *data)
{
    int *counter = (int*)data;
    ++*counter;
}

void MainDiagnosticsCounterOnDraw(void *data)
{
    int *counter = (int*)data;
    printf("%d", *counter);
}
void MainDiagnosticsCounterExpOnExecute(void *data)
{
    int *counter = (int*)data;
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

int main()
{
    printf ("----- Darren's Dummy Menu -----\n\n");
    char inputChar;
    tCurrentMenu currentMenu = {&menuMain};
    MenuDraw(&currentMenu, eButtonNone);

    do {
        int result = scanf("%c", &inputChar);
        if (result > 0) {
            eButton buttonPress;
            switch (inputChar) {
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
            default:
                buttonPress = eButtonNone;
                break;
            }
            
            MenuDraw(&currentMenu, buttonPress);

            if (!currentMenu.menu) {
                printf ("Exiting Menu\n");
                break;
            }
        }
        else if (result < 0) {
            break;
        }
    } while (inputChar != 'q');


    printf ("\nExiting Program\n");
    return 0;
}

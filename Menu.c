#include <stdio.h>

typedef struct sMenu tMenu;

// The actual menu item.
// Holds the name of the item, and function pointers for when the item is displayed
// and if the user selects the item.
// The data pointer can point to any piece of data, and will be passed into the execute and draw
// functions.
typedef struct {
    const char *name;
    void (*onExecute)(void*);
    void (*onDraw)(void*);
    void *data;
}tMenuItem;

// The actual menu (or submenu).
// Holds the name of the menu, and the array of menu items.
// The index of the top level menu needs to be set to 0,
// and the previous pointer to NULL.
// Notice that the addition of the "previous" pointer makes our menu
// act a bit like a linked list, so we can dynamically move up and down in
// the menu structure.
typedef struct sMenu{
    const char *name;
    const tMenuItem *items;
    int index;
    struct sMenu *previous;
}tMenu;

// Instead of having to pass a pointer-to-pointer into MenuDraw, we can pass a pointer
// to tCurrentMenu, which makes it easier to think about.
typedef struct {
    tMenu *menu;
}tCurrentMenu;

// Place this function in the "onExecute" callback, and the address of the target menu in the data pointer,
// to navigate to a submenu.
void MenuOnExecuteSubMenu(){}

// An enumeration for separating menu button presses from the actual key strokes used
// to navigate the menu.
typedef enum {
    eButtonNone,
    eButtonUp,
    eButtonDown,
    eButtonLeft,
    eButtonRight,
}eButton;

// Handles the drawing, navigating and updating of the menu.
void MenuDraw(tCurrentMenu *currentMenu, eButton buttonPress)
{
    // Make sure sensible values have been passed into the function.
    if (!currentMenu) {
        return;
    }
    if (!currentMenu->menu) {
        return;
    }
    
    tMenu *menu = currentMenu->menu;

    // Handle the navigation of the menu first, so that we update the menu before we draw it.
    switch (buttonPress) {
    case eButtonUp:
        if (menu->index > 0) {
            --menu->index;
        }
        else {
            int i = menu->index + 1;
            while (menu->items[i].name) {
                ++menu->index;
                ++i;
            }
        }
        break;
    case eButtonDown:
        if (menu->items[menu->index].name && menu->items[menu->index + 1].name) {
            ++menu->index;
        }
        else {
            menu->index = 0;
        }
        break;
    case eButtonLeft:
        currentMenu->menu = menu->previous;
        break;
    case eButtonRight:
    {
        const tMenuItem *item = &menu->items[menu->index];
        if (item->onExecute == MenuOnExecuteSubMenu) {
            if (item->data) {
                tMenu *subMenu = (tMenu*)item->data;
                subMenu->previous = currentMenu->menu;
                subMenu->index = 0;
                currentMenu->menu = subMenu;
            }
        }
        else if (item->onExecute) {
            item->onExecute(item->data);
        }
        break;
    }
    default:
        break;
    }
    
    // Check to see if the user has exited the menu.
    if (!currentMenu->menu) {
        return;
    }

    menu = currentMenu->menu;

    // Draw the menu.
    printf("%s\n", menu->name);
    int i = 0;
    while (menu->items[i].name != NULL) {
        const tMenuItem *item = &menu->items[i];
        printf("%s  %s ", (i == menu->index) ? "->" : "  ", item->name);
        if (item->onDraw) {
            item->onDraw(item->data);
        }
        printf("\n");
        ++i;
    } 
}

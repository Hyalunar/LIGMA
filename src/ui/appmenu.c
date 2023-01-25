#include "appmenu.h"

GtkWidget* menuBar      = NULL;
GtkWidget* fileMenuItem = NULL;

void AppMenu_FileMenuItem_Create()
{
    if (fileMenuItem != NULL) {
        return;
    }
    GtkWidget* newFileItem;
    GtkWidget* openFileItem;
    GtkWidget* saveFileItem;
    GtkWidget* autoSaveItem;

    // Create Widgets
    fileMenuItem = gtk_menu_item_new_with_mnemonic("_File");
    newFileItem  = gtk_menu_item_new_with_mnemonic("_New");
    openFileItem = gtk_menu_item_new_with_mnemonic("_Open");
    saveFileItem = gtk_menu_item_new_with_mnemonic("_Save");
    autoSaveItem = gtk_check_menu_item_new_with_mnemonic("_Autosave");
    GtkWidget* fileMenu = gtk_menu_new();

    // Connect signals
    // TODO: Actually connect signals

    // Attach Widgets
    gtk_menu_attach(GTK_MENU(fileMenu), newFileItem , 0, 1, 0, 1);
    gtk_menu_attach(GTK_MENU(fileMenu), openFileItem, 0, 1, 2, 3);
    gtk_menu_attach(GTK_MENU(fileMenu), saveFileItem, 0, 1, 4, 5);
    gtk_menu_attach(GTK_MENU(fileMenu), autoSaveItem, 0, 1, 6, 7);

    // Set submenu
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMenuItem), fileMenu);
}

void AppMenu_Create()
{
    if (menuBar != NULL) {
        return;
    }

    menuBar  = gtk_menu_bar_new();
    AppMenu_FileMenuItem_Create();

    gtk_container_add(GTK_CONTAINER(menuBar), fileMenuItem);

}


GtkWidget* AppMenu_GetWidget()
{
    return menuBar;
}
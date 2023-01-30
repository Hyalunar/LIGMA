#include "appmenu.h"

GtkWidget* menuBar      = NULL;
GtkWidget* fileMenuItem = NULL;
GtkWidget* plugMenuItem = NULL;

void AppMenu_LoadPlug_PassOn(void* fname, void* data)
{
    Load_PlugByPath(fname);
}

void AppMenu_LoadPlug_Callback()
{
    printf("Loading Plug!\n");
    GtkFileChooserNative* fileDialog;
    GtkFileChooser*       fileChooser;
    GtkFileFilter*        fileFilter;

    fileDialog = gtk_file_chooser_native_new(
        "Select Plug SharedObject Library",
        NULL,
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "Load",
        "Cancel");
    
    fileChooser = GTK_FILE_CHOOSER(fileDialog);
    gtk_file_chooser_set_select_multiple(fileChooser, TRUE);

    fileFilter = gtk_file_filter_new();

    #ifdef __unix__
    gtk_file_filter_add_mime_type(fileFilter, "application/x-sharedlib");
    #elif _WIN32
    gtk_file_filter_add_mime_type(fileFilter, "application/x-dosexec");
    #endif

    gtk_file_chooser_set_filter(fileChooser, fileFilter);

    gint response = gtk_native_dialog_run(GTK_NATIVE_DIALOG(fileDialog));

    if (response == GTK_RESPONSE_ACCEPT) {
        GSList* plugFileNames = gtk_file_chooser_get_filenames(fileChooser);
        g_slist_foreach(plugFileNames, AppMenu_LoadPlug_PassOn, NULL);
        g_slist_free_full(plugFileNames, free);
    }

    gtk_native_dialog_destroy(GTK_NATIVE_DIALOG(fileDialog));
    g_object_unref(fileDialog);
    // This automatically unrefs fileChooser and fileFilter as well
}

void AppMenu_UnloadPlug_Callback()
{
    printf("Unloading Plug!\n");
}

void AppMenu_ReloadPlug_Callback()
{
    printf("Reloading Plug!\n");
}

void AppMenu_ShowPlugs_Callback()
{
    printf("Showing Plugs!\n");
}

void AppMenu_PlugMenuItem_Create()
{
    if (plugMenuItem != NULL) {
        return;
    }
    plugMenuItem = gtk_menu_item_new_with_mnemonic("_Plugs");

    GtkWidget* plugSubMenu;

    GtkWidget* loadPlugItem;
    GtkWidget* unloadPlugItem;
    GtkWidget* reloadPlugItem;
    GtkWidget* showPlugsItem;
    
    // Create widgets
    plugSubMenu    = gtk_menu_new();
    loadPlugItem   = gtk_menu_item_new_with_mnemonic("_Load Plug");
    unloadPlugItem = gtk_menu_item_new_with_mnemonic("_Unload Plug");
    reloadPlugItem = gtk_menu_item_new_with_mnemonic("_Reload Plug");
    showPlugsItem  = gtk_menu_item_new_with_mnemonic("_Show Plugs");

    // Connect Signals
    //TODO: Connect signals
    g_signal_connect(loadPlugItem  , "activate", AppMenu_LoadPlug_Callback  , NULL);
    g_signal_connect(unloadPlugItem, "activate", AppMenu_UnloadPlug_Callback, NULL);
    g_signal_connect(reloadPlugItem, "activate", AppMenu_ReloadPlug_Callback, NULL);
    g_signal_connect(showPlugsItem , "activate", AppMenu_ShowPlugs_Callback  , NULL);

    // Add to submenu
    gtk_menu_attach(GTK_MENU(plugSubMenu), loadPlugItem  , 0, 1, 0, 1);
    gtk_menu_attach(GTK_MENU(plugSubMenu), unloadPlugItem, 0, 1, 2, 3);
    gtk_menu_attach(GTK_MENU(plugSubMenu), reloadPlugItem, 0, 1, 4, 5);
    gtk_menu_attach(GTK_MENU(plugSubMenu), showPlugsItem , 0, 1, 6, 7);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(plugMenuItem), plugSubMenu);
}

void AppMenu_FileMenuItem_Create()
{
    if (fileMenuItem != NULL) {
        return;
    }
    fileMenuItem = gtk_menu_item_new_with_mnemonic("_File");
    
    GtkWidget* fileSubMenu;
    GtkWidget* newFileItem;
    GtkWidget* openFileItem;
    GtkWidget* saveFileItem;
    GtkWidget* autoSaveItem;

    // Create Widgets
    fileSubMenu  = gtk_menu_new();
    newFileItem  = gtk_menu_item_new_with_mnemonic("_New");
    openFileItem = gtk_menu_item_new_with_mnemonic("_Open");
    saveFileItem = gtk_menu_item_new_with_mnemonic("_Save");
    autoSaveItem = gtk_check_menu_item_new_with_mnemonic("_Autosave");

    // Connect signals
    // TODO: Actually connect signals

    // Attach Widgets
    gtk_menu_attach(GTK_MENU(fileSubMenu), newFileItem , 0, 1, 0, 1);
    gtk_menu_attach(GTK_MENU(fileSubMenu), openFileItem, 0, 1, 2, 3);
    gtk_menu_attach(GTK_MENU(fileSubMenu), saveFileItem, 0, 1, 4, 5);
    gtk_menu_attach(GTK_MENU(fileSubMenu), autoSaveItem, 0, 1, 6, 7);

    // Set submenu
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMenuItem), fileSubMenu);
}

void AppMenu_Create()
{
    if (menuBar != NULL) {
        return;
    }

    menuBar  = gtk_menu_bar_new();
    AppMenu_FileMenuItem_Create();
    AppMenu_PlugMenuItem_Create();

    gtk_container_add(GTK_CONTAINER(menuBar), fileMenuItem);
    gtk_container_add(GTK_CONTAINER(menuBar), plugMenuItem);

}


GtkWidget* AppMenu_GetWidget()
{
    return menuBar;
}
#include "pluginlister.h"

void PluginLister_Show()
{
    GtkWidget* dialog;
    GtkWidget* listbox;
    GArray* list;
    plug_t* plugin;

    list    = PluginManager_GetPluginList();
    dialog  = gtk_dialog_new_with_buttons("Plugins", NULL, GTK_DIALOG_MODAL, "OK", GTK_RESPONSE_NONE, NULL);
    listbox = gtk_list_box_new();

    for (int i = 0; i < list->len; i++) {
        plugin = list->data + i * sizeof(plug_t);
        gtk_list_box_insert(GTK_LIST_BOX(listbox), gtk_label_new(plugin->pluginfo.name->str), -1);
    }

     g_signal_connect_swapped (dialog,
                           "response",
                           G_CALLBACK (gtk_widget_destroy),
                           dialog);

    gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(dialog)), gtk_label_new("Loaded Plugins:"));
    gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(dialog)), listbox);
    gtk_window_resize(GTK_WINDOW(dialog), 240, 480);
    gtk_widget_show_all(dialog); 
}
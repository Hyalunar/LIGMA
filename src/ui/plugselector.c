#include "plugselector.h"

GtkWidget* PlugSelector      = NULL;
GArray*    PlugSelectorItems = NULL;

GtkWidget* PlugSelector_GetWidget()
{
    return PlugSelector;
}

int PlugSelector_PlugManagerUnloadCallback(char actionMask, plug_t* plug)
{
    printf("Unloaded %s\n", plug->pluginfo.name->str);
}

int PlugSelector_PlugManagerLoadCallback(char actionMask, plug_t* plug)
{
    printf("Loaded %s\n", plug->pluginfo.name->str);
}

gboolean PlugSelector_UIPlugSelectedCallback(GtkWidget* widget, plug_t* plug)
{
    printf("Plug \"%s\" was selected\n", plug->pluginfo.name->str);
    return TRUE;
}

/// @brief Add a plug to the selection
/// @param plug Plug to be added
/// @return EINVAL Plugin was NULL
/// @return EINVAL Plugin has no valid name
int PlugSelector_AddPlug(plug_t* plug)
{
    if (plug == NULL) {
        return EINVAL;
    }
    if (plug->pluginfo.name == NULL) {
        return EINVAL;
    }

    GtkWidget* gtkItem = gtk_label_new(plug->pluginfo.name->str);
    gtk_widget_set_events(gtkItem, gtk_widget_get_events(gtkItem) | GDK_BUTTON_PRESS_MASK);

    g_signal_connect(gtkItem, "button-press-event", G_CALLBACK(PlugSelector_UIPlugSelectedCallback), plug);

    plugselectoritem_t item;
    item.plug        = plug;
    item.gtkItem     = gtkItem;

    gtk_list_box_insert(GTK_LIST_BOX(PlugSelector), gtkItem, 0);
    g_array_append_val(PlugSelectorItems, item);
}

void PlugSelector_Create()
{
    if (PlugSelector == NULL) {
        PlugSelector = gtk_list_box_new();
    }
    if (PlugSelectorItems == NULL) {
        PlugSelectorItems = g_array_new(TRUE, TRUE, sizeof(plugselectoritem_t));
    }
    PluginManager_RegisterCallback(PlugSelector_PlugManagerLoadCallback, PLUGACTION_LOAD);
    PluginManager_RegisterCallback(PlugSelector_PlugManagerUnloadCallback, PLUGACTION_UNLOAD);
}

void PlugSelector_Destroy()
{
    if (PlugSelectorItems != NULL) {
        g_array_unref(PlugSelectorItems);
    }
    PluginManager_UnregisterCallback(PlugSelector_PlugManagerLoadCallback);
    PluginManager_UnregisterCallback(PlugSelector_PlugManagerUnloadCallback);
}
#include "plugselector.h"

GtkWidget* PlugSelector      = NULL;
GArray*    PlugSelectorItems = NULL;

GtkWidget* PlugSelector_GetWidget()
{
    return PlugSelector;
}

int PlugSelector_PlugUnloadCallback(char actionMask, plug_t* plug)
{
    printf("Unloaded %s\n", plug->pluginfo.name->str);
}

int PlugSelector_PlugLoadCallback(char actionMask, plug_t* plug)
{
    printf("Loaded %s\n", plug->pluginfo.name->str);
    PlugSelector_AddPlug(plug);
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

    GtkWidget* gtkItem = gtk_button_new_with_label(plug->pluginfo.name->str);
    gtk_widget_set_events(gtkItem, gtk_widget_get_events(gtkItem) | GDK_BUTTON_PRESS_MASK);

    g_signal_connect(gtkItem, "button-press-event", G_CALLBACK(PlugSelector_UIPlugSelectedCallback), plug);

    plugselectoritem_t item;
    item.plug        = plug;
    item.gtkItem     = gtkItem;

    gtk_container_add(GTK_CONTAINER(PlugSelector), gtkItem);
    gtk_widget_show(gtkItem);
    g_array_append_val(PlugSelectorItems, item);
}

void PlugSelector_Create()
{
    if (PlugSelector == NULL) {
        PlugSelector = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    }
    if (PlugSelectorItems == NULL) {
        PlugSelectorItems = g_array_new(TRUE, TRUE, sizeof(plugselectoritem_t));
    }

    
    PlugManager_RegisterCallback(PlugSelector_PlugLoadCallback, PLUGACTION_LOAD);
    PlugManager_RegisterCallback(PlugSelector_PlugUnloadCallback, PLUGACTION_UNLOAD);
}

void PlugSelector_Destroy()
{
    if (PlugSelectorItems != NULL) {
        g_array_unref(PlugSelectorItems);
    }
    PlugManager_UnregisterCallback(PlugSelector_PlugLoadCallback);
    PlugManager_UnregisterCallback(PlugSelector_PlugUnloadCallback);
}
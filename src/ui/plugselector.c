#include "plugselector.h"

GtkWidget* PlugSelector      = NULL;
GArray*    PlugSelectorItems = NULL;

void PlugSelector_Create()
{
    if (PlugSelector == NULL) {
        PlugSelector = gtk_list_box_new();
    }
    if (PlugSelectorItems == NULL) {
        PlugSelectorItems = g_array_new(TRUE, TRUE, sizeof(plugselectoritem_t));
    }
}

GtkWidget* PlugSelector_GetWidget()
{
    return PlugSelector;
}

gboolean PlugSelector_PlugSelectedCallback(GtkWidget* widget, plug_t* plug)
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

    g_signal_connect(gtkItem, "button-press-event", G_CALLBACK(PlugSelector_PlugSelectedCallback), plug);

    plugselectoritem_t item;
    item.plug        = plug;
    item.gtkItem     = gtkItem;

    gtk_list_box_insert(GTK_LIST_BOX(PlugSelector), gtkItem, 0);
    g_array_append_val(PlugSelectorItems, item);
}
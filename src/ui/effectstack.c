#include "effectstack.h"

GtkWidget* stackWidget    = NULL;

int Effectstack_InsertEffect(GString* effectName, gint position)
{
	if (effectName == NULL) {
		return EINVAL;
	}

	GtkWidget* effectRow   = gtk_list_box_row_new();
	GtkWidget* effectLabel = gtk_label_new(effectName->str);

    gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(effectRow), TRUE);
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(effectRow), TRUE);
    gtk_container_add(GTK_CONTAINER(effectRow), effectLabel);

    gtk_list_box_insert(GTK_LIST_BOX(stackWidget), effectRow, position);

    gtk_widget_show_all(effectRow);
}

void Effectstack_Create()
{
    if (stackWidget != NULL) {
        return;
    }

    stackWidget            = gtk_list_box_new();

    GtkWidget* headerRow   = gtk_list_box_row_new();
    
    GtkWidget* headerLabel = gtk_label_new("Effects stacked");
    gtk_widget_set_halign(headerLabel, GTK_ALIGN_CENTER); // Center the label
    
    // Unselectable and unclickable row
    gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(headerRow), FALSE);
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(headerRow), FALSE);
    gtk_container_add(GTK_CONTAINER(headerRow), headerLabel);

    gtk_list_box_prepend(GTK_LIST_BOX(stackWidget), headerRow);
}

/// @brief Return the Widget serving as the stackWidget
/// @return Imagelist
GtkWidget* Effectstack_GetWidget()
{
    return stackWidget;
}

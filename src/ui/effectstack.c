#include "effectstack.h"

GtkWidget* Effectstack = NULL;

void Effectstack_Create()
{
    if (Effectstack != NULL) {
        return;
    }

    Effectstack            = gtk_list_box_new();

    GtkWidget* headerRow   = gtk_list_box_row_new();
    
    GtkWidget* vBox        = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget* headerLabel = gtk_label_new("Effects stacked");
    gtk_widget_set_halign(headerLabel, GTK_ALIGN_CENTER);
    gtk_container_add(GTK_CONTAINER(vBox), headerLabel);
    gtk_container_add(GTK_CONTAINER(vBox), gtk_separator_new(GTK_ORIENTATION_VERTICAL));
    
    gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(headerRow), FALSE);
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(headerRow), FALSE);
    gtk_container_add(GTK_CONTAINER(headerRow), vBox);

    gtk_list_box_prepend(GTK_LIST_BOX(Effectstack), headerRow);
}

/// @brief Return the Widget serving as the Effectstack
/// @return Imagelist
GtkWidget* Effectstack_GetWidget()
{
    return Effectstack;
}
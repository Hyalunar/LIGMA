#include "filelist.h"

GtkWidget* Filebar = NULL;

void Filelist_Create()
{
    if (Filebar != NULL) {
        return;
    }

    Filebar      = gtk_list_box_new();
    
    GtkWidget* alternateText = gtk_text_view_new();
    GtkTextBuffer* buffer      = gtk_text_view_get_buffer(GTK_TEXT_VIEW(alternateText));
    gtk_text_buffer_set_text(buffer, "No Images", -1);
    gtk_list_box_set_placeholder(GTK_LIST_BOX(Filebar), alternateText);
    // Create a text view that will be shown if no elements are inside the list box
    
}

/// @brief Return the Widget serving as a filebar
/// @return Filebar
GtkWidget* Filelist_GetWidget()
{
    return Filebar;
}
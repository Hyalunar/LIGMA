#include "filebar.h"

GtkListBox* Filebar = NULL;

void Filebar_Create()
{
    if (Filebar == NULL) {
        return;
    }

    Filebar      = gtk_list_box_new();
    
    GtkTextView* alternateText = gtk_text_view_new();
    GtkTextBuffer* buffer      = gtk_text_view_get_buffer(alternateText);
    gtk_text_buffer_set_text(buffer, "No Images", -1);
    gtk_list_box_set_placeholder(Filebar, alternateText);
    // Create a text view that will be shown if no elements are inside the list box
    
}

GtkListBox* Filebar_GetWidget()
{
    return Filebar;
}
#include <gtk/gtk.h>

GtkWidget* toolbar;

void Toolbar_Create()
{
    toolbar = gtk_toolbar_new();
}

void Toolbar_Destroy()
{
    gtk_widget_destroy(toolbar);
}

GtkWidget* Toolbar_GetWidget()
{
    return toolbar;
}
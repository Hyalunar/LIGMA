#include <gtk/gtk.h>

GtkWidget* drawingArea;

void Viewport_Create()
{
    drawingArea = gtk_drawing_area_new();
}

void Viewport_Destroy()
{
    gtk_destroy_widget(drawingArea);
}
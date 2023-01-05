#include "viewport.h"

GtkWidget* drawingArea;

/**
 * @brief Callback for a buttonpress on the drawing viewport
 * 
 * @param widget Widget generating the callback
 * @param cr cairo-stuff
 * @param data data passed at signal registrations
 * @return FALSE
 */
gboolean Viewport_ButtonPressEvent_Callback(GtkWidget* widget, cairo_t* cr, gpointer data)
{
    g_print("Button-Click!\n");
    return FALSE;
}

void Viewport_Create()
{
    drawingArea = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawingArea, 300, 300);
    g_signal_connect(G_OBJECT(drawingArea), "button-release-event", G_CALLBACK(Viewport_ButtonPressEvent_Callback), NULL);
}

GtkWidget* Viewport_GetWidget()
{
    return drawingArea;
}
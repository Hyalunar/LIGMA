#include "viewport.h"

GtkWidget* drawingWidget;
cairo_surface_t* drawingSurface;

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
    printf("Button-Click!\n");
    return FALSE;
}

gboolean Viewport_MotionNotifyEvent_Callback(GtkWidget* widget, GdkEventMotion* event, gpointer data)
{
    printf("Motion-Notify!\n");
    return FALSE;
}

void Viewport_Create()
{
    drawingWidget = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawingWidget, 300, 300);
    gtk_widget_set_events(drawingWidget, gtk_widget_get_events(drawingWidget) | GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK);
    g_signal_connect(G_OBJECT(drawingWidget), "button-release-event", G_CALLBACK(Viewport_ButtonPressEvent_Callback), NULL);
    g_signal_connect(G_OBJECT(drawingWidget), "motion-notify-event", G_CALLBACK(Viewport_MotionNotifyEvent_Callback), NULL);

    drawingSurface = cairo_image_surface_create(
        CAIRO_FORMAT_ARGB32, 
        gtk_widget_get_allocated_height(drawingWidget),
        gtk_widget_get_allocated_height(drawingWidget));
}

GtkWidget* Viewport_GetWidget()
{
    return drawingWidget;
}
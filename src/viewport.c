#include "viewport.h"

GtkWidget* drawingWidget        = NULL;
cairo_surface_t* widgetSurface = NULL;

void Viewport_ClearSurface()
{
    cairo_t* cairo = cairo_create(widgetSurface); 
    // Cairo Context

    cairo_set_source_rgba(cairo, 1.0, 1.0, 1.0, 1.0);
    cairo_paint(cairo);

    cairo_destroy(cairo);
}

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

/// @brief Process Motion-Notify (Mouse-Move) Event
/// @param widget Widget receiving the event
/// @param event event containing motion-data
/// @param data passed-data, ignored
/// @return FALSE
gboolean Viewport_MotionNotifyEvent_Callback(GtkWidget* widget, GdkEventMotion* event, gpointer data)
{
    cairo_t* cairo;
    cairo = cairo_create(widgetSurface); // Surface cairo context

    cairo_rectangle(cairo, event->x - 3, event->y - 3, 7.0, 7.0);
    cairo_fill(cairo);

    cairo_destroy(cairo); // Remove cairo surface context

    gtk_widget_queue_draw(widget); // Redraw widget

    return FALSE;
}

/// @brief Configure drawing Surface when widget is ready for configuration
/// @param widget widget to configure
/// @param event configureEvent
/// @param data passed data, ignored
/// @return TRUE
gboolean Viewport_ConfigureEvent_Callback(GtkWidget* widget, GdkEventConfigure* event, gpointer data)
{
    if (widgetSurface != NULL) {
        cairo_surface_destroy(widgetSurface);
    }
    
    widgetSurface = gdk_window_create_similar_surface(
        gtk_widget_get_window(widget), 
        CAIRO_CONTENT_COLOR_ALPHA, 
        gtk_widget_get_allocated_height(drawingWidget),
        gtk_widget_get_allocated_height(drawingWidget));

    Viewport_ClearSurface();
    
    return TRUE; // Event handled
}

gboolean Viewport_Draw_Callback(GtkWidget* Widget, cairo_t* cairo, gpointer data)
{
    cairo_set_source_surface(cairo, widgetSurface, 0, 0);
    cairo_paint(cairo);

    return TRUE; //Event handled
}

void Viewport_Create()
{
    drawingWidget = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawingWidget, 300, 300);
    gtk_widget_set_events(drawingWidget, gtk_widget_get_events(drawingWidget) | GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK);
    g_signal_connect(G_OBJECT(drawingWidget), "button-release-event", G_CALLBACK(Viewport_ButtonPressEvent_Callback), NULL);
    g_signal_connect(G_OBJECT(drawingWidget), "motion-notify-event", G_CALLBACK(Viewport_MotionNotifyEvent_Callback), NULL);
    g_signal_connect(G_OBJECT(drawingWidget), "configure-event", G_CALLBACK(Viewport_ConfigureEvent_Callback), NULL);
    g_signal_connect(G_OBJECT(drawingWidget), "draw", G_CALLBACK(Viewport_Draw_Callback), NULL);

    gtk_widget_set_halign(drawingWidget, GTK_ALIGN_CENTER);
}

GtkWidget* Viewport_GetWidget()
{
    return drawingWidget;
}
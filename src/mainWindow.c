#include <stdio.h>

#include <gtk/gtk.h>

GtkWidget* window;

/**
    This acts as the entry point for the GTK-Application.
    This gets called after GTK is initialized. It performs some
    simple initialization tasks for the main window.
**/
void MainWindow_AppActivate(GtkApplication* app, gpointer user_data)
{
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "LIGMA");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_widget_show_all(window);
}

/**
    This is our GTK-Application exit point. It gets called
    if the application is asked to shut down.
**/
void MainWindow_AppShutdown(GtkApplication* app, gpointer user_data)
{
    printf("Bye!\n");
}
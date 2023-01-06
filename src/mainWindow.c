#include <stdio.h>

#include <gtk/gtk.h>

#include "toolbar.h"
#include "viewport.h"
#include "filelist.h"

GtkWidget* window;
GtkWidget* layoutBox;

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

    Toolbar_Create();
    Viewport_Create();
    Filelist_Create();

    layoutBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_box_pack_start(GTK_BOX(layoutBox), GTK_WIDGET(Toolbar_GetWidget()), 1, 1, 15U);
    // Add Toolbar to master box

    GtkWidget* lowerBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
    gtk_box_pack_start(GTK_BOX(lowerBox), Filelist_GetWidget(), TRUE, TRUE, 15);
    gtk_box_pack_start(GTK_BOX(lowerBox), Viewport_GetWidget(), TRUE, TRUE, 15);
    // Add second box to layoutBox, to align image and files

    gtk_box_pack_start(GTK_BOX(layoutBox), GTK_WIDGET(lowerBox), 1, 1, 15U);


    gtk_container_add(GTK_CONTAINER(window), layoutBox);
    // Add master box to window

    gtk_widget_show_all(window);
}

/**
    This is our GTK-Application exit point. It gets called
    if the application is asked to shut down.
**/
void MainWindow_AppShutdown(GtkApplication* app, gpointer user_data)
{
    // TODO: Do all windows close automatically?
    //gtk_window_close(GTK_WINDOW(window));
    //gtk_widget_destroy(GTK_WIDGET(window));
    printf("Bye!\n");
}
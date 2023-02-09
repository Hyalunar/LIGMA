#include <stdio.h>

#include <gtk/gtk.h>

#include "toolbar.h"
#include "viewport.h"
#include "effectstack.h"
#include "colorchooser.h"
#include "appmenu.h"
#include "plugselector.h"

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
    
    Toolbar_Create();
    Viewport_Create();
    Effectstack_Create();
    Colorchooser_Create();
    AppMenu_Create();
    PlugSelector_Create();


    layoutBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_box_pack_start(GTK_BOX(layoutBox), AppMenu_GetWidget(), TRUE, FALSE, 0U);
    gtk_box_pack_start(GTK_BOX(layoutBox), Toolbar_GetWidget(), TRUE, FALSE, 15U);
    gtk_box_pack_start(GTK_BOX(layoutBox), PlugSelector_GetWidget(), TRUE, FALSE, 15U);
    // Add Toolbar to master box

    GtkWidget* lowerBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
    gtk_box_pack_start(GTK_BOX(lowerBox), Effectstack_GetWidget(), TRUE, FALSE, 15U);
    gtk_box_pack_start(GTK_BOX(lowerBox), Viewport_GetWidget() , TRUE, FALSE, 15U);
    gtk_box_pack_start(GTK_BOX(lowerBox), Colorchooser_GetWidget(), TRUE, FALSE, 15U);
    // Add second box to layoutBox, to align image and files

    gtk_box_pack_start(GTK_BOX(layoutBox), GTK_WIDGET(lowerBox), TRUE, FALSE, 15U);


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
    // All sub-widgets of your main-widget are closed automatically
    Viewport_Destroy();
    printf("Bye!\n");
}
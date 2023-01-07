#include <stdio.h>

#include "toolbar.h"

GtkWidget* toolbar;

/** The Toolbar Items **/
GtkToolItem* tbOpenFile;
GtkToolItem* tbSaveFile;
GtkToolItem* tbNewFile;

/** The OnClick methods **/
void Toolbar_TbNew_Onclick()
{
    printf("New File!\n");
}

void Toolbar_TbOpen_Onclick()
{
    printf("Opening File!\n");
    //TODO: Open FileChooserDialog and evaluate it
}

void Toolbar_TbSave_Onclick()
{
    printf("Saving File!\n");
    //TODO: open FileChooserDialog and evaluate it
}

void Toolbar_Create()
{
    toolbar = gtk_toolbar_new();

    /** Init the toolbar items  **/
    tbNewFile  = gtk_tool_button_new(NULL, "New");
    tbOpenFile = gtk_tool_button_new(NULL, "Open");
    tbSaveFile = gtk_tool_button_new(NULL, "Save");
    g_signal_connect(G_OBJECT(tbNewFile),  "clicked", G_CALLBACK(Toolbar_TbNew_Onclick), NULL);
    g_signal_connect(G_OBJECT(tbOpenFile), "clicked", G_CALLBACK(Toolbar_TbOpen_Onclick), NULL);
    g_signal_connect(G_OBJECT(tbSaveFile), "clicked", G_CALLBACK(Toolbar_TbSave_Onclick), NULL);
    gtk_container_add(GTK_CONTAINER(toolbar), GTK_WIDGET(tbNewFile));
    gtk_container_add(GTK_CONTAINER(toolbar), GTK_WIDGET(tbOpenFile));
    gtk_container_add(GTK_CONTAINER(toolbar), GTK_WIDGET(tbSaveFile));
}

GtkWidget* Toolbar_GetWidget()
{
    return toolbar;
}
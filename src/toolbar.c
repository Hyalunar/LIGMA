#include <stdio.h>

#include "toolbar.h"

GtkWidget* toolbar;

/** The Toolbar Items **/
GtkToolItem* tbOpen;
GtkToolItem* tbSave;
GtkToolItem* tbNew;

/** The OnClick methods **/
void Toolbar_TbNew_Onclick()
{
    printf("New File!\n");
}

void Toolbar_TbOpen_Onclick()
{
    printf("Opening File!\n");
}

void Toolbar_TbSave_Onclick()
{
    printf("Saving File!\n");
}

void Toolbar_Create()
{
    toolbar = gtk_toolbar_new();

    /** Init the toolbar items  **/
    tbNew  = gtk_tool_button_new(NULL, "New");
    tbOpen = gtk_tool_button_new(NULL, "Open");
    tbSave = gtk_tool_button_new(NULL, "Save");
    g_signal_connect(G_OBJECT(tbNew), "clicked", G_CALLBACK(Toolbar_TbNew_Onclick), NULL);
    g_signal_connect(G_OBJECT(tbOpen), "clicked", G_CALLBACK(Toolbar_TbOpen_Onclick), NULL);
    g_signal_connect(G_OBJECT(tbSave), "clicked", G_CALLBACK(Toolbar_TbSave_Onclick), NULL);
    gtk_container_add(GTK_CONTAINER(toolbar), GTK_WIDGET(tbNew));
    gtk_container_add(GTK_CONTAINER(toolbar), GTK_WIDGET(tbOpen));
    gtk_container_add(GTK_CONTAINER(toolbar), GTK_WIDGET(tbSave));
}

GtkWidget* Toolbar_GetWidget()
{
    return toolbar;
}
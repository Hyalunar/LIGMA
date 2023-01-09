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
    //TODO: Check for memory leaks
    printf("Opening File!\n");
    GtkFileChooserNative* fileDialog;
    GtkFileChooser*       fileChooser;
    GtkFileFilter*        fileFilter;
    fileDialog = gtk_file_chooser_native_new(
        "Select file to Open",
        NULL,
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "Load",
        "Cancel");
    
    fileChooser = GTK_FILE_CHOOSER(fileDialog);
    gtk_file_chooser_set_select_multiple(fileChooser, TRUE);

    fileFilter = gtk_file_filter_new();
    gtk_file_filter_add_mime_type(fileFilter, "image/png");
    gtk_file_filter_add_mime_type(fileFilter, "image/svg+xml");
    gtk_file_filter_add_mime_type(fileFilter, "image/pdf");
    
    gtk_file_chooser_set_filter(fileChooser, fileFilter);

    gint response = gtk_native_dialog_run(GTK_NATIVE_DIALOG(fileDialog));

    if (response == GTK_RESPONSE_ACCEPT) {
        GSList* fileNames = gtk_file_chooser_get_filenames(fileChooser);
        g_slist_free_full(fileNames, free);
    }
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
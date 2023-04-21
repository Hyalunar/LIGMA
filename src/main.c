#include <gtk/gtk.h>
#include "ui/mainWindow.h"
#include "logic/plugManager.h"

int main(int argc, char** argv)
{
    GtkApplication* app;
    int status;

    PlugManager_Create();

    app = gtk_application_new("org.ligma", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(MainWindow_AppActivate), NULL);
    g_signal_connect(app, "shutdown", G_CALLBACK(MainWindow_AppShutdown), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    PlugManager_Destroy();

    return status;
}

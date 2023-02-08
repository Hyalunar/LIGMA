#ifndef APPMENU_H
#define APPMENU_H

#include <gtk/gtk.h>

#include "../logic/plugManager.h"
#include "pluginlister.h"

void AppMenu_Create();
GtkWidget* AppMenu_GetWidget();

#endif // APPMENU_H
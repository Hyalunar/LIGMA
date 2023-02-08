#ifndef PLUGSELECTOR_H
#define PLUGSELECTOR_H

#include <gtk/gtk.h>
#include "../logic/plugManager.h"

typedef struct PlugSelectorItem {
    GtkWidget* gtkItem;
    plug_t*    plug;
} plugselectoritem_t;

void PlugSelector_Create();
GtkWidget* PlugSelector_GetWidget();

int  PlugSelector_AddPlug();

#endif
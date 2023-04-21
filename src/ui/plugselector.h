#ifndef PLUGSELECTOR_H
#define PLUGSELECTOR_H

#include <gtk/gtk.h>
#include "../logic/plugManager.h"
#include "../ui/effectstack.h"

typedef struct PlugSelectorItem {
    GtkWidget* gtkItem;
    GString*   plugName;
} plugselectoritem_t;

void PlugSelector_Create();
GtkWidget* PlugSelector_GetWidget();

int  PlugSelector_AddPlug();

#endif

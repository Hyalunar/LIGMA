#ifndef EFFECTSTACK_H
#define EFFECTSTACK_H

#include <gtk/gtk.h>

void Effectstack_Create();
GtkWidget* Effectstack_GetWidget();

int Effectstack_InsertEffect(GString* effectName, gint position);

#endif // EFFECTSTACK_H

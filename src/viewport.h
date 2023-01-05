#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <stdio.h>

#include <gtk/gtk.h>
#include <cairo/cairo.h>

void Viewport_Create();
GtkWidget* Viewport_GetWidget();

#endif // VIEWPORT_H
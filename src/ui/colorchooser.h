#ifndef COLORCHOOSER_H
#define COLORCHOOSER_H

#include <gtk/gtk.h>

void Colorchooser_Create();
GtkWidget* Colorchooser_GetWidget();
GtkWidget* Colorbutton1_GetWidget();
GtkWidget* Colorbutton2_GetWidget();

GdkRGBA Colorchooser_GetPrimaryRGBA();
GdkRGBA Colorchooser_GetSecondaryRGBA();
void    Colorchooser_RotateColors();

#endif

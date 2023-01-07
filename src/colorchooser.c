#include "colorchooser.h"

GtkWidget* Colorchooser = NULL;
GtkWidget* Colorbutton1 = NULL;
GtkWidget* Colorbutton2 = NULL;

void Colorbuttons_Create()
{
    GdkRGBA startColor;
    if (Colorbutton1 == NULL) {
        startColor.red   = 0.0;
        startColor.green = 0.0;
        startColor.blue  = 0.0;
        startColor.alpha = 1.0;
        Colorbutton1 = gtk_color_button_new_with_rgba(&startColor);
    }

    if (Colorbutton2 == NULL) {
        startColor.red   = 1.0;
        startColor.green = 1.0;
        startColor.blue  = 1.0;
        startColor.alpha = 1.0;
        Colorbutton2 = gtk_color_button_new_with_rgba(&startColor);
    }
}

void Colorchooser_RotateColors()
{
    GdkRGBA primary;
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(Colorbutton1), &primary);
    GdkRGBA secondary;
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(Colorbutton2), &secondary);

    gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(Colorbutton1), &secondary);
    gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(Colorbutton2), &primary);
}

void Colorchooser_Create()
{
    Colorbuttons_Create();
    if (Colorchooser != NULL) {
        return;
    }
    
    Colorchooser = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

    gtk_container_add(GTK_CONTAINER(Colorchooser), gtk_label_new("Primary"));
    gtk_container_add(GTK_CONTAINER(Colorchooser), Colorbutton1);
    gtk_container_add(GTK_CONTAINER(Colorchooser), gtk_label_new("Secondary"));
    gtk_container_add(GTK_CONTAINER(Colorchooser), Colorbutton2);

    GtkWidget* rotateButton = gtk_button_new_with_mnemonic("_Rotate");
    g_signal_connect(G_OBJECT(rotateButton), "clicked", G_CALLBACK(Colorchooser_RotateColors), NULL);
    gtk_container_add(GTK_CONTAINER(Colorchooser), rotateButton);
}

GtkWidget* Colorchooser_GetWidget()
{
    return Colorchooser;
}

GtkWidget* Colorbutton1_GetWidget()
{
    return Colorbutton1;
}

GtkWidget* Colorbutton2_GetWidget()
{
    return Colorbutton2;
}

GdkRGBA Colorchooser_GetPrimaryRGBA()
{
    GdkRGBA rgba;
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(Colorbutton1), &rgba);
    return rgba;
}

GdkRGBA Colorchooser_GetSecondaryRGBA()
{
    GdkRGBA rgba;
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(Colorbutton2), &rgba);
    return rgba;
}
#include "sdk/ligmaPlug.h"

#include <stdio.h>


int Ligma_OnLoad()
{
    printf("Hello World!\n");
    return 0;
}

int Ligma_OnUnload()
{
    printf("Hello World!");
    return 0;
}

int Ligma_GetPlugInfo(pluginfo_t* pluginfo)
{
    pluginfo->name      = g_string_new("Hello World Plug");
    pluginfo->about     = g_string_new("This is the Hello World Plug");
    pluginfo->publisher = g_string_new("Hyalunar");
    pluginfo->arguments = g_array_new(TRUE, TRUE, sizeof(argument_t));
    return 0;
}

int Ligma_Process(image_t* image)
{
    return 0;
}
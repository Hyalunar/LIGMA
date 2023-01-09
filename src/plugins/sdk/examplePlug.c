#include <stdio.h>

#include "ligmaPlug.h"

void Ligma_OnLoad()
{
    printf("Loaded ExamplePlug!\n");
}

void Ligma_OnUnload()
{
    printf("Unloaded ExamplePlug!\n");
}

void Ligma_GetPluginInfo()
{
    
}

void Ligma_Process(int width, int height, char* bitmap)
{
    printf("ExamplePlug: Processing Image with size(%i, %i)\n", width, height);
}
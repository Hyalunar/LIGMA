#include <stdio.h>

#include "ligmaPlug.h"

PARAMETERS_BEGIN()
ADD_PARAMETER("TestParameter", float)
ADD_PARAMETER("AnotherTestParameter", int)
PARAMETERS_END()

void Ligma_OnLoad()
{
    printf("Loaded ExamplePlug!\n");
}

void Ligma_OnUnload()
{
    printf("Unloaded ExamplePlug!\n");
}

char* Ligma_GetPluginInfo()
{
    printf(metadata);
    return metadata;
}

void Ligma_Process(image_t* image)
{
    printf("ExamplePlug: Processing Image with size(%i, %i)\n", image->height, image->width);
}
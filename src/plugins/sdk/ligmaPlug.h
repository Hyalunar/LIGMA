#ifndef LIGMAPLUG_H
#define LIGMAPLUG_H

/**
    This is the interface for building a plugin for the IGMA LIGMA.
    In here, all necessary methods for building a functional plugin are
    provided. 
**/

void Ligma_OnLoad();
void Ligma_OnUnload();
void Ligma_GetParameters();
void Ligma_Process(int width, int height, char* bitmap);

#endif // LIGMAPLUG_H
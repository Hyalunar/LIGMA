#ifndef LIGMAPLUG_H
#define LIGMAPLUG_H

/**
    This is the interface for building a plugin for the IGMA LIGMA.
    In here, all necessary methods for building a functional plugin are
    provided. 
**/

extern void Ligma_OnLoad();
extern void Ligma_OnUnload();
extern void Ligma_GetPluginInfo();
extern void Ligma_Process(int width, int height, char* bitmap);

#endif // LIGMAPLUG_H
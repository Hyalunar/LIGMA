#ifndef LIGMAPLUG_H
#define LIGMAPLUG_H

/**
    This is the interface for building a plugin for the IGMA LIGMA.
    In here, all necessary methods for building a functional plugin are
    provided. 
**/

#include "../../logic/image.h"

#define PARAMETERS_BEGIN() char* metadata = 
#define ADD_PARAMETER(n, t) n "," #t "|"
#define PARAMETERS_END() ;

extern void  Ligma_OnLoad();
extern void  Ligma_OnUnload();
extern char* Ligma_GetPluginInfo();
extern void  Ligma_Process(image_t* image);

#endif // LIGMAPLUG_H
#ifndef PLUGMANAGER_H
#define PLUGMANAGER_H

#include <glib.h>
#include <dlfcn.h>

#include "../plugins/sdk/ligmaPlug.h"

typedef struct Plug {
    #ifdef __unix__
    void* dll;
    #elif _WIN32
    HANDLE dll;
    #endif

    pluginfo_t pluginfo;

} plug_t;

void Init_PlugManager();
int  Load_PlugByPath(char* path);

#endif // PLUGINMANAGER_H
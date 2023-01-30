#ifndef PLUGMANAGER_H
#define PLUGMANAGER_H

#include <glib.h>
#include <dlfcn.h>

#include <stdio.h>

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
void Destroy_PlugManager();

int  Load_PlugByPath(char* path);
int  Unload_PlugByName(GString* name);

void PlugError(char* s);

#endif // PLUGINMANAGER_H
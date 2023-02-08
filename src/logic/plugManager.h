#ifndef PLUGMANAGER_H
#define PLUGMANAGER_H

#include <stdio.h>
#include <glib.h>

#ifdef __unix__
#include <dlfcn.h>
#elif _WIN32
#include <Windows.h>
#endif

#include "../plugins/sdk/ligmaPlug.h"

typedef struct Plug {
    #ifdef __unix__
    void* dll;
    #elif _WIN32
    HANDLE dll;
    #endif

    pluginfo_t pluginfo;
} plug_t;

void PluginManager_Init();
void PluginManager_Destroy();

int  PluginManager_LoadByPath(char* path);
int  PluginManager_UnloadByName(GString* name);
GArray* PluginManager_GetPluginList();

void PluginManager_PlugError(char* s);

#endif // PLUGINMANAGER_H
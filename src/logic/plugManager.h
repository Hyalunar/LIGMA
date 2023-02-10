#ifndef PLUGMANAGER_H
#define PLUGMANAGER_H

#include <stdio.h>
#include <glib.h>
#include <stdbool.h>

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

#define PLUGACTION_LOAD    0b1
#define PLUGACTION_UNLOAD  0b01
#define PLUGACTION_PROCESS 0b01
#define PLUGACTION_ALL     0b11111111

typedef struct PlugCallback {
    int (*callback) (char, plug_t*);
    char actions;
} plugcallback_t;

void PluginManager_Create();
void PluginManager_Destroy();

int  PluginManager_LoadByPath(char* path);
int  PluginManager_UnloadByName(GString* name);

void PluginManager_RegisterCallback(int (*function) (char, plug_t*), char actionMask);
int  PluginManager_UnregisterCallback(int (*function) (char, plug_t*));
void PluginManager_DoCallback(char eventActionMask, plug_t* plug);

void PluginManager_PlugError(char* s);

#endif // PLUGINMANAGER_H
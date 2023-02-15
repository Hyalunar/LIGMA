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

typedef int (*OnLoadFunc)   (void);
typedef int (*OnUnloadFunc) (void);
typedef int (*GetInfoFunc)  (pluginfo_t*);
typedef int (*ProcessFunc)  (image_t*);

typedef struct Plug {
    OnLoadFunc   loadFunction;
    OnUnloadFunc unloadFunction;
    GetInfoFunc  infoFunction;
    ProcessFunc  processFunction;

    #ifdef __unix__
    void* dll;
    #elif _WIN32
    HANDLE dll;
    #endif

    pluginfo_t pluginfo;
} plug_t;

#define PLUGACTION_LOAD    0b00000001 // Fires after the Plug is initialized but before it is added to the plug Array
#define PLUGACTION_UNLOAD  0b00000010 // Fires after the Plugs OnUnload Function was called but before it is removed from the plug Array
#define PLUGACTION_PROCESS 0b00000100 // Fires before the Plugs Ligma_Process is called
#define PLUGACTION_ALL     0b11111111 // See notes at other Actions

typedef struct PlugCallback {
    int (*callback) (char, plug_t*);
    char actions;
} plugcallback_t;

void PlugManager_Create();
void PlugManager_Destroy();

int  PlugManager_LoadByPath(char* path);
int  PlugManager_UnloadByName(GString* name);

int  PlugManager_PlugByName(GString* name, plug_t* plugLocation);

void PlugManager_RegisterCallback(int (*function) (char, plug_t*), char actionMask);
int  PlugManager_UnregisterCallback(int (*function) (char, plug_t*));
void PlugManager_DoCallback(char eventActionMask, plug_t* plug);

void PlugManager_PlugError(char* s);

#endif // PLUGINMANAGER_H
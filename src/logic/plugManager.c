#include "plugManager.h"

GArray* plugArray     = NULL;
GArray* callbackArray = NULL;

/** @brief Initialize the global Plug Manager to render it able to manage the applications plugs **/
void PluginManager_Create()
{
    if (plugArray == NULL) {
        plugArray = g_array_new(FALSE, FALSE, sizeof(plug_t));
    }
    if (callbackArray == NULL) {
        callbackArray = g_array_new(FALSE, FALSE, sizeof(plugcallback_t));
    }
}

void PluginManager_Destroy()
{
    if (plugArray != NULL) {
        // Free Memory allocated by elements
        for (guint i = 0; i < plugArray->len; i++) {
            plug_t* plug = &g_array_index(plugArray, plug_t, i);
            
            dlclose(plug->dll);
            g_string_free(plug->pluginfo.about, TRUE);
            g_string_free(plug->pluginfo.name, TRUE);
            g_string_free(plug->pluginfo.publisher, TRUE);
            g_array_free(plug->pluginfo.arguments, TRUE);
        }

        g_array_unref(plugArray);
    }
    if (callbackArray != NULL) {
        g_array_unref(callbackArray);
    }
}

guint PluginManager_CallbackIndexByFunction(int (*function) (char, plug_t*))
{
    guint index = callbackArray->len + 1;
    bool found  = false;
    plugcallback_t plug;
    for (guint i = 0; (i < callbackArray->len) && (!found); i++) {
        plug  = g_array_index(callbackArray, plugcallback_t, i);
        found = plug.callback == function;
        index = found ? i : index;
    }

    return index;
}

/// @brief Iterate over all registered callback functions and call those that match the eventActionMask
/// @param eventActionMask mask to be matched by a callback
/// @param plug Plug to be passed as an argument when the callback is called
void PluginManager_DoCallback(char eventActionMask, plug_t* plug)
{
    plugcallback_t plugCallback;
    for (guint i = 0; i < callbackArray->len; i++) {
        plugCallback = g_array_index(callbackArray, plugcallback_t, i);
        if (eventActionMask & plugCallback.actions) {
            plugCallback.callback(eventActionMask, plug);
        }
    }
}

/// @brief Unregister a Plug identified by its function address
/// @param function callback function address
/// @return EINVAL: invalid function argument
/// @return ENOMEDIUM: No callback with the specified attributes could be found
/// @return EXIT_SUCCESS: Success, get it?
int PluginManager_UnregisterCallback(int (*function) (char, plug_t*))
{
    if (function == NULL) {
        return EINVAL;
    }

    guint index = PluginManager_CallbackIndexByFunction(function);
    if (index >= callbackArray->len) {
        return ENOMEDIUM;
    }

    g_array_remove_index_fast(callbackArray, index);

    return EXIT_SUCCESS;
}

/// @brief Register a callback at the PlugManager to be called when a specified event occurs
/// @param function callback function
/// @param actionMask mask including only the actions this plug should be called with
void PluginManager_RegisterCallback(int (*function) (char, plug_t*), char actionMask)
{
    plugcallback_t plugCallback;
    plugCallback.callback = function;
    plugCallback.actions  = actionMask;
    g_array_append_val(callbackArray, plugCallback);
}

/** @brief Error Handling for the Plug Manager
    @param s **/
void PluginManager_PlugError(char *s)
{
    puts(s);
}

int PlugManager_LoadPlugFunctions(plug_t* plug)
{
    #ifdef __unix__
        plug->loadFunction    = dlsym(plug->dll, "Ligma_OnLoad");
        plug->unloadFunction  = dlsym(plug->dll, "Ligma_OnUnload");
        plug->infoFunction    = dlsym(plug->dll, "Ligma_GetPlugInfo");
        plug->processFunction = dlsym(plug->dll, "Ligma_Process");
    #elif _WIN32

    #endif

    if (plug->loadFunction == NULL || plug->unloadFunction == NULL || plug->infoFunction == NULL || plug->processFunction == NULL) {
        return ENXIO;
    }

    return EXIT_SUCCESS;
}

/** @brief Load a Plug with a given path
    @param path plugin to load
    @return EINVAL, ENXIO, EXIT_SUCCESS
    The error code ... is returned when:
    EINVAL:    Failed to load plug
    ENXIO:     Could not find symbol within dll
    ECANCELED: Plugin operation failed **/
int PluginManager_LoadByPath(char *path)
{
    plug_t plug;

    #ifdef __unix__
        /* funky linux stuff */

        plug.dll = NULL;
        plug.dll = dlopen(path, RTLD_NOW);
        if (plug.dll == NULL)
        {
            return EINVAL;
        }
    
    #elif _WIN32
        /** sadly windows stuff **/
        // TODO: Find someone to do this for me
    #endif

    // Load Plug-Functions provided by the SharedObject File
    if (PlugManager_LoadPlugFunctions(&plug) == ENXIO) {
        dlclose(plug.dll);
        return ENXIO;
    }

    // Retrieve Plug Information from the provided function
    if (plug.infoFunction(&plug.pluginfo)) {
        dlclose(plug.dll);
        return ECANCELED;
    }

    PluginManager_DoCallback(PLUGACTION_LOAD, &plug);
    g_array_append_val(plugArray, plug);
}

/// @brief Unload a Plug identified by its name
/// @param name Name of the Plug to unload
/// @return ENOMEDIUM: No such plugin was found
/// @return EINVAL: GString was invalid
/// @return EXIT_SUCCESS: Operation performed successfully
int PluginManager_UnloadByName(GString* name)
{
    plug_t* plug;
    guint   plugIndex;
    for (guint plugIndex = 0; plugIndex < plugArray->len; plugIndex++) {
        plug = &g_array_index(plugArray, plug_t, plugIndex);
        GString* plugName = plug->pluginfo.name;
        if (g_string_equal(name, plugName)) {
            break;
        }
    }

    if (plugIndex < plugArray->len) {
        return ENOMEDIUM;
    }


    PluginManager_DoCallback(PLUGACTION_UNLOAD, plug);

    #ifdef __unix__
    dlclose(plug->dll);
    
    #elif _WIN32

    #endif

    plug->dll = NULL;
    g_string_free(plug->pluginfo.about,     TRUE);
    g_string_free(plug->pluginfo.name,      TRUE);
    g_string_free(plug->pluginfo.publisher, TRUE);
    g_array_unref(plug->pluginfo.arguments);
    return EXIT_SUCCESS;
}
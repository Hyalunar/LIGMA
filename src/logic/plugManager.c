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
        g_array_unref(plugArray);
        //TODO: Add proper element free
    }
    if (callbackArray != NULL) {
        g_ptr_array_unref,(callbackArray);
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

int PluginManager_UnregisterCallback(int (*function) (char, plug_t*))
{
    guint index = PluginManager_CallbackIndexByFunction(function);
    if (index == callbackArray->len + 1) {
        return EINVAL;
    }

    g_array_remove_index_fast(callbackArray, index);

    return EXIT_SUCCESS;
}

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
    /** Loaded Plug **/

    /** TODO: Make cleanup in return clauses **/

    /** Get info Function **/
    dlerror(); /** Clear the error **/
    int (*getPlugInfoFunc)(pluginfo_t *) = dlsym(plug.dll, "Ligma_GetPlugInfo");
    if (getPlugInfoFunc == NULL)
    {
        PluginManager_PlugError(dlerror());
        return ENXIO;
    }

    if (getPlugInfoFunc(&(plug.pluginfo)))
    {
        PluginManager_PlugError("Failed to load Plugin info");
        return ECANCELED;
    }

    dlerror();
    int (*plugOnLoadFunc)(void) = dlsym(plug.dll, "Ligma_OnLoad");
    if (plugOnLoadFunc == NULL)
    {
        PluginManager_PlugError(dlerror());
        return ENXIO;
    }

    if (plugOnLoadFunc())
    {
        PluginManager_PlugError("Loading the plug failed.");
        return ECANCELED;
    }

#elif _WIN32
/** sadly windows stuff **/
// TODO: Find someone to do this for me
#endif

    PluginManager_DoCallback(PLUGACTION_LOAD, &plug);
    g_array_append_val(plugArray, plug);
}
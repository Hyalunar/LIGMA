#include "plugManager.h"

GArray*    plugArray     = NULL;
GPtrArray* callbackArray = NULL;

/** @brief Initialize the global Plug Manager to render it able to manage the applications plugs **/
void PluginManager_Init()
{
    if (plugArray == NULL) {
        plugArray = g_array_new(FALSE, FALSE, sizeof(plug_t));
    }
    if (callbackArray == NULL) {
        callbackArray = g_ptr_array_new();
    }
}

void PluginManager_Destroy()
{
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

    g_array_append_val(plugArray, plug);
}
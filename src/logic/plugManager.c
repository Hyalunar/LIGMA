#include "plugManager.h"

GArray* plugArray = NULL;

/// @brief Initialize the global Plug Manager to render it able to manage the applications plugs
void Init_PlugManager()
{
    if (plugArray != NULL) {
        return;
    }
    plugArray = g_array_new(FALSE, FALSE, sizeof(plug_t));
}

/// @brief Error Handling for the Plug Manager
/// @param s 
void PlugError(char* s)
{
    printf(s);
}

/// @brief Load a Plug with a given path
/// @param path plugin to load
/// @return EINVAL, ENXIO, EXIT_SUCCESS
int Load_PlugByPath(char* path)
{
    plug_t plug;

    #ifdef __unix__
    /* funky linux stuff */

    plug.dll = NULL;
    plug.dll = dlopen(path, RTLD_NOW);
    if (plug.dll == NULL) {
        return EINVAL;
    }
    // Loaded Plug

    // Get info Function
    dlerror(); // Clear the error
    int (*getPlugInfoFunc) (pluginfo_t*) = dlsym(plug.dll, "Ligma_GetPlugInfo");
    if (getPlugInfoFunc == NULL) {
        PlugError(dlerror());
        return ENXIO;
    }

    if (getPlugInfoFunc(&(plug.pluginfo))) {
        PlugError("Failed to load Plugin");
        return ECANCELED;
    }

    #elif  _WIN32
    /* sadly windows stuff */
    //TODO: Find someone to do this for me
    #endif

    g_array_append_val(plugArray, plug);
}
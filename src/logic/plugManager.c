#include "plugManager.h"

GArray* plugArray = NULL;

void Init_PlugManager()
{
    if (plugArray != NULL) {
        return;
    }
    plugArray = g_array_new(FALSE, FALSE, sizeof(plug_t));
}

/// @brief Load a Plug with a given path
/// @param path plugin to load
/// @return EINVAL, EXIT_SUCCESS
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

    #elif  _WIN32
    /* sadly windows stuff */
    //TODO: Find someone to do this for me
    #endif

    g_array_append_val(plugArray, plug);
}
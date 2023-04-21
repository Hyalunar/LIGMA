#ifndef LIGMAPLUG_H
#define LIGMAPLUG_H

/**
    This is the interface for building a plugin for the IGMA LIGMA.
    In here, all necessary methods for building a functional plugin are
    provided. 
**/

#include "../../logic/image.h"

#include <glib.h>
#include <stdint.h>
#include <float.h>

typedef struct PlugInfo {
    GString* name;
    GString* displayName;
    GString* about;
    GString* publisher;
    GArray*  arguments;
} pluginfo_t;

typedef enum PlugArgumentType {
    ARGUMENTTYPE_BOOL,
    ARGUMENTTYPE_UINT32,
    ARGUMENTTYPE_INT32,
    ARGUMENTTYPE_FLOAT,
    ARGUMENTTYPE_DOUBLE,
    ARUGMENTTYPE_STRING,
    ARGUMENTTYPE_INTRANGE,
    ARGUMENTTYPE_FLOATRANGE
} argument_t;

typedef struct IntRange {
    int32_t min;
    int32_t max;
} intrange_t;

typedef struct FloatRange {
    float min;
    float max;
} floatrange_t;

typedef struct PlugArgument {
    /** @brief name of the argument **/
    GString* name;
    /** @brief Message to be displayed to the user **/
    GString* userMessage;
    /** @brief Type of the argument **/
    argument_t type;
    /** @brief Segment for data only needed for special argument types **/
    union {
        intrange_t intRange;
        floatrange_t floatRange;
    } extradata;
} plugargument_t;

/** @brief Function to be executed when the plugin is loaded **/
extern int  Ligma_OnLoad();

/** @brief Function to be executed when the plugin is unloaded **/
extern int  Ligma_OnUnload();

/** @brief Function to inform the application about the plug
    @param pluginfo struct containing information about the plug
    @return error codes **/
extern int  Ligma_GetPlugInfo(pluginfo_t* pluginfo);

/** @brief Function exposed by the Plug which is called to process images
    @param image image to be processed
    @return error codes **/
extern int  Ligma_Process(image_t* image);

#endif // LIGMAPLUG_H

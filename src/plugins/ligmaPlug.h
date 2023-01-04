/**
    This is the interface for building a plugin for the IGMA LIGMA.
    In here, all necessary methods for building a functional plugin are
    provided. 
**/

void Ligma_OnLoad();
void Ligma_OnUnload();
void Ligma_GetParameters();
void Ligma_Process(int width, int size, char* bitmap);
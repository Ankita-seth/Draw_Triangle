#include "framework.h"

int WINAPI WinMain(HINSTANCE hInstance,    //Main windows function
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd)

{
    Triangle* triangle = new Triangle();
    if (triangle)
    {
        // create the window
        if (!triangle->InitializeWindow(hInstance, nShowCmd, triangle->FullScreen))
        {
            MessageBox(0, L"Window Initialization - Failed",
                L"Error", MB_OK);
            return 1;
        }

        // initialize direct3d
        if (!triangle->InitD3D())
        {
            MessageBox(0, L"Failed to initialize direct3d 12",
                L"Error", MB_OK);
            triangle->Cleanup();
            return 1;
        }

        // start the main loop
        triangle->mainloop();

        // we want to wait for the gpu to finish executing the command list before we start releasing everything
        triangle->WaitForPreviousFrame();

        // close the fence event
        CloseHandle(triangle->fenceEvent);

        // clean up everything
        triangle->Cleanup();
    }
    delete triangle;
    triangle = NULL;
    return 0;
}
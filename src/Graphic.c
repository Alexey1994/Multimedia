#include "Graphic.h"

#include <windows.h>
#include <GL/gl.h>


static void init_OpenGL()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //glShadeModel(GL_SMOOTH);
    //glEnable(GL_DEPTH_TEST);
    //glFrontFace(GL_CW);
    //glEnable(GL_CULL_FACE);
    //glEnable(GL_COLOR_MATERIAL);
    //glEnable(GL_NORMALIZE);

    glEnable(GL_TEXTURE_2D);
}


static LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CLOSE:   PostQuitMessage(0); break;
        case WM_DESTROY: return 0;
        default:         return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}


static void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    *hDC = GetDC(hwnd);

    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize      = sizeof(pfd);
    pfd.nVersion   = 1;
    pfd.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    *hRC = wglCreateContext(*hDC);
    wglMakeCurrent(*hDC, *hRC);
}


static void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}


static void draw_thread(void (*draw)())
{
    WNDCLASSEX     wcex;
    HWND           hwnd;
    HDC            hDC;
    HGLRC          hRC;
    MSG            msg;

    wcex.cbSize        = sizeof(WNDCLASSEX);
    wcex.style         = CS_OWNDC;
    wcex.lpfnWndProc   = WindowProc;
    wcex.cbClsExtra    = 0;
    wcex.cbWndExtra    = 0;
    wcex.hInstance     = 0;
    wcex.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName  = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);;


    if(!RegisterClassEx(&wcex))
        return 0;

    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          256,
                          256,
                          NULL,
                          NULL,
                          0,
                          NULL);

    ShowWindow(hwnd, 1);
    EnableOpenGL(hwnd, &hDC, &hRC);
    init_OpenGL();

    for(;;)
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_QUIT)
                break;
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            draw();

            SwapBuffers(hDC);
            Sleep(1);
        }
    }

    DisableOpenGL(hwnd, hDC, hRC);
    DestroyWindow(hwnd);
}


void init_graphic(void(*draw)())
{
    run_thread(draw_thread, draw);
}

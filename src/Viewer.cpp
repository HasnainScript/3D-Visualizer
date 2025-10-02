#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
#include <V3d_Viewer.hxx>
#include <V3d_View.hxx>
#include <WNT_Window.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <TopoDS_Shape.hxx>
#include "Viewer.h"

void Viewer::displayShape(const TopoDS_Shape& shape) {
    // 1?? Create display connection and OpenGL driver
    Handle(Aspect_DisplayConnection) disp = new Aspect_DisplayConnection();
    Handle(Graphic3d_GraphicDriver) driver = new OpenGl_GraphicDriver(disp);

    // 2?? Create 3D viewer
    Handle(V3d_Viewer) viewer = new V3d_Viewer(driver);

    // 3?? Create interactive context
    Handle(AIS_InteractiveContext) context = new AIS_InteractiveContext(viewer);

    // 4?? Create a Win32 window
    WNDCLASS wc{};
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"OCCTWindow";
    RegisterClass(&wc);

    HWND hwnd = CreateWindow(
        wc.lpszClassName,
        L"OCCT 3D Viewer",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        nullptr, nullptr, wc.hInstance, nullptr
    );

    Handle(WNT_Window) wind = new WNT_Window(hwnd);

    // 5?? Create the view
    Handle(V3d_View) view = viewer->CreateView();
    view->SetWindow(wind);

    if (!wind->IsMapped()) wind->Map();

    // 6?? Display the shape
    Handle(AIS_Shape) aisShape = new AIS_Shape(shape);
    context->Display(aisShape, Standard_True);

    view->FitAll();
    viewer->Update();

    // 7?? Standard Windows message loop (keeps window open & interactive)
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        viewer->Redraw(); // refresh view continuously
    }
}

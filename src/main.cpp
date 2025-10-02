#include <vtkActor.h>
#include <vtkConeSource.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkNew.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkLight.h>

int main()
{
    // --- First object: Cone ---
    vtkNew<vtkConeSource> cone;
    cone->SetHeight(3.0);
    cone->SetRadius(1.0);
    cone->SetResolution(30);

    vtkNew<vtkPolyDataMapper> coneMapper;
    coneMapper->SetInputConnection(cone->GetOutputPort());

    vtkNew<vtkActor> coneActor;
    coneActor->SetMapper(coneMapper);
    coneActor->GetProperty()->SetColor(1.0, 0.2, 0.2); // red
    coneActor->SetPosition(-2, 0, 0); // move left

    // --- Second object: Sphere ---
    vtkNew<vtkSphereSource> sphere;
    sphere->SetRadius(1.0);
    sphere->SetThetaResolution(30);
    sphere->SetPhiResolution(30);

    vtkNew<vtkPolyDataMapper> sphereMapper;
    sphereMapper->SetInputConnection(sphere->GetOutputPort());

    vtkNew<vtkActor> sphereActor;
    sphereActor->SetMapper(sphereMapper);
    sphereActor->GetProperty()->SetColor(0.2, 0.6, 1.0); // blue
    sphereActor->SetPosition(2, 0, 0); // move right

    // --- Renderer + Window + Interactor ---
    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(coneActor);
    renderer->AddActor(sphereActor);
    renderer->SetBackground(0.2, 0.6, 0.4); // dark gray

    vtkNew<vtkLight> light;
	light->SetLightTypeToSceneLight();
	light->SetPosition(0, 5, 5);
	light->SetFocalPoint(0, 0, 0);
	light->SetColor(1, 1, 1);
	light->SetIntensity(1);

	renderer->AddLight(light);

    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(800, 600);

    vtkNew<vtkRenderWindowInteractor> interactor;
    interactor->SetRenderWindow(renderWindow);

	vtkNew<vtkInteractorStyleTrackballCamera> style;
	interactor->SetInteractorStyle(style);

    // Render + Start interaction
    renderWindow->Render();
    interactor->Start();

    return 0;
}

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
#include <vtkSliderWidget.h>
#include <vtkSliderRepresentation2D.h>
#include <vtkCommand.h>
#include <string>
#include <vtkCallbackCommand.h>

// Struct to hold data for slider callback
struct ConeSliderData {
    vtkConeSource* cone;
    vtkRenderWindow* renderWindow;
};

// Callback function for slider interaction
void ConeResolutionCallback(vtkObject* caller, long unsigned int, void* clientData, void*)
{
    vtkSliderWidget* sliderWidget = static_cast<vtkSliderWidget*>(caller);
    vtkSliderRepresentation* sliderRep = static_cast<vtkSliderRepresentation*>(sliderWidget->GetRepresentation());
    double value = sliderRep->GetValue();

    ConeSliderData* data = static_cast<ConeSliderData*>(clientData);
    data->cone->SetResolution(static_cast<int>(value));
    data->renderWindow->Render(); // update render window
}

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
    coneActor->SetPosition(-2, 0, 0);

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
    sphereActor->SetPosition(2, 0, 0);

    // --- Renderer + Window + Interactor ---
    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(coneActor);
    renderer->AddActor(sphereActor);
    renderer->SetBackground(0.2, 0.6, 0.4);

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

    // --- Slider Representation ---
    vtkNew<vtkSliderRepresentation2D> sliderRep;
    sliderRep->SetMinimumValue(3);
    sliderRep->SetMaximumValue(60);
    sliderRep->SetValue(30);
    sliderRep->SetTitleText("Cone Resolution");
    sliderRep->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedDisplay();
    sliderRep->GetPoint1Coordinate()->SetValue(0.1, 0.05);
    sliderRep->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedDisplay();
    sliderRep->GetPoint2Coordinate()->SetValue(0.4, 0.05);
    sliderRep->SetSliderLength(0.02);
    sliderRep->SetSliderWidth(0.03);
    sliderRep->SetEndCapLength(0.01);
    sliderRep->SetEndCapWidth(0.03);
    sliderRep->SetTubeWidth(0.005);
    sliderRep->SetLabelFormat("%0.0f");

    // --- Slider Widget ---
    vtkNew<vtkSliderWidget> sliderWidget;
    sliderWidget->SetInteractor(interactor);
    sliderWidget->SetRepresentation(sliderRep);
    sliderWidget->SetAnimationModeToAnimate();
    sliderWidget->EnabledOn();

    // --- Connect slider to cone ---
    ConeSliderData sliderData;
    sliderData.cone = cone;
    sliderData.renderWindow = renderWindow;

    // Create a callback object
    vtkNew<vtkCallbackCommand> sliderCallback;
    sliderCallback->SetClientData(&sliderData);
    sliderCallback->SetCallback(ConeResolutionCallback);

    // Add observer using the callback object
    sliderWidget->AddObserver(vtkCommand::InteractionEvent, sliderCallback);

    // --- Render + Start interaction ---
    renderWindow->Render();
    interactor->Start();

    return 0;
}

#include "GeometryEngine.h"
#include <BRepPrimAPI_MakeBox.hxx>

TopoDS_Shape GeometryEngine::createBox(double dx, double dy, double dz) {
    return BRepPrimAPI_MakeBox(dx, dy, dz).Shape();
}

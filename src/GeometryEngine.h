#pragma once
#include <TopoDS_Shape.hxx>

class GeometryEngine {
public:
    GeometryEngine() = default;
    ~GeometryEngine() = default;

    TopoDS_Shape createBox(double dx, double dy, double dz);
};

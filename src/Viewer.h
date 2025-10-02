#pragma once
#include <TopoDS_Shape.hxx>

class Viewer {
public:
    Viewer() = default;
    ~Viewer() = default;

    void displayShape(const TopoDS_Shape& shape);
};

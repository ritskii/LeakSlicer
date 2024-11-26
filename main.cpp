#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>

struct Point {
    float X, Y, Z;

    Point(float x, float y, float z) : X(x), Y(y), Z(z) {}

    Point(float* XYZ) {
        X = XYZ[0];
        Y = XYZ[1];
        Z = XYZ[2];
    }
};

struct Triangle {
    Point Normal, V1, V2, V3;

    Triangle(Point normal, Point v1, Point v2, Point v3)
        : Normal(normal), V1(v1), V2(v2), V3(v3) {}
};

#include "Model.hpp"
#include "Importer.hpp"


int main() {
    Model Dataset;
    Importer Import("Dataset.stl", &Dataset);

    for(const auto& Tr : Dataset.Faces) {
        std::cout << Tr.Normal.X << " " << Tr.Normal.Y << " " << Tr.Normal.Z << std::endl;
    }

    return 0;
}

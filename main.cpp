#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <array>
#include <openstl/core/stl.h>

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
#include "Slicer.hpp"

void example() {
    std::ifstream file("../Dataset.stl", std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file '" << "../Dataset.stl" << "'" << std::endl;
    }

    // Deserialize the triangles in either binary or ASCII format
    std::vector<openstl::Triangle> triangles = openstl::deserializeStl(file);
    for(const auto& el : triangles) {
        std::cout << el.normal.z << std::endl;
    }
    file.close();
}

int main() {
    Model Dataset;
    Importer Handler("../Dataset.stl");
    Handler.importSTL(&Dataset);

    Handler.exportSTL("../FinalTest.stl", &Dataset);

    Slicer Sl(0.3, Dataset);

    return 0;
}

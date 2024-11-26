#ifndef MODEL_HPP
#define MODEL_HPP

class Model {
public:
    int Count;
    std::vector<Triangle> Faces;

    float findMin() {
        float Min = INT_MAX;

        for (const auto& Elem : Faces) {
            Min = std::min({Min, Elem.V1.Z, Elem.V2.Z, Elem.V3.Z});
        }

        return Min;
    }

    float findMax() {
        float Max = INT_MIN;

        for (const auto& Elem : Faces) {
            Max = std::max({Max, Elem.V1.Z, Elem.V2.Z, Elem.V3.Z});
        }

        return Max;
    }
};

#endif //MODEL_HPP

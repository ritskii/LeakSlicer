#ifndef SLICER_HPP
#define SLICER_HPP

class Slicer {
public:
    Slicer(float LayerHeight, Model& Data) {
        float Min = Data.findMin() + 0.3;
        float Max = Data.findMax();
        int NumLayers = std::ceil((Max - Min) / LayerHeight);
        std::vector<float> LayersHeight(NumLayers);

        std::vector<std::pair<float, float>> Intersections;

        for(int I = 0; I < LayersHeight.size(); I++) {
            LayersHeight[I] = Min + I * LayerHeight;
            std::cout << LayersHeight[I] << std::endl;
            for(const Triangle& Elem : Data.Faces) {
                if((Elem.V1.Z < LayersHeight[I] && Elem.V2.Z > LayersHeight[I])
                || (Elem.V1.Z > LayersHeight[I] && Elem.V2.Z < LayersHeight[I])) {
                    float T = (LayersHeight[I] - Elem.V1.Z) / (Elem.V2.Z - Elem.V1.Z);
                    float XIntersect = Elem.V1.X + T * (Elem.V2.X - Elem.V1.X);
                    float YIntersect = Elem.V1.Y + T * (Elem.V2.Y - Elem.V1.Y);
                    Intersections.push_back({XIntersect, YIntersect});
                }
            }
        }
        for (const auto& El : Intersections) {
            std::cout << El.first << " " << El.second << std::endl;
        }
    }
};

#endif //SLICER_HPP

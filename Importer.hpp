#ifndef IMPORTER_HPP
#define IMPORTER_HPP

class Importer {
public:
    std::ifstream File;

    Importer(const std::string& Path) {
        File.open(Path, std::ios::binary);
        if (!File.is_open()) {
            throw std::runtime_error("Failed to open file: " + Path);
        }
    }

    void importSTL(Model* Model) {
        File.seekg(80, std::ios::cur);

        File.read(reinterpret_cast<char*>(&Model->Count), sizeof(Model->Count));

        for (int i = 0; i < Model->Count; ++i) {
            float Normal[3], V1[3], V2[3], V3[3];
            File.read(reinterpret_cast<char*>(Normal), sizeof(Normal));
            File.read(reinterpret_cast<char*>(V1), sizeof(V1));
            File.read(reinterpret_cast<char*>(V2), sizeof(V2));
            File.read(reinterpret_cast<char*>(V3), sizeof(V3));

            std::cout << "Normal: (" << Normal[0] << ", " << Normal[1] << ", " << Normal[2] << ")\n";
            std::cout << "V1: (" << V1[0] << ", " << V1[1] << ", " << V1[2] << ")\n";
            std::cout << "V2: (" << V2[0] << ", " << V2[1] << ", " << V2[2] << ")\n";
            std::cout << "V3: (" << V3[0] << ", " << V3[1] << ", " << V3[2] << ")\n";

            File.seekg(2, std::ios::cur);

            Model->Faces.emplace_back(Point(Normal), Point(V1), Point(V2), Point(V3));
        }

        std::cout << "Model loaded successfully! \n";
    }

    void exportSTL(const std::string& Path, const Model* Model) {
        std::ofstream File(Path, std::ios::binary);
        if (!File.is_open()) {
            throw std::runtime_error("Failed to open file for writing: " + Path);
        }

        char header[80] = {0};
        File.write(header, sizeof(header));

        File.write(reinterpret_cast<const char*>(&Model->Count), sizeof(Model->Count));

        for (const auto& Face : Model->Faces) {
            float Normal[3] = {Face.Normal.X, Face.Normal.Y, Face.Normal.Z};
            float V1[3] = {Face.V1.X, Face.V1.Y, Face.V1.Z};
            float V2[3] = {Face.V2.X, Face.V2.Y, Face.V2.Z};
            float V3[3] = {Face.V3.X, Face.V3.Y, Face.V3.Z};

            File.write(reinterpret_cast<const char*>(Normal), sizeof(Normal));
            File.write(reinterpret_cast<const char*>(V1), sizeof(V1));
            File.write(reinterpret_cast<const char*>(V2), sizeof(V2));
            File.write(reinterpret_cast<const char*>(V3), sizeof(V3));

            File.write(reinterpret_cast<const char*>("\x01\x02"), 2);
        }

        std::cout << "Model exported successfully to " << Path << "!\n";
    }

    ~Importer() {
        if (File.is_open()) {
            File.close();
        }
    }
};


#endif //IMPORTER_HPP

#ifndef IMPORTER_HPP
#define IMPORTER_HPP

class Importer {
public:
    std::ifstream File;

    Importer(const std::string& Path, Model* Model) {
        File.open(Path, std::ios::binary);
        if (!File.is_open()) {
            throw std::runtime_error("Failed to open file: " + Path);
        }
        File.seekg(80, std::ios::cur);

        File.read(reinterpret_cast<char*>(&Model->Count), sizeof(Model->Count));

        for (int i = 0; i < Model->Count; ++i) {
            float Normal[3], V1[3], V2[3], V3[3];
            File.read(reinterpret_cast<char*>(Normal), sizeof(Normal));
            File.read(reinterpret_cast<char*>(V1), sizeof(V1));
            File.read(reinterpret_cast<char*>(V2), sizeof(V2));
            File.read(reinterpret_cast<char*>(V3), sizeof(V3));

            int attributeByteCount;
            File.read(reinterpret_cast<char*>(&attributeByteCount), sizeof(attributeByteCount));

            Model->Faces.emplace_back(Point(Normal), Point(V1), Point(V2), Point(V3));
        }

        std::cout << "Model loaded successfully! \n";
    }

    ~Importer() {
        if (File.is_open()) {
            File.close();
        }
    }
};


#endif //IMPORTER_HPP

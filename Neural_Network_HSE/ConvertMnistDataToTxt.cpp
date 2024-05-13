#include <fstream>
#include <iostream>

int ReadInt(std::ifstream &in) {
    uint8_t byte;
    int res = 0;
    for (size_t i = 0; i < 4; ++i) {
        in >> byte;
        res = (res << 8) + byte;
    }
    return res;
}

void WriteImages(std::ifstream &in, std::ofstream &out) {
    int magic = ReadInt(in);
    size_t n = ReadInt(in), rows = ReadInt(in), cols = ReadInt(in);
    out << n << " " << rows << " " << cols << "\n";
    for (size_t i = 0; i < n; ++i) {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                uint8_t byte;
                in >> byte;
                out << static_cast<double>(byte) / 255 << " ";
            }
            out << "\n";
        }
        out << "\n";
    }
    in.close();
    out.close();
}

void WriteLabels(std::ifstream &in, std::ofstream &out) {
    int magic = ReadInt(in);
    size_t n = ReadInt(in);
    out << n << "\n";
    for (size_t i = 0; i < n; ++i) {
        uint8_t byte;
        in >> byte;
        out << static_cast<int>(byte) << "\n";
    }
    in.close();
    out.close();
}

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-i") && strcmp(argv[i], "-l")) {
            std::cout << "Неверный аргумент " << argv[i] << "\n";
            continue;
        }
        std::ifstream in;
        in.open(argv[i + 1]);
        if (!in.is_open()) {
            std::cout << "Не удалось открыть файл " << argv[i + 1] << "\n";
            continue;
        }
        std::ofstream out;
        std::string new_name = argv[i + 1];
        new_name += ".txt";
        out.open(new_name);
        if (!out.is_open()) {
            std::cout << "Не удалось создать файл " << new_name << "\n";
            in.close();
            continue;
        }
        if (!strcmp(argv[i], "-i")) {
            WriteImages(in, out);
        } else {
            WriteLabels(in, out);
        }
    }
}

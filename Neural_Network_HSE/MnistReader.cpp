#include <vector>
#include <fstream>
#include <iostream>
#include <string>

struct DigitData {
    std::vector<std::vector<double>> pixels;
    int digit;
};

std::vector<DigitData> ReadDigits(const std::string& filename) {
    std::ifstream fin;
    fin.open(filename);
    if (!fin.is_open()) {
        std::cout << "Error openning the  " << filename << " digits file for reading digits\n";
        system("pause");
        return;
    }
    int size;
    fin >> size;
    int n, m;
    fin >> n >> m;
    std::vector<DigitData> digits(size);

    for (size_t i = 0; i < size; ++i) {
        DigitData digit;
        digit.pixels.resize(n, std::vector<double>(m));
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                fin >> digit.pixels[i][j];
            }
        }
        digits[i] = digit;
    }
    std::cout << "Цифры прочитаны\n";
    return digits;
}

void ReadLabels(const std::string& filename, std::vector<DigitData>& digits) {
    std::ifstream fin;
    fin.open(filename);
    if (!fin.is_open()) {
        std::cout << "Error openning the  " << filename << " labels file for reading labels\n";
        system("pause");
        return;
    }
    int size;
    fin >> size;
    for (size_t i = 0; i < size; ++i) {
        fin >> digits[i].digit;
    }
}

#include <vector>
#include <fstream>
#include <iostream>
#include <string>

struct DigitData {
    std::vector<std::vector<double>> pixels;
    int digit;
};

std::vector<DigitData> ReadDigits(const std::string& filename) {


    std::cout << "цифры прочитаны\n";
    return ...
}
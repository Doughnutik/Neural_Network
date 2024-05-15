#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct DigitData {
    std::vector<double> pixels;
    int digit;
};

std::vector<DigitData> ReadDigits(const std::string &filename);

void ReadLabels(const std::string &filename, std::vector<DigitData> &digits);

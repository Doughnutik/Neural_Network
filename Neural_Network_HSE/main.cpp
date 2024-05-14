#include "Network.h"
#include "MnistReader.cpp"

#include <iostream>
#include <fstream>
#include <string>

enum class FileType {
    Config, Data
};

void Train(const std::string& data_file, const std::string& train_digits_file, const std::string& train_labels_file, FileType filetype) {
    Network nw;
    if (filetype == FileType::Config) {
        nw.ReadConfig(data_file);
    }
    else {
        nw.ReadData(data_file);
    }

    std::vector<DigitData> digits = ReadDigits(train_digits_file);  // считываем цифры
    ReadLabels(train_labels_file, digits);

    int n = digits.size();
    std::cout << "Начинаем обучение\n";
    std::vector<int> results = nw.Train(digits);
    std::cout << "Обучение закончено\n";
    
    std::cout << "Если хотите сохранить данные сети, введи файл, куда это сделать, либо -, если не требуется\n";
    std::string save_file;
    std::cin >> save_file;
    if (save_file == "-") {
        return;
    }
    nw.SaveData(save_file);
}

void Test(const std::string& data_file, const std::string& test_digits_file, const std::string& test_labels_file) {
    Network nw;
    nw.ReadData(data_file);

    std::vector<DigitData> digits = ReadDigits(test_digits_file);  // считываем цифры
    ReadLabels(test_labels_file, digits);

    int n = digits.size();
    std::cout << "Начинаем тестирование\n";
    std::vector<int> results = nw.Test(digits);
    std::cout << "Тестирование закончено\n";

    for (int i = 0; i < n - 1; ++i) {
        std::cout << "Предсказано: " << results[i] << " Должно быть: " << digits[i].digit << "\n";
    }

    std::cout << "Точность " << results.back() / n << "\n";
}

int main(int argc, char* argv[]) {
    if (argc != 5 && argc != 6) {
        std::cout << "Неверное количество аргументов\n";
        exit(0);
    }
    std::string process(argv[1]);
    if (process != "train" && process != "test") {
        std::cout << "Первый аргумент test или train\n";
        exit(0);
    }
    if (process == "train") {  // training
        if (argc != 5) {
            std::cout << "Неверное количество аргументов\n";
            exit(0);
        }
        if (argv[2] != "-c" && argv[2] != "-d") {
            std::cout << "В случае обучения, второй аргумент -c или -d\n";
            exit(0);
        }
        std::string data_file(argv[3]);
        std::string train_digits_file(argv[4]);
        std::string train_labels_file(argv[5]);
        if (argv[2] == "-c") {  // config
            Train(data_file, train_digits_file, train_labels_file, FileType::Config);
        }
        else {  // data
            Train(data_file, train_digits_file, train_labels_file, FileType::Data);
        }
    }
    else {  // testing
        std::string data_file(argv[2]);
        std::string test_digits_file(argv[3]);
        std::string test_labels_file(argv[4]);
        Test(data_file, test_digits_file, test_labels_file);
    }
}
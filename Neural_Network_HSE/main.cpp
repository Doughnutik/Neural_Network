#include "Network.h"

#include <fstream>
#include <iostream>
#include <string>

enum class FileType { Config, Data };

void Train(const std::string &data_file, const std::string &train_digits_file,
           const std::string &train_labels_file, FileType filetype) {
    Network nw;
    if (filetype == FileType::Config) {
        nw.ReadConfig(data_file);
    } else {
        nw.ReadData(data_file);
    }

    std::vector<DigitData> digits =
        ReadDigits(train_digits_file); // считываем цифры
    ReadLabels(train_labels_file, digits);

    std::cout << "Начинаем обучение\n";
    nw.Train(digits);
    std::cout << "Обучение закончено\n";

    std::cout << "Если хотите сохранить данные сети, введи файл, куда это "
                 "сделать, либо -, если не требуется\n";
    std::string save_file;
    std::cin >> save_file;
    if (save_file == "-") {
        return;
    }
    nw.SaveData(save_file);
}

void Test(const std::string &data_file, const std::string &test_digits_file,
          const std::string &test_labels_file) {
    Network nw;
    nw.ReadData(data_file);

    std::vector<DigitData> digits =
        ReadDigits(test_digits_file); // считываем цифры
    ReadLabels(test_labels_file, digits);

    size_t n = digits.size();
    std::cout << "Начинаем тестирование\n";
    std::vector<int> results = nw.Test(digits);
    std::cout << "Тестирование закончено\n";

    // for (size_t i = 0; i < n; ++i) {
    //     std::cout << "Предсказано: " << results[i]
    //               << " Должно быть: " << digits[i].digit << "\n";
    // }

    std::cout << "Точность " << static_cast<double>(results.back()) / n << "\n";
}

int main() {
    std::cout << "Введите, желаете ли обучить модель или протестировать "
                 "(train, test)\n";
    std::string process;
    std::cin >> process;

    if (process != "train" && process != "test") {
        std::cout << "Введите test или train\n";
        exit(0);
    }
    if (process == "train") { // training
        std::cout
            << "Введите, будете задавать config фалом или data фалом (c, d)\n";
        char c;
        std::cin >> c;
        if (c != 'c' && c != 'd') {
            std::cout << "Введите c или d\n";
            exit(0);
        }

        std::cout << "Введите путь до файла (абсолютный или относительный)\n";
        std::string data_file;
        std::cin >> data_file;

        std::cout << "Введите путь до файла с пикселями цифр (абсолютный или "
                     "относительный)\n";
        std::string train_digits_file;
        std::cin >> train_digits_file;

        std::cout << "Введите путь до файла с цифрами (абсолютный или "
                     "относительный)\n";
        std::string train_labels_file;
        std::cin >> train_labels_file;

        if (c == 'c') { // config
            Train(data_file, train_digits_file, train_labels_file,
                  FileType::Config);
        } else { // data
            Train(data_file, train_digits_file, train_labels_file,
                  FileType::Data);
        }
    } else { // testing
        std::cout << "Введите путь до файла (абсолютный или относительный)\n";
        std::string data_file;
        std::cin >> data_file;

        std::cout << "Введите путь до файла с пикселями цифр (абсолютный или "
                     "относительный)\n";
        std::string test_digits_file;
        std::cin >> test_digits_file;

        std::cout << "Введите путь до файла с цифрами (абсолютный или "
                     "относительный)\n";
        std::string test_labels_file;
        std::cin >> test_labels_file;
        Test(data_file, test_digits_file, test_labels_file);
    }
}

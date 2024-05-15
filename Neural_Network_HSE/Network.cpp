#include "Network.h"

#include <chrono>
#include <fstream>
#include <iostream>

void Network::Init(size_t num_layers, const std::vector<int> num_neurons,
                   const std::string &func_name, double rate) {
    num_layers_ = num_layers;
    num_neurons_ = num_neurons;
    layers_.resize(num_layers - 1, Layer());
    for (int i = 0; i < num_layers - 1; ++i) {
        layers_[i].Init(num_neurons[i + 1], num_neurons[i], Filling::Random);
    }

    neurons_values_.resize(num_layers, Vector());
    neurons_errors_.resize(num_layers, Vector());
    sum_values_.resize(num_layers, Vector());

    for (int i = 0; i < num_layers; ++i) {
        neurons_values_[i].Init(num_neurons[i]);
        neurons_errors_[i].Init(num_neurons[i]);
        if (i) { // на 0 слое не нужны суммы нейронов
            sum_values_[i].Init(num_neurons[i]);
        }
    }

    learning_rate_ = rate;
    func_ = func_names_map.at(func_name).first;
    der_ = func_names_map.at(func_name).second;
    func_name_ = func_name;
}

void Network::PrintData() { // вывести количество нейронов на каждом слое
    std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
    std::cout << num_layers_ << "слоёв нейросети\n";
    for (size_t i = 0; i < num_layers_; ++i) {
        std::cout << "На " << i << " слоё " << num_neurons_[i] << " нейронов\n";
    }
    std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
}

void Network::PrintValues(size_t id) { // вывести значения нейронов на слое id
    std::cout << "$$$   Values   $$$\n";
    for (size_t i = 0; i < num_neurons_[id]; ++i) {
        std::cout << i << " " << neurons_values_[id][i] << "\n";
    }
    std::cout << "$$$$$$$$$$$$$$$$$$\n";
}

void Network::LoadData(const std::vector<double> &vec) {
    neurons_values_[0] =
        Vector(vec); // загрузка первого слоя нейронов как картинки 28x28 в виде
                     // вектора из 784 даблов
}

int Network::Propagate() { // функция прямого распространения
    for (size_t i = 1; i < num_layers_; ++i) {
        sum_values_[i] =
            (layers_[i - 1].GetWeights() * neurons_values_[i - 1]) +
            layers_[i - 1].GetBias();               // Ax + b = z
        neurons_values_[i] = func_(sum_values_[i]); // func(z)
    }
    std::pair<int, double> p = neurons_values_[num_layers_ - 1]
                                   .FindMax(); // нашли предсказанную цифру и
                                               // значение нейрона в этой цифре.
    return p.first; // вернули предсказанную цифру.
}

void Network::BackPropagate(int expect) {
    // Пусть слои нейронов нумеруются 0, 1, ..., l - 1, слои весов
    // соответственно 0, 1, ..., l - 2 Пусть веса будут обозначатся w_i_j^l,
    // b_j^l. Нейроны a_i^l. (l - номер слоя). Тогда z_i^l = w_0_i^{l-1} *
    // a_0^{l-1} + ... + w_k_i^{l-1} * a_k^{l-1} + b_i^{l-1}, a_i^l =
    // func(z_i^l), где k - кол-во нейронов на l-1 слое.
    Vector expect_values(10);
    expect_values[expect] = 1; // правильный вектор ответа
    neurons_errors_[num_layers_ - 1] =
        (neurons_values_[num_layers_ - 1] - expect_values) *
        2; // посчитали dC / da^{l-1}
    sum_values_[num_layers_ - 1] =
        der_(sum_values_[num_layers_ - 1]); // z^{l-1} -> der(z^{l-1})
    for (int l = num_layers_ - 2; l >= 0; --l) {
        size_t n = num_neurons_[l];
        sum_values_[l] = der_(sum_values_[l]); // z^l -> der(z^l)
        for (size_t b = 0; b < num_neurons_[l]; ++b) {
            neurons_errors_[l][b] = 0;
            for (size_t k = 0; k < num_neurons_[l + 1]; ++k) {
                neurons_errors_[l][b] +=
                    neurons_errors_[l + 1][k] * sum_values_[l + 1][k] *
                    layers_[l].GetWeights()[b][k]; // посчитали ошибки нейронов
                // dC / da_b^l = sum_k dC / da_k^{l+1} * da_k^{l+1} / dz_k^{l+1}
                // * dz_k^{l+1} / da_b^l = = sum_k dC / da_k^{l+1} * da_k^{l+1}
                // * der(z_k^{l+1}) * w_b_k^l
            }
        }
    }

    for (int l = num_layers_ - 2; l >= 0; --l) {
        std::pair<size_t, size_t> sizes = layers_[l].GetSize();
        size_t rows = sizes.first, cols = sizes.second;
        for (size_t a = 0; a < rows; ++a) {
            for (size_t b = 0; b < cols; ++b) {
                double delta_w = neurons_errors_[l + 1][b] *
                                 sum_values_[l + 1][b] * neurons_values_[l][a];
                layers_[l].ChangeWeights()[a][b] -= delta_w * learning_rate_;
            }
            double delta_b = neurons_errors_[l + 1][a] * sum_values_[l + 1][a];
            layers_[l].ChangeBias()[a] -= delta_b * learning_rate_;
            // посчитали изменения весов
            // dC / dw_a_b^l = dC / da_b^{l+1} * da_b^{l+1} / dz_b^{l+1} *
            // dz_b^{l+1} / dw_a_b^l = dC / da_b^{l+1} * der(z_b^{l+1}) * a_a^l
            // dC / db_a^l = dC / da_b^{l+1} * da_b^{l+1} / dz_b^{l+1} *
            // dz_b^{l+1} / db_a^l = dC / da_b^{l+1} * der(z_b^{l+1}) * 1
            // w_a_b^l = w_a_b^l - dC / dw_a_b^l * learning_rate
            // b_a^l = b_a^l - dC / db_a^l * learning_rate
        }
    }
}

void Network::SaveData(
    const std::string &filename) { // сохраняем значения нейросети в файл
    std::ofstream fout;
    fout.open(filename);
    if (!fout.is_open()) {
        std::cout << "Error openning the  " << filename
                  << "  data file for saving data\n";
        system("pause");
        return;
    }
    fout << num_layers_ << " " << learning_rate_
         << "\n"; // сохраняем кол-во слоёв, скорость обучения
    for (size_t i = 0; i < num_layers_; ++i) {
        fout << num_neurons_[i] << " "; // сохраняем количества нейронов
    }
    fout << "\n";
    for (int i = 0; i < num_layers_ - 1; ++i) {
        fout << layers_[i].GetWeights() << "\n"; // сохраняем матрицы весов
    }

    for (int i = 0; i < num_layers_ - 1; ++i) {
        fout << layers_[i].GetBias() << "\n"; // сохраняем вектора сдвигов
    }
    fout << func_name_ << "\n"; // сохраняем название функции активации
                                // (sigmoida, relu, th, ...)
    std::cout << "Data saved\n";
    fout.close();
}

void Network::ReadData(
    const std::string &filename) { // читаем значения нейросети из файла
    std::ifstream fin;
    fin.open(filename);
    if (!fin.is_open()) {
        std::cout << "Error openning the  " << filename
                  << "  data file for reading data\n";
        system("pause");
        return;
    }
    fin >> num_layers_ >>
        learning_rate_; // читаем кол-во слоёв, скорость обучения
    num_neurons_.resize(num_layers_);
    layers_.resize(num_layers_ - 1, Layer());

    for (size_t i = 0; i < num_layers_; ++i) {
        fin >> num_neurons_[i]; // читаем количества нейронов
    }
    for (int i = 0; i < num_layers_ - 1; ++i) {
        layers_[i].Init(num_neurons_[i + 1], num_neurons_[i], Filling::Zeroes);
    }

    for (int i = 0; i < num_layers_ - 1; ++i) {
        fin >> layers_[i].ChangeWeights(); // читаем матрицы весов
    }
    for (int i = 0; i < num_layers_ - 1; ++i) {
        fin >> layers_[i].ChangeBias(); // читаем вектора сдвигов
    }

    fin >> func_name_; // считываем название функции активации
    func_ = func_names_map.at(func_name_).first;
    der_ = func_names_map.at(func_name_).second;
    std::cout << "Data read\n";

    neurons_values_.resize(num_layers_, Vector());
    neurons_errors_.resize(num_layers_, Vector());
    sum_values_.resize(num_layers_, Vector());

    for (int i = 0; i < num_layers_; ++i) {
        neurons_values_[i].Init(num_neurons_[i]);
        neurons_errors_[i].Init(num_neurons_[i]);
        if (i) { // на 0 слое не нужны суммы нейронов
            sum_values_[i].Init(num_neurons_[i]);
        }
    }

    std::cout << "Data uploaded\n";
    fin.close();
}

void Network::ReadConfig(const std::string &filename) {
    std::ifstream fin;
    fin.open("Config.txt");
    if (!fin.is_open()) {
        std::cout << "Error openning the  " << filename
                  << "  config file for reading config\n";
        system("pause");
        return;
    }
    size_t num_layers;
    std::vector<int> num_neurons;
    std::string func_name;
    double rate;

    fin >> num_layers >> rate; // читаем кол-во слоёв, скорость обучения
    num_neurons.resize(num_layers);
    for (size_t i = 0; i < num_layers; ++i) {
        fin >> num_neurons[i]; // читаем количества нейронов
    }
    fin >> func_name; // считываем название функции активации
    std::cout << "Config read\n";
    Init(num_layers, num_neurons, func_name, rate);
    std::cout << "Config uploaded\n";
    fin.close();
}

void Network::SaveConfig(const std::string &filename) {
    std::ofstream fout;
    fout.open(filename);
    if (!fout.is_open()) {
        std::cout << "Error openning the  " << filename
                  << "  config file for saving config\n";
        system("pause");
        return;
    }
    fout << num_layers_ << " " << learning_rate_
         << "\n"; // сохраняем кол-во слоёв, скорость обучения
    for (size_t i = 0; i < num_layers_; ++i) {
        fout << num_neurons_[i] << " "; // сохраняем количества нейронов
    }
    fout << "\n";
    fout << func_name_ << "\n"; // сохраняем название функции активации
                                // (sigmoida, relu, th, ...)
    std::cout << "Config saved\n";
    fout.close();
}

void Network::Train(const std::vector<DigitData> &digits) {
    const size_t epoch = 20;
    size_t n = digits.size();
    PrintData();
    double rate = learning_rate_;
    double lambda = exp(-1 / epoch);

    auto begin_time = std::chrono::steady_clock::now();
    for (size_t e = 1; e <= epoch; ++e) {
        for (size_t i = 0; i < n; ++i) {
            LoadData(digits[i].pixels);
            int predict = Propagate(); // здесь не нужен
            BackPropagate(digits[i].digit);
        }
        learning_rate_ *= lambda;
        auto cur_time = std::chrono::steady_clock::now();
        std::cout << "Пошло " << e << " эпох. Затрачено "
                  << cur_time - begin_time << " времени\n";
    }
    learning_rate_ = rate;
}

std::vector<int> Network::Test(const std::vector<DigitData> &digits) {
    size_t n = digits.size();
    std::vector<int> results(n + 1);

    for (size_t i = 0; i < n; ++i) {
        LoadData(digits[i].pixels);
        int predict = Propagate();
        results[i] = predict;
    }

    int cnt = 0;
    for (size_t i = 0; i < n; ++i) {
        cnt += (results[i] == digits[i].digit);
    }
    results[n] = cnt;
    return results;
}

// TODO добавить learning rate в backpropagation

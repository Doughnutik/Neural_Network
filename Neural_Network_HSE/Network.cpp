#include "Network.h"

#include <fstream>
#include <iostream>

void Network::Init(size_t num_layers, const std::vector<int> num_neurons,
                   const function& func, const derivative& der, const std::string& func_name, double rate) {
    num_layers_ = num_layers;
    num_neurons_ = num_neurons;
    layers_.resize(num_layers - 1, Layer());
    for (int i = 0; i < num_layers - 1; ++i) {
        layers_[i].Init(num_neurons[i + 1], num_neurons[i]);
    }

    neurons_values_.resize(num_layers, Vector());
    neurons_deltas_.resize(num_layers, Vector());

    for (int i = 0; i < num_layers; ++i) {
        neurons_values_[i].Init(num_neurons[i]);
        neurons_deltas_[i].Init(num_neurons[i]);
    }

    learning_rate_ = rate;
    func_ = func;
    der_ = der;
    func_name_ = func_name;
}

void Network::PrintData() {  // вывести количество нейронов на каждом слое
    std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
    std::cout << num_layers_ << "слоёв нейросети\n";
    for (size_t i = 0; i < num_layers_; ++i) {
        std::cout << "На " << i << " слоё " << num_neurons_[i] << " нейронов\n";
    }
    std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
}

void Network::PrintValues(size_t id) {  // вывести значения нейронов на слое id
    std::cout << "$$$   Values   $$$\n";
    for (size_t i = 0; i < num_neurons_[id]; ++i) {
        std::cout << i << " " << neurons_values_[id][i] << "\n";
    }
    std::cout << "$$$$$$$$$$$$$$$$$$\n";
}

void Network::LoadData(const std::vector<double> &vec) {
    neurons_values_[0] = Vector(vec);  // загрузка первого слоя нейронов как картинки 28x28 в виде вектора из 784 даблов
}

int Network::Propagate() {  // функция прямого распространения
    for (size_t i = 1; i < num_layers_; ++i) {
        Vector res =
            (layers_[i - 1].GetWeights() * neurons_values_[i - 1]) + layers_[i - 1].GetBias();  // Ax + b
        res = func_(res);  // func(x)
        neurons_values_[i] = res;  // вычислили значения нейронов на новом слое.
    }
    std::pair<int, double> p = neurons_values_[num_layers_ - 1].FindMax();  // нашли предсказанную цифру и значение нейрона в этой цифре.
    return p.first;  // вернули предсказанную цифру.
}

void Network::BackPropagate(int expect) {
    for (size_t i = 0; i < num_neurons_[num_layers_ - 1]; ++i) {
        if (i != expect) {
            neurons_errors_[num_layers_ - 1][i] =
                neurons_values_[num_layers_ - 1][i] *
                layers_[num_layers_ - 2].act_func_(
                    neurons_values_[num_layers_ - 1][i], true);
        } else {
            neurons_errors_[num_layers_ - 1][i] =
                (1.0 - neurons_values_[num_layers_ - 1][i]) *
                layers_[num_layers_ - 2].act_func_(
                    neurons_values_[num_layers_ - 1][i], true);
        }
    }
    for (int i = num_layers_ - 2; i >= 0; --i) {
        neurons_errors_[i] = layers_[i].aT_ * neurons_errors_[i + 1];
        for (int j = 0; j < num_neurons_[i]; j++) {
            neurons_errors_[i][j] *=
                layers_[i].act_func_(neurons_errors_[i][j], true);
        }
    }
}

void Network::WeightUpdate() {
    for (int i = 0; i < num_layers_ - 1; ++i) {
        for (int j = 0; j < num_neurons_[i + 1]; ++j) {
            for (int k = 0; k < num_neurons_[i]; ++k) {
                layers_[i].a_[j][k] += neurons_values_[i][k] *
                                       neurons_errors_[i + 1][j] *
                                       learning_rate_;
            }
        }
    }
    for (int i = 0; i < num_layers_ - 1; i++) {
        for (int k = 0; k < num_neurons_[i + 1]; k++) {
            layers_[i].b_[k] += neurons_errors_[i + 1][k] * learning_rate_;
        }
    }
}

void Network::SaveData() {  // сохраняем значения нейросети в файл
    std::ofstream fout;
    fout.open("Data.txt");
    if (!fout.is_open()) {
        std::cout << "Error reading the file";
        system("pause");
    }
    fout << num_layers_ << " " << learning_rate_ << "\n";  // сохраняем кол-во слоёв, скорость обучения
    for (size_t i = 0; i < num_layers_; ++i) {
        fout << num_neurons_[i] << " ";   // сохраняем количества нейронов
    }
    fout << "\n";
    for (int i = 0; i < num_layers_ - 1; ++i) {
        fout << layers_[i].GetWeights() << "\n";  // сохраняем матрицы весов
    }

    for (int i = 0; i < num_layers_ - 1; ++i) {
        fout << layers_[i].GetBias() << "\n";  // сохраняем вектора сдвигов
    }
    fout << func_name_ << "\n";  // сохраняем название функции активации (sigmoida, relu, th, ...)
    std::cout << "Weights saved \n";
    fout.close();
}

void Network::ReadData() {  // читаем значения нейросети из файла
    std::ifstream fin;
    fin.open("Data.txt");
    if (!fin.is_open()) {
        std::cout << "Error reading the file";
        system("pause");
    }
    fin >> num_layers_ >> learning_rate_;  // читаем кол-во слоёв, скорость обучения
    for (size_t i = 0; i < num_layers_; ++i) {
        fin >> num_neurons_[i];  // читаем количества нейронов
    }
    for (int i = 0; i < num_layers_ - 1; ++i) {
        fin >> layers_[i].ChangeWeights();  // читаем матрицы весов
    }
    for (int i = 0; i < num_layers_ - 1; ++i) {
        fin >> layers_[i].ChangeBias();  // читаем вектора сдвигов
    }
    fin >> func_name_;  // считываем название функции активации
    func_ = func_names_map.at(func_name_).first;
    der_ = func_names_map.at(func_name_).second;
    std::cout << "Weights readed \n";
    fin.close();
}

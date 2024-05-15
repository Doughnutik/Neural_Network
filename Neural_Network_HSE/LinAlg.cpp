#include "LinAlg.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <random>

std::normal_distribution<double> distribution(1, 0);  // можно менять генератор чисел
std::mt19937 gen(43);

Vector::Vector(size_t size) { Init(size); }

Vector::Vector(const std::vector<double> &vec) {
    Init(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        vec_[i] = vec[i];
    }
}

void Vector::Init(size_t size) {
    vec_.assign(size, 0);
    size_ = size;
}

void Vector::RandomFill() {
    for (size_t i = 0; i < size_; ++i) {
        vec_[i] = distribution(gen); // тут можно менять рандом
    }
}

size_t Vector::Size() const { return size_; }

double &Vector::operator[](size_t ind) { return vec_[ind]; }

double Vector::operator[](size_t ind) const { return vec_[ind]; }

void Vector::operator+=(const Vector &other) {
    assert(size_ == other.size_);
    for (size_t i = 0; i < size_; ++i) {
        vec_[i] += other[i];
    }
}

Vector Vector::operator+(const Vector &other) const {
    assert(size_ == other.size_);
    Vector new_vec = *this;
    new_vec += other;
    return new_vec;
}

void Vector::operator-=(const Vector &other) {
    assert(size_ == other.size_);
    for (size_t i = 0; i < size_; ++i) {
        vec_[i] -= other[i];
    }
}

Vector Vector::operator-(const Vector &other) const {
    assert(size_ == other.size_);
    Vector new_vec = *this;
    new_vec -= other;
    return new_vec;
}

void Vector::operator*=(double value) {
    for (size_t i = 0; i < size_; ++i) {
        vec_[i] *= value;
    }
}

Vector Vector::operator*(double value) const {
    Vector new_vec = *this;
    new_vec *= value;
    return new_vec;
}

double Vector::operator*(const Vector &other) const {
    assert(size_ == other.size_);
    double res = 0;
    for (size_t i = 0; i < size_; ++i) {
        res += vec_[i] * other[i];
    }
    return res;
}

std::pair<int, double> Vector::FindMax() const {
    int id = static_cast<int>(std::max_element(vec_.begin(), vec_.end()) -
                              vec_.begin());
    return {id, vec_[static_cast<size_t>(id)]};
}

Matrix::Matrix(size_t rows, size_t cols) { Init(rows, cols); }

Matrix::Matrix(const std::vector<std::vector<double>> &mat) {
    Init(mat.size(), mat[0].size());
    for (size_t i = 0; i < mat.size(); ++i) {
        matrix_[i] = Vector(mat[i]);
    }
}

void Matrix::Init(size_t rows, size_t cols) {
    rows_ = rows;
    cols_ = cols;
    matrix_.assign(rows, Vector(cols));
}

void Matrix::RandomFill() {
    for (size_t i = 0; i < rows_; ++i) {
        matrix_[i].RandomFill();
    }
}

size_t Matrix::Rows() const { return rows_; }

size_t Matrix::Cols() const { return cols_; }

void Matrix::operator+=(const Matrix &other) {
    assert(other.rows_ == rows_ && other.cols_ == cols_);
    for (size_t i = 0; i < rows_; ++i) {
        matrix_[i] += other.matrix_[i];
    }
}

Matrix Matrix::operator+(const Matrix &other) const {
    assert(other.rows_ == rows_ && other.cols_ == cols_);
    Matrix new_matrix = *this;
    new_matrix += other;
    return new_matrix;
}

void Matrix::operator-=(const Matrix &other) {
    assert(other.rows_ == rows_ && other.cols_ == cols_);
    for (size_t i = 0; i < rows_; ++i) {
        matrix_[i] -= other.matrix_[i];
    }
}

Matrix Matrix::operator-(const Matrix &other) const {
    assert(other.rows_ == rows_ && other.cols_ == cols_);
    Matrix new_matrix = *this;
    new_matrix -= other;
    return new_matrix;
}

Vector &Matrix::operator[](size_t ind) { return matrix_[ind]; }

const Vector &Matrix::operator[](size_t ind) const { return matrix_[ind]; }

void Matrix::operator*=(double value) {
    for (size_t i = 0; i < rows_; ++i) {
        matrix_[i] *= value;
    }
}

Matrix Matrix::operator*(double value) const {
    Matrix new_matrix = *this;
    new_matrix *= value;
    return new_matrix;
}

Vector Matrix::operator*(const Vector &other) const {
    assert(cols_ == other.Size());
    Vector new_vector(rows_);
    for (size_t i = 0; i < rows_; ++i) {
        new_vector[i] = matrix_[i] * other;
    }
    return new_vector;
}

Matrix Matrix::T() const {
    Matrix new_matrix(cols_, rows_);
    for (size_t i = 0; i < cols_; ++i) {
        for (size_t j = 0; j < rows_; ++j) {
            new_matrix[i][j] = matrix_[j][i];
        }
    }
    return new_matrix;
}

std::ostream &operator<<(std::ostream &os, const Vector &vec) {
    for (size_t i = 0; i < vec.size_; ++i)
        os << vec.vec_[i] << " ";
    return os;
}

std::istream &operator>>(std::istream &is, Vector &vec) {
    for (size_t i = 0; i < vec.size_; ++i)
        is >> vec.vec_[i];
    return is;
}

std::ostream &operator<<(std::ostream &os, const Matrix &mat) {
    for (size_t i = 0; i < mat.rows_; ++i) {
        for (size_t j = 0; j < mat.cols_; ++j) {
            os << mat[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}

std::istream &operator>>(std::istream &is, Matrix &mat) {
    for (size_t i = 0; i < mat.rows_; ++i) {
        for (size_t j = 0; j < mat.cols_; ++j) {
            is >> mat[i][j];
        }
    }
    return is;
}

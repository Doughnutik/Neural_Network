#include "LinAlg.h"
#include <assert.h>
#include <random>
#include <algorithm>

std::normal_distribution<double> distribution(1, 0); 
std::mt19937 gen(43);

Vector::Vector(size_t size) {
    Init(size);
}

Vector::Vector(const std::vector<double>& vec) {
    Init(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        vec_[i] = vec[i];
    }
}

void Vector::Init(size_t size) {
    vec_.assign(size, 0);
}

void Vector::RandomFill() {
    for (size_t i = 0 ; i < size_; ++i) {
        vec_[i] = distribution(gen);  // тут можно менять рандом
    }
}

size_t Vector::Size() const {
    return size_;   
}

double& Vector::operator[](size_t ind) {
    return vec_[ind];
}

double Vector::operator[](size_t ind) const {
    return vec_[ind];
}

void Vector::operator += (const Vector& other) {
    assert(size_ == other.size_);
    for (size_t i = 0; i < size_; ++i) {
        vec_[i] += other[i];
    }
}

Vector Vector::operator + (const Vector& other) const {
    assert(size_ == other.size_);
    Vector new_vec = *this;
    new_vec += other;
    return new_vec;
}

void Vector::operator -= (const Vector& other) {
    assert(size_ == other.size_);
    for (size_t i = 0; i < size_; ++i) {
        vec_[i] -= other[i];
    }
}

Vector Vector::operator - (const Vector& other) const {
    assert(size_ == other.size_);
    Vector new_vec = *this;
    new_vec -= other;
    return new_vec;
}

void Vector::operator *= (double value) {
    for (size_t i = 0; i < size_; ++i) {
        vec_[i] *= value;
    }
}

Vector Vector::operator * (double value) const {
    Vector new_vec = *this;
    new_vec *= value;
    return new_vec;
}

double Vector::operator * (const Vector& other) const {
    assert(size_ == other.size_);
    double res = 0;
    for (size_t i = 0 ; i < size_; ++i) {
        res += vec_[i] * other[i];
    }
    return res;
}

std::pair<int, double> Vector::FindMax() {
    size_t id = std::max_element(vec_.begin(), vec_.end()) - vec_.begin();
    return {id, vec_[id]};
}

Matrix::Matrix(size_t rows, size_t cols) {
    Init(rows, cols);
}

Matrix::Matrix(const std::vector<std::vector<double>>& mat) {
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
    for (size_t i = 0 ; i < rows_; ++i) {
        matrix_[i].RandomFill();
    }
}

size_t Matrix::GetRows() const {
    return rows_;
}

size_t Matrix::GetCols() const {
    return cols_;
}

void Matrix::operator+=(const Matrix& other) {
    assert(other.rows_ == rows_ && other.cols_ == cols_);
    for (size_t i = 0; i < rows_; ++i) {
        matrix_[i] += other.matrix_[i];
    }
}

Matrix Matrix::operator+(const Matrix& other) const{
    assert(other.rows_ == rows_ && other.cols_ == cols_);
    Matrix new_matrix = *this;
    new_matrix += other;
    return new_matrix;
}

void Matrix::operator-=(const Matrix& other) {
    assert(other.rows_ == rows_ && other.cols_ == cols_);
    for (size_t i = 0; i < rows_; ++i) {
        matrix_[i] -= other.matrix_[i];
    }
}

Matrix Matrix::operator-(const Matrix& other) const{
    assert(other.rows_ == rows_ && other.cols_ == cols_);
    Matrix new_matrix = *this;
    new_matrix -= other;
    return new_matrix;
}

Vector& Matrix::operator[](size_t ind) {
    return matrix_[ind];
}

const Vector& Matrix::operator[](size_t ind) const{
    return matrix_[ind];
}

void Matrix::operator *= (double value) {
    for (size_t i = 0; i < rows_; ++i) {
        matrix_[i] *= value;
    }
}

Matrix Matrix::operator * (double value) const {
    Matrix new_matrix = *this;
    new_matrix *= value;
    return new_matrix;
}

Vector Matrix::operator * (const Vector& other) const {
    assert(cols_ == other.Size());
    Vector new_vector(cols_);
    for (size_t i = 0; i < rows_; ++i) {
        new_vector[i] = matrix_[i] * other;
    }
    return new_vector;
}
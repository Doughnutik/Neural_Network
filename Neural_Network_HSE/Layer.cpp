#include "Layer.h"

void Layer::Init(size_t rows, size_t cols, Filling filling_type) {
    a_.Init(rows, cols);
    if (filling_type == Filling::Random) {
        a_.RandomFill();
    }
    weight_errors_.Init(rows, cols);
    b_.Init(rows);
    if (filling_type == Filling::Random) {
        b_.RandomFill();
    }
    bias_errors_.Init(rows);
    rows_ = rows;
    cols_ = cols;
}

std::pair<size_t, size_t> Layer::GetSize() const { return {rows_, cols_}; }

const Matrix &Layer::GetWeights() const { return a_; }

Matrix &Layer::ChangeWeights() { return a_; }

const Vector &Layer::GetBias() const { return b_; }
Vector &Layer::ChangeBias() { return b_; }

const Matrix &Layer::GetWeightErrors() const { return weight_errors_; }
Matrix &Layer::ChangeWeightErrors() { return weight_errors_; }

const Vector &Layer::GetBiasErrors() const { return bias_errors_; }
Vector &Layer::ChangeBiasErrors() { return bias_errors_; }

void Layer::Reset() {
    weight_errors_.Init(rows_, cols_);
    bias_errors_.Init(rows_);
}

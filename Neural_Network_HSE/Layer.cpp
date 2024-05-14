#include "Layer.h"

void Layer::Init(size_t rows, size_t cols, Filling filling_type) {
    a_.Init(rows, cols);
    if (filling_type == Filling::Random) {
        a_.RandomFill();
    }
    aT_ = a_.T();
    b_.Init(rows);
    if (filling_type == Filling::Random) {
        b_.RandomFill();
    }
    rows_ = rows;
    cols_ = cols;
}

std::pair<size_t, size_t> Layer::GetSize() const { return {rows_, cols_}; }

const Matrix &Layer::GetWeights() const { return a_; }

Matrix &Layer::ChangeWeights() { return a_; }

const Vector &Layer::GetBias() const { return b_; }
Vector &Layer::ChangeBias() { return b_; }

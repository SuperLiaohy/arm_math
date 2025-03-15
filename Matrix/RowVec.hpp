//
// Created by liaohy on 25-3-15.
//
#pragma once
#include "Matrix.hpp"
template<uint32_t COLS>
using RowVec = Matrix<1, COLS>;

//template<uint32_t COLS>
//class RowVec : public Matrix<1, COLS> {
//public:
//    RowVec(const float (&arr)[COLS]) : Matrix<1, COLS>() {
//        memcpy(this->data, arr, COLS * sizeof(float));
//    }
//
//    template<typename... Args>
//    RowVec(Args &&... args) : Matrix<1, COLS>(std::forward<Args>(args)...) {
//    }
//
//    float &operator[](uint32_t num) {
//        return this->data[0][num - 1];
//    }
//
//    float operator[](uint32_t num) const {
//        return this->data[0][num - 1];
//    }
//
//    friend RowVec<3> operator^(const RowVec<3> &self, const RowVec<3> &other);
//};
//
//
//inline RowVec<3> operator^(const RowVec<3> &self, const RowVec<3> &other) {
//    RowVec<3> result;
//    result[1] = self[2] * other[3] - self[3] * other[2];
//    result[2] = self[3] * other[1] - self[1] * other[3];
//    result[3] = self[1] * other[2] - self[2] * other[1];
//    return result;
//};
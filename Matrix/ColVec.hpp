//
// Created by liaohy on 25-3-15.
//
#pragma once
#include "Matrix.hpp"

 template<uint32_t ROWS>
 using ColVec = Matrix<ROWS, 1>;


//template<uint32_t ROWS>
//class ColVec : public Matrix<ROWS, 1> {
//public:
//    ColVec(const float (&arr)[ROWS]) : Matrix<ROWS, 1>() {
//        memcpy(this->data, arr, ROWS * sizeof(float));
//    }
//
//    template<typename... Args>
//    ColVec(Args &&... args) : Matrix<ROWS, 1>(std::forward<Args>(args)...) {
//    }
//
//    float &operator[](uint32_t num) {
//        return this->data[num - 1][0];
//    }
//
//    float operator[](uint32_t num) const {
//        return this->data[num - 1][0];
//    }
//
//    ColVec operator^(const ColVec &other) const;
//
//};
//
//template<>
//inline ColVec<3> ColVec<3>::operator^(const ColVec<3> &other) const {
//    ColVec<3> result;
//    result(0, 0) = (*this)[2] * other[3] - (*this)[3] * other[2];
//    result(0, 1) = (*this)[3] * other[1] - (*this)[1] * other[3];
//    result(0, 2) = (*this)[1] * other[2] - (*this)[2] * other[1];
//    return result;
//};



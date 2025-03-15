//
// Created by Administrator on 25-1-4.
//

/*
 * 经过测试直接调用arm_math库和数组，用时为A
 * 通过Matrix类封装arm_math库和数组，用时为B=1.18A左右
 * 通过Matrix类封装直接用数组进行矩阵运算，用时为C=1.2B~1.3B左右
 */
#pragma once


#include <concepts>

#ifdef __cplusplus
extern "C" {
#endif

#include "arm_math.h"

#ifdef __cplusplus
}
#endif

#include "cstring"
#include "iostream"


template<uint32_t ROWS, uint32_t COLS>
class Matrix {
public:
    static Matrix zeros() {
        Matrix result;
        memset(result.data, 0, ROWS * COLS * sizeof(float));
        return result;
    }

    static Matrix eyes() {
        Matrix result = zeros();
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (i == j) {
                    result.data[i][j] = 1;
                }
            }
        }
        return result;
    }

public:
    Matrix() {
        arm_mat_init_f32(&matrix, ROWS, COLS, reinterpret_cast<float32_t *>(data));
    }

    Matrix(const float (&arr)[ROWS][COLS])
            : Matrix() {
        memcpy(this->data, arr, ROWS * COLS * sizeof(float));
    }

    Matrix(const Matrix &other) {
        this->matrix.numRows = ROWS;
        this->matrix.numCols = COLS;
        this->matrix.pData = reinterpret_cast<float *>(data);
        memcpy(data, other.data, ROWS * COLS * sizeof(float));
    }

    Matrix &operator=(const float (&arr)[ROWS][COLS]) {
        arm_mat_init_f32(&matrix, ROWS, COLS, reinterpret_cast<float32_t *>(data));
        memcpy(data, arr, ROWS * COLS * sizeof(float));
        return *this;
    }

    Matrix &operator=(const Matrix &other) {
        this->matrix.numRows = ROWS;
        this->matrix.numCols = COLS;
        this->matrix.pData = reinterpret_cast<float *>(data);
        memcpy(data, other.data, ROWS * COLS * sizeof(float));
        return *this;
    }

    // 重载赋值运算符处理nullptr
    Matrix &operator=(std::nullptr_t) {
        matrix.pData = nullptr;
    }

    bool operator==(std::nullptr_t) {
        return matrix.pData == nullptr;
    }

    constexpr uint32_t get_row() { return ROWS; }

    constexpr uint32_t get_col() { return COLS; }

    float &operator()(uint32_t row, uint32_t col) {
        return data[row][col];
    }

    const float &operator()(uint32_t row, uint32_t col) const {
        return data[row][col];
    }

    Matrix operator+(const Matrix &other) {
        Matrix result;
        arm_mat_add_f32(&matrix, &other.matrix, &result.matrix);
        return result;
    }

    Matrix operator-(const Matrix &other) const {
        Matrix result;
        arm_mat_sub_f32(&matrix, &other.matrix, &result.matrix);
        return result;
    }

    template<uint32_t row, uint32_t col>
    Matrix<ROWS, col> operator*(const Matrix<row, col> &other) const requires(COLS == row) {
        Matrix<ROWS, col> result;
        arm_mat_mult_f32(&matrix, &other.matrix, &result.matrix);
        return result;
    }

    Matrix operator*(float scale) const {
        Matrix result;
        arm_mat_scale_f32(&matrix, scale, &result.matrix);
        return result;
    }

    friend Matrix<ROWS, COLS> operator*(float scale, const Matrix<ROWS, COLS> &other) {
        Matrix result;
        arm_mat_scale_f32(&other.matrix, scale, &result.matrix);
        return result;
    }

    Matrix operator/(float scale) const {
        Matrix result;
        arm_mat_scale_f32(&matrix, 1.0f / scale, &result.matrix);
        return result;
    }

    Matrix<COLS, ROWS> transpose() const {
        Matrix<COLS, ROWS> result;
        arm_mat_trans_f32(&matrix, &result.matrix);
        return result;
    }

    void transpose(Matrix &mat) const {
        arm_mat_trans_f32(&matrix, &mat.matrix);
    }

    Matrix<COLS, ROWS> operator~() {
        Matrix<COLS, ROWS> result;
        arm_mat_trans_f32(&matrix, &result.matrix);
        return result;
    }

    Matrix operator^(const Matrix &other) requires(ROWS == COLS) {
        Matrix result;
        arm_mat_inverse_f32(&matrix, &result.matrix);
        return result;
    }

    void operator+=(const Matrix &other) {
        arm_mat_add_f32(&matrix, &other.matrix, &matrix);
    }

    void operator-=(const Matrix &other) {
        arm_mat_sub_f32(&matrix, &other.matrix, &matrix);
    }

    void operator*=(const Matrix &other) requires(ROWS == COLS) {
        arm_mat_mult_f32(&matrix, &other.matrix, &matrix);
    }

    void operator*=(float scale) {
        arm_mat_scale_f32(&matrix, scale, &matrix);
    }

    void operator/=(float scale) {
        arm_mat_scale_f32(&matrix, 1.0f / scale, &matrix);
    }

    inline arm_status inv(Matrix &result) requires(ROWS == COLS);

    inline Matrix inv() requires(ROWS == COLS);

    template<uint32_t row, uint32_t clo>
    inline void
    assign_multiply(const Matrix<ROWS, clo> &first_matrix, const Matrix<row, COLS> &second_matrix) requires(row == clo);

    inline void assign_add(const Matrix &first_matrix, const Matrix &second_matrix);

    inline void assign_sub(const Matrix &first_matrix, const Matrix &second_matrix);

    inline void assign_scale(float scale);

    inline arm_status assign_inv(Matrix &scr_matrix) requires(ROWS == COLS);

    friend std::ostream &operator<<(std::ostream &os, const Matrix &mat) {
        os << "\n[";
        for (uint32_t i = 0; i < ROWS; ++i) {
            if (i > 0) os << "\n ";
            for (uint32_t j = 0; j < COLS; ++j) {
                os << " " << mat(i, j);
                if (j < COLS - 1) os << ",";
            }
            if (i < ROWS - 1) os << ",";
        }
        os << " ]";
        return os;
    }

private:
    arm_matrix_instance_f32 matrix{};
    float data[ROWS][COLS]{};
};

template<uint32_t ROWS, uint32_t COLS>
arm_status Matrix<ROWS, COLS>::assign_inv(Matrix &scr_matrix) requires(ROWS == COLS) {
    arm_status ret = arm_mat_inverse_f32(&scr_matrix.matrix, &matrix);
    return ret;
}

template<uint32_t ROWS, uint32_t COLS>
void Matrix<ROWS, COLS>::assign_scale(float scale) {
    arm_mat_scale_f32(&matrix, scale, &matrix);
}

template<uint32_t ROWS, uint32_t COLS>
void Matrix<ROWS, COLS>::assign_sub(const Matrix &first_matrix, const Matrix &second_matrix) {
    arm_mat_sub_f32(&first_matrix.matrix, &second_matrix.matrix, &matrix);
}

template<uint32_t ROWS, uint32_t COLS>
void Matrix<ROWS, COLS>::assign_add(const Matrix &first_matrix, const Matrix &second_matrix) {
    arm_mat_add_f32(&first_matrix.matrix, &second_matrix.matrix, &matrix);
}

template<uint32_t ROWS, uint32_t COLS>
template<uint32_t row, uint32_t clo>
void Matrix<ROWS, COLS>::assign_multiply(const Matrix<ROWS, clo> &first_matrix,
                                         const Matrix<row, COLS> &second_matrix) requires(row == clo) {
    arm_mat_mult_f32(&first_matrix.matrix, &second_matrix.matrix, &matrix);
}

template<uint32_t ROWS, uint32_t COLS>
inline arm_status Matrix<ROWS, COLS>::inv(Matrix &result) requires(ROWS == COLS) {
    arm_matrix_instance_f32 matrix_bak;
    matrix_bak.numRows = ROWS;
    matrix_bak.numCols = COLS;
    float data_bak[ROWS][COLS]{};
    memcpy(data_bak, data, ROWS * COLS * sizeof(float));
    matrix_bak.pData = reinterpret_cast<float *>(data_bak);
    arm_status ret = arm_mat_inverse_f32(&matrix_bak, &result.matrix);
    return ret;
}

template<uint32_t ROWS, uint32_t COLS>
inline Matrix<ROWS, COLS> Matrix<ROWS, COLS>::inv() requires(ROWS == COLS) {
    Matrix result;
    arm_matrix_instance_f32 matrix_bak;
    matrix_bak.numRows = ROWS;
    matrix_bak.numCols = COLS;
    float data_bak[ROWS][COLS]{};
    memcpy(data_bak, data, ROWS * COLS * sizeof(float));
    matrix_bak.pData = reinterpret_cast<float *>(data_bak);
    arm_status ret = arm_mat_inverse_f32(&matrix_bak, &result.matrix);
    return ret == ARM_MATH_SUCCESS ? result : zeros();
}






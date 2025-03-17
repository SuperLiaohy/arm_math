//
// Created by liaohy on 3/17/25.
//
#pragma once

#include "platform.h"
#include "arm_math.h"

class Windows {
public:
    using status = arm_status;
    using MatrixInstance = arm_matrix_instance_f32;

    [[gnu::always_inline]] inline static void
    matrix_init(MatrixInstance *self, uint16_t rows, uint16_t cols, float *data) {
        arm_mat_init_f32(self, rows, cols, data);
    };

    [[gnu::always_inline]] inline static void
    matrix_add(MatrixInstance *self, MatrixInstance *other, MatrixInstance *result) {
        arm_mat_add_f32(self, other, result);
    };

    [[gnu::always_inline]] inline static void
    matrix_sub(MatrixInstance *self, MatrixInstance *other, MatrixInstance *result) {
        arm_mat_sub_f32(self, other, result);
    };

    [[gnu::always_inline]] inline static void
    matrix_mul(MatrixInstance *self, MatrixInstance *other, MatrixInstance *result) {
        arm_mat_mult_f32(self, other, result);
    };

    [[gnu::always_inline]] inline static void
    matrix_scale(MatrixInstance *self, float scale, MatrixInstance *result) {
        arm_mat_scale_f32(self, scale, result);
    };

    [[gnu::always_inline]] inline static void
    matrix_trans(MatrixInstance *self, MatrixInstance *result) {
        arm_mat_trans_f32(self, result);
    };

    [[gnu::always_inline]] inline static void
    matrix_inverse(MatrixInstance *self,MatrixInstance *result) {
        arm_mat_inverse_f32(self, result);
    };
};

template<PlatFormConcept T>
class tmp : public T {

};

tmp<Windows> a;

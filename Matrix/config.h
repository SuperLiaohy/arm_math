//
// Created by liaohy on 3/17/25.
//
#pragma once

#include "arm_math.h"

class WINDOWS {
public:
    using status = arm_status;
    using MatrixInstance = arm_matrix_instance_f32;

    static void matrix_init(MatrixInstance *self,
                            uint16_t rows, uint16_t cols, float *
    );

    static void matrix_add(MatrixInstance *self,
                           std::declval<typename T::MatrixInstance *>(),
                           std::declval<typename T::MatrixInstance *>()

    )

    void matrix_sub(std::declval<typename T::MatrixInstance *>(),
                    std::declval<typename T::MatrixInstance *>(),
                    std::declval<typename T::MatrixInstance *>()

    )

    void matrix_mul(std::declval<typename T::MatrixInstance *>(),
                    std::declval<typename T::MatrixInstance *>(),
                    std::declval<typename T::MatrixInstance *>()

    )

    void matrix_scale(std::declval<typename T::MatrixInstance *>(),
                      std::declval<float>(),
                      std::declval<typename T::MatrixInstance *>()

    )

    void matrix_trans(std::declval<typename T::MatrixInstance *>(),
                      std::declval<typename T::MatrixInstance *>()

    )


    status matrix_inverse(std::declval<typename T::MatrixInstance *>(),
                          std::declval<typename T::MatrixInstance *>()
    )

};

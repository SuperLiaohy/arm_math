//
// Created by liaohy on 25-3-13.
//

#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "Matrix.hpp"
#include "RowVec.hpp"
#include "ColVec.hpp"
class Quaternion {
    template<uint32_t T>
    using Vec = RowVec<T>;
public:
    Quaternion(float w, float x, float y, float z) : w(w), u(Vec<3>({x, y, z})) {};

    Quaternion(float w, const Vec<3> &u) : w(w), u(u) {};

    Quaternion derivative(float wx, float wy, float wz) {
        return 0.5 * Quaternion(0, wx, wy, wz) * (*this);
    };

    Quaternion operator*(const Quaternion &q) {
        return Quaternion(q.w * w - (q.u * u)(1, 1), q.w * u + w * q.u + (u ^ q.u));
    };

    Quaternion operator*(float scale) {
        return Quaternion(scale * w, u * scale);
    };

    friend Quaternion operator*(float scale, const Quaternion &q) {
        return Quaternion(scale * q.w, q.u * scale);
    };

    friend std::ostream &operator<<(std::ostream &os, const Quaternion &mat) {
        os << "\n[";
        os << " " << mat.w << ",";
        os << " " << mat.u;
        os << " ]";
        return os;
    }


private:
    float w;
    Vec<3> u;
};


#endif //QUATERNION_HPP

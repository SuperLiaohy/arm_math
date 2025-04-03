//
// Created by liaohy on 25-3-13.
//

#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "Matrix.hpp"
#include "RowVec.hpp"
#include "ColVec.hpp"

class Quaternion {
public:
    template<uint32_t T>
    using Vec = RowVec<T>;

    static consteval Quaternion zero() { return Quaternion{0, 0, 0, 0};}
    static consteval Quaternion init() { return Quaternion{1, 0, 0, 0};}
public:
    constexpr Quaternion(float w, float x, float y, float z) : w(w), u(Vec<3>({x, y, z})) {};

    constexpr Quaternion(float w, const Vec<3> &u) : w(w), u(u) {};

    [[nodiscard]] constexpr Quaternion derivative(float wx, float wy, float wz) const {
        return Quaternion(0, wx * 0.5f, wy * 0.5f, wz * 0.5f) * (*this);
    };

    constexpr Quaternion operator*(const Quaternion &other) {
        return Quaternion{other.w * w - (other.u * u)(1, 1), other.w * u + w * other.u + (u ^ other.u)};
    };

    constexpr Quaternion operator*(float scale) {
        return Quaternion{scale * w, u * scale};
    };

    friend constexpr Quaternion operator*(float scale, const Quaternion &other) {
        return Quaternion{scale * other.w, other.u * scale};
    };

    constexpr Quaternion operator+(const Quaternion &other) {
        return Quaternion{w + other.w, u + other.u};
    }

    constexpr Quaternion operator-(const Quaternion &other) {
        return Quaternion{w - other.w, u - other.u};
    }

    constexpr Quaternion operator-() {
        return Quaternion{-w, -u(1), -u(2), -u(3)};
    }

    constexpr Quaternion conj() {
        return Quaternion{w, -u(1), -u(2), -u(3)};
    }

    constexpr Quaternion operator~() {
        return Quaternion{w, -u(1), -u(2), -u(3)};
    }

    consteval Quaternion inv() {
        auto size = w * w + (u * u)[0];
        return Quaternion{w / size, -u(1) / size, -u(2) / size, -u(3) / size};
    }

    template<typename OStream>
    friend OStream &operator<<(OStream &os, const Quaternion &mat) {
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

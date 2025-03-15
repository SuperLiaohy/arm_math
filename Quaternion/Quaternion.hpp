//
// Created by liaohy on 25-3-13.
//

#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "Matrix.hpp"

class Quaternion {
public:
    Quaternion(float w, float x, float y, float z) {
        this->w = w;
        this->u = RowVec<3>({x, y, z});
    };

    Quaternion(float w, const RowVec<3> &u) {
        this->w = w;
        this->u = u;
    };

//    Quaternion(const Quaternion &q);

    Quaternion operator*(const Quaternion &q) {
        return Quaternion(q.w * w - (q.u * u.transpose())(0, 0), q.w * u + w * q.u + (u ^ q.u));
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
    RowVec<3> u;
};


#endif //QUATERNION_HPP

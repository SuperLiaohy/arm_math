#include <iostream>
#include "Matrix.hpp"
#include "ColVec.hpp"
#include "Quaternion.hpp"
int main() {
    Matrix matrix({{2, 2}, {1,3}});
    ColVec<2> colVec(std::array<float, 2>{1, 3});
    RowVec<2> rowVec({1, 3});

    RowVec<1> point({2});

    std::cout << "RowVec" << rowVec << std::endl;
    std::cout << "ColVec:" << colVec << std::endl;
    std::cout << "row * col" << colVec * rowVec<< std::endl;
    std::cout << "origin:" << matrix << std::endl;
    std::cout << "tran:" << matrix.transpose() << std::endl;
    std::cout << "inverse:" << matrix.inv() << std::endl;
    std::cout << "origin * inverse:" << matrix * matrix.inv() << std::endl;
    std::cout << "origin * Col" << matrix * colVec << std::endl;
    std::cout << "row * origin" << rowVec * matrix << std::endl;
    std::cout << "point * row" << point * rowVec << std::endl;

    std::cout << "point * row" << point * point << std::endl;

    std::cout << "Hello, World!" << std::endl;

    auto q1 = (Quaternion(1, 2, 3, 4));
    auto q2 = (Quaternion(2, 4, 3, 4));
    auto q3 = q1 * q2;
    std::cout << "q1 * q2" << q3 << std::endl;

    return 0;
}
#include <iostream>
#include "matrix.hpp"


int main()
{
    Matrix<double> m1(9);
    Matrix<double> m2(m1);
    m1.fillMatrix();
    m1(2,1) = 5.5;
    m2(2,2) = 1;
    Matrix<double> m3 = m1;

    std::cout << "m1" << m1 << std::endl;
    std::cout << "m2" << m2 << std::endl;
    std::cout << "m3 (m3 = m1)" << m3 << std::endl;

    return 0;
}

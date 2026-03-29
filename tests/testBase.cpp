#include "../src/matrix.hpp"
#include <cassert>
#include <iostream>

int main () {
    // Constructor init
    matrix::Matrix<double> mD(7, 4);
    matrix::Matrix<int> mI(3);
    matrix::Matrix<long long> mL(6, 5);

    // Static init
    auto mI1 = matrix::Matrix<int>::identity(3);
    auto mR = matrix::Matrix<float>::random(7, 4, 0.0, 1.0);
    auto ones = matrix::Matrix<long>::ones(6);
    auto zeros = matrix::Matrix<long>::zeros(6);

    // ()
    mI(0,0) = 1;
    mI(1,1) = 1;
    mI(2,2) = 1;
    assert(mI == mI1);
    assert(ones != zeros);


    // fill
    mD.fillRandom();
    matrix::Matrix<double> mD1(mD);
    assert(mD.isApprox(mD1));

    mL.fill(2);

    // stampa
    std::cout << mD << std::endl;
    std::cout << mI << std::endl;
    std::cout << mL << std::endl;
    std::cout << mI1 << std::endl;
    std::cout << mR << std::endl;
    std::cout << ones << std::endl;
    std::cout << zeros << std::endl;

    // Operazioni
    auto mD2 = mD + mD1;
    auto mI2 = mI + mI1;
    auto ones1 = ones + zeros;
    try {
        auto mR1 = matrix::Matrix<float>::random(6, 4, 0.0, 1.0);
        mR1 + mR;
    } catch (...) {
        std::cout << "Correclty found error, "
                     "cannot sum matrix of different size" << std::endl;
    }

    mI2 -= mI;

    assert(mI2 == mI);

    // Moltiplicazione
    try {
        mD2 = mD * mD1;
    } catch (...) {
    std::cout << "Correclty found error, "
                 "cannot sum matrix of different size" << std::endl;
    }

    mD2 = mD * mD1.transpose(); // corrtect way
    mI2 = mI * mI1;

    assert(mI2 == mI);

    // Determinante

    return 0;
}
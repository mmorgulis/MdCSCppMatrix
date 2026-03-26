#include <iostream>
#include <chrono>
#include "matrix.hpp"


int main()
{
    matrix::Matrix<float> m1(5);
    matrix::Matrix<float> m2(5);
    m1.fillMatrix();
    m2.fillMatrix();

    auto inizio = std::chrono::high_resolution_clock::now();
    auto m3 = m1 + m2;
    auto transposed = m1.transpose();
    auto fine = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tempo = fine - inizio;
    std::cout << "Tempo impiegato: " << tempo.count() << " ms" << std::endl;
    std::cout << m1 << std::endl;
    std::cout << transposed << std::endl;

    return 0;
}

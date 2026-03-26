#include <iostream>
#include "matrix.hpp"
#include <chrono>


int main()
{
    auto m1 = matrix::Matrix<float>::random(5);
    auto m2 = matrix::Matrix<long>::identity(10);

    matrix::Matrix<double> m3(1000);
    matrix::Matrix<double> m4(1000);

    m3.fill(2.45);
    m4.fill(4.55);

    auto start = std::chrono::high_resolution_clock::now();
    auto m5 = m3 * m4;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tempo = end - start;
    std::cout << "Tempo impiegato: " << tempo.count() << " ms" << std::endl;


    return 0;
}

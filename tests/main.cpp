#include <iostream>
#include "../src/matrix.hpp"
#include <chrono>


int main()
{
    auto m1 = matrix::Matrix<float>::random(5);
    auto m2 = matrix::Matrix<long>::identity(10);
    auto row = m2.getRow(1);
    row[3] = 8888;
    std::cout << m2 << std::endl;

    auto m3 = m1.triu();
    auto m4 = m1.tril();
    std::cout << m1 << std::endl;
    std::cout << m3 << std::endl;
    std::cout << m4 << std::endl;

    // matrix::Matrix<double> m3(1000);
    // matrix::Matrix<double> m4(1000);

    // m3.fill(2.45);
    // m4.fill(4.55);

    // auto start = std::chrono::high_resolution_clock::now();
    // auto m5 = m3 * m4;
    // auto end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double, std::milli> tempo = end - start;
    // std::cout << "Tempo impiegato: " << tempo.count() << " ms" << std::endl;

    std::cout << std::numeric_limits<long double>::epsilon() << std::endl;
    std::cout << std::numeric_limits<int>::max() << std::endl;
    std::cout << sizeof(long double) << std::endl;
    double i = 0.3;
    double j = 0.2;
    j += 0.1;
    if (i == j ){
        std::cout << "if" << std::endl;
    } else if (i - j < std::numeric_limits<double>::epsilon()) {
        std::cout << "elseif: " << std::numeric_limits<double>::epsilon() << std::endl;
    } else {
        std::cout << "else" << std::endl;
    }


    return 0;
}

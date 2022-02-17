#include "Polynomial.h"
#include <iostream>

int main() {
    Polynomial p1{ DoubleArray{ 0, 7, -5, 10 } };
    for(int i = 0; i < std::size(p1); ++i){
        if (p1[i] == 0)
            i++;
        std::cout << p1[i] << "x" << i + 1;
        if ((i + 1) != std::size(p1))
            std::cout << " + ";
    }
    std::cout << std::endl;

    Polynomial p2{ { 1, 2, 3, 4, 0, 1} };
    for(int i = 0; i < std::size(p2); ++i){
        if (p2[i] == 0)
            i++;
        std::cout << p2[i] << "x" << i + 1;
        if ((i + 1) != std::size(p2))
            std::cout << " + ";
    }
    std::cout << std::endl;

    Polynomial p3 = p2 >> 2;
    for(int i = 0; i < std::size(p3); ++i){
        if (p3[i] == 0)
            i++;
        std::cout << p3[i] << "x" << i + 1;
        if ((i + 1) != std::size(p3))
            std::cout << " + ";
    }
    std::cout << std::endl;

    Polynomial p4 = p2 << 4;
    for(int i = 0; i < std::size(p4); ++i){
        if (p4[i] == 0)
            i++;
        std::cout << p4[i] << "x" << i + 1;
        if ((i + 1) != std::size(p4))
            std::cout << " + ";
    }
    std::cout << std::endl;

    Polynomial p5 = -p4;
    for(int i = 0; i < std::size(p5); ++i){
        if (p5[i] == 0)
            i++;
        std::cout << p5[i] << "x" << i + 1;
        if ((i + 1) != std::size(p5))
            std::cout << " + ";
    }
    std::cout << std::endl;

    Polynomial p6 = p2 + p4;
    for(int i = 0; i < std::size(p6); ++i){
        if (p6[i] == 0)
            i++;
        std::cout << p6[i] << "x" << i + 1;
        if ((i + 1) != std::size(p6))
            std::cout << " + ";
    }
    std::cout << std::endl;

    Polynomial p7 = p1 - p5;
    for(int i = 0; i < std::size(p7); ++i){
        if (p7[i] == 0)
            i++;
        std::cout << p7[i] << "x" << i + 1;
        if ((i + 1) != std::size(p7))
            std::cout << " + ";
    }
    std::cout << std::endl;

    Polynomial p8 = p6 * p3;
    for(int i = 0; i < std::size(p8); ++i){
        if (p8[i] == 0)
            i++;
        std::cout << p8[i] << "x" << i + 1;
        if ((i + 1) != std::size(p8))
            std::cout << " + ";
    }
    std::cout << std::endl;

    Polynomial p9 = p5 / 5;
    for(int i = 0; i < std::size(p9); ++i){
        if (p9[i] == 0)
            i++;
        std::cout << p9[i] << "x" << i + 1;
        if ((i + 1) != std::size(p9))
            std::cout << " + ";
    }
    std::cout << std::endl;

    Polynomial p10{ { 1, 2, 3, 4 } };
    Polynomial p11{ { 5, 6, 7, 8 } };

    std::cout << std::boolalpha << (p10 == p11) << std::endl;
    std::cout << std::boolalpha <<(p10 != p11) << std::endl;

    std::cout << std::boolalpha << (p2 == p10) << std::endl;
    std::cout << std::boolalpha << (p2 != p10) << std::endl;

    return 0;
}

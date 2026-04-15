#include <iostream>
#include "rational.hpp"

int main(void)
{
    int num;
    int den;

    std::cout << "Inserisci il denominatore: ";
    std::cin >> num;

    std::cout << "Inserisci il numeratore: ";
    std::cin >> num;

    rational<int> r(num, den);

    std::cout << r << "\n";

    return 0;
}
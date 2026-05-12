#include <iostream>
#include "rational.hpp"

int main()
{
    rational<int> a(1, 2);
    rational<int> b(1, 3);

    /* TEST OPERATORI */
    std::cout << a << " + " << b << " = " << a + b << "\n";
    std::cout << a << " - " << b << " = " << a - b << "\n";
    std::cout << a << " * " << b << " = " << a * b << "\n";
    std::cout << a << " / " << b << " = " << a / b << "\n\n";

    /* TEST CASI NaN, Inf, */
    rational<int> inf(1, 0);
    rational<int> nan(0, 0);
    rational<int> zero(0, 1);

    std::cout << "Inf + 1/2 = " << inf + a   << "\n";
    std::cout << "NaN + 1/2 = " << nan + a   << "\n";
    std::cout << "Inf * 0   = " << inf * zero << "\n";
    std::cout << "1/2 / 0   = " << a / zero  << "\n\n";

    /* TEST SEMPLIFICAZIONE */
    rational<int> r(3, 6);
    std::cout << r << "\n\n";

    /* TEST num() E den() */
    std::cout << "num(3/6) = " << r.num() << "\n";
    std::cout << "den(3/6) = " << r.den() << "\n\n";

    std::cout << "num(Inf) = " << inf.num() << "\n";
    std::cout << "den(Inf) = " << inf.den() << "\n\n";

    std::cout << "num(NaN) = " << nan.num() << "\n";
    std::cout << "den(NaN) = " << nan.den() << "\n\n";

    return 0;
}
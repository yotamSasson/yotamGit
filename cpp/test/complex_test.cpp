#include "complex.hpp" //complex class decleration
#include "utilities.hpp" 

using namespace dev;

int main ()
{
    HEADER(Default Ctor);
    Complex c;
    std::cout << c << std::endl;

    HEADER(Paramatized Ctor);
    Complex c1(3,4);
    std::cout << c1 << std::endl;

    HEADER(operator+=);
    Complex c2(5,3);
    c += c2;
    std::cout << "c: " << c << std::endl;

    HEADER(operator-=);
    c2 -= c;
    std::cout << "c2: " << c2 << std::endl;

    HEADER(operator+);
    Complex c3(5,3);
    c1 = c2 + c3;
    std::cout << "c1: " << c1 << std::endl;

    HEADER(operator-);
    c1 = c3 - c2;
    std::cout << "c1: " << c1 << std::endl;

    HEADER(operator==);
    Complex c4(c3);
    std::cout << std::boolalpha << "c4 == c3: " << (c4 == c3) << std::endl;

    HEADER(operator>>);
    std::cout << std::boolalpha << "c1 != c3: " << (c1 != c3) << std::endl;

    HEADER(operator*);
    std::cout << std::boolalpha << "c1 * 0= : " << (c1 * 0) << std::endl;

    HEADER(operator/);
    std::cout << std::boolalpha << "c1 / 1 = : " << (c1 / 1) << std::endl;

    HEADER(operator>>);
    std::cin >> c1;
    std::cout << "c1: " << c1 << std::endl;

    
    return 0;
}

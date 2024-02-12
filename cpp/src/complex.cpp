#include "complex.hpp" //complex class decleration

namespace dev
{
/************************ Non Member Function ************************/
bool operator==(const Complex& lhs, const Complex& rhs)
{
    return ((lhs.GetReal() == rhs.GetReal()) && (lhs.GetImaginary() == rhs.GetImaginary()));
}

bool operator!=(const Complex& lhs, const Complex& rhs)
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os_, const Complex& complex_)
{
    return os_ << complex_.GetReal() << " + " << complex_.GetImaginary() << "i";
}

std::istream& operator>>(std::istream& is, Complex& complex_)
{
    double real(0);
    double imaginary(0);

    is >> real;
    is >> imaginary;

    complex_.SetReal(real);
    complex_.SetImaginary(imaginary);

    return is;
}

}

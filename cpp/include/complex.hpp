#ifndef MY_PROJECT_COMPLEX_HPP
#define MY_PROJECT_COMPLEX_HPP

#include <iostream> // ostream

namespace dev
{

class Complex
{
public:
    inline Complex(const double real = 0, const double imaginary = 0); // Non explicit ctor on purpose
    // cctor, = opertor and dtor are auto-generated.

    inline void SetReal(double num);
    inline void SetImaginary(double num);
    inline double GetReal() const;
    inline double GetImaginary() const;

    inline Complex& operator+=(const Complex& other_);
    inline Complex& operator-=(const Complex& other_);
    inline Complex& operator*=(const Complex& other_);
    inline Complex& operator/=(const Complex& other_);

private:
    double m_real;
    double m_imaginary;
};

inline const Complex operator+(const Complex& lhs, const Complex& rhs);
inline const Complex operator-(const Complex& lhs, const Complex& rhs);
inline const Complex operator*(const Complex& lhs, const Complex& rhs);
inline const Complex operator/(const Complex& lhs, const Complex& rhs);
bool operator==(const Complex& lhs, const Complex& rhs);
bool operator!=(const Complex& lhs, const Complex& rhs);
std::ostream& operator<<(std::ostream& os_, const Complex& complex_);
std::istream& operator>>(std::istream& is, Complex& complex_);

/************************ Constructors ************************/
inline Complex::Complex(const double real , const double imaginary ): m_real(real), m_imaginary(imaginary){}

/************************ Set Methods ************************/
inline void Complex::SetReal(double num)
{
    m_real = num;
}

inline void Complex::SetImaginary(double num)
{
   m_imaginary = num;
}
/************************ Get Methods ************************/
inline double Complex::GetReal() const
{
    return m_real;
}

inline double Complex::GetImaginary() const
{
    return m_imaginary;
}
/************************ operator ************************/

inline Complex& Complex::operator+=(const Complex& other_)
{
   *this = (*this + other_);
    return *this; 
}

inline Complex& Complex::operator-=(const Complex& other_)
{
   *this = (*this - other_);
    return *this; 
}

inline Complex& Complex::operator*=(const Complex& other_)
{
   *this = (*this * other_);

    return *this;
}

inline Complex& Complex::operator/=(const Complex& other_)
{
    if ((0 != other_.GetReal() && 0 == other_.GetImaginary()))
    {
        throw std::invalid_argument("Division by zero");
    }

    *this = (*this / other_);
    return *this;
}
/************************ Non Member Function ************************/

inline const Complex operator+(const Complex& lhs, const Complex& rhs)
{
    Complex result(lhs.GetReal() + rhs.GetReal(),
    lhs.GetImaginary() + rhs.GetImaginary());
    
    return result;
}

inline const Complex operator-(const Complex& lhs, const Complex& rhs)
{
    Complex result(lhs.GetReal() - rhs.GetReal(),
    lhs.GetImaginary() - rhs.GetImaginary());
    
    return result;
}

inline const Complex operator*(const Complex& lhs, const Complex& rhs)
{
    double real = (lhs.GetReal() * rhs.GetReal()) - (lhs.GetImaginary() * rhs.GetImaginary());
    double imaginary = (lhs.GetReal() * rhs.GetImaginary()) + (lhs.GetImaginary() * rhs.GetReal());

    return Complex(real, imaginary);
}

inline const Complex operator/(const Complex& lhs, const Complex& rhs)
{
    if (0 == rhs.GetReal() && 0 == rhs.GetImaginary())
    {
        throw std::invalid_argument("Division by zero");
    }

    double denominator = (rhs.GetReal() * rhs.GetReal()) + (rhs.GetImaginary() * rhs.GetImaginary());
    double real = ((lhs.GetReal() * rhs.GetReal()) + (lhs.GetImaginary() * rhs.GetImaginary())) / denominator;
    double imaginary = ((lhs.GetImaginary() * rhs.GetReal()) - (lhs.GetReal() * rhs.GetImaginary())) / denominator;
    
    return Complex(real, imaginary);
}

}


#endif// MY_PROJECT_COMPLEX_HPP

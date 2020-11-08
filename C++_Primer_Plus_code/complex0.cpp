#include "complex0.h"

Complex::Complex()
{
    m_real = 0;
    m_imag = 0;
}
Complex::Complex(double n1, double n2)
{
    m_real = n1;
    m_imag = n2;
}
Complex::~Complex()
{

}
Complex operator + (const Complex &n1, const Complex &n2)
{
    return Complex (n1.m_real + n2.m_real, n1.m_imag + n2.m_imag);
}
Complex operator - (const Complex &n1, const Complex &n2)
{
    return Complex (n1.m_real - n2.m_real, n1.m_imag - n2.m_imag);
}
Complex operator * (const Complex &n1, const Complex &n2)
{
    return Complex ( (n1.m_real * n2.m_real) - (n1.m_imag * n2.m_imag),  (n1.m_real * n2.m_imag) + (n1.m_imag * n2.m_real));
}
Complex operator * (double num, const Complex &n)
{
    return Complex (n.m_real * num, n.m_imag * num);
}
Complex operator * (const Complex &n, double num)
{
    return Complex (n.m_real * num, n.m_imag * num);
}
Complex operator ~ (const Complex &c)
{
    return Complex (c.m_real, -c.m_imag);
}
std::istream &operator >> (std::istream &is, Complex &c)
{
    std::cout << "real: ";
    if (is >> c.m_real)
    {
        std::cout << "imaginary: ";
        is >> c.m_imag;
    }
    return is;
}
std::ostream &operator<<(std::ostream &os, const Complex &c)
{
    os << "(" << c.m_real << ", " << c.m_imag << "i)";
    return os;
}

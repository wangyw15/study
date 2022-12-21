#ifndef COMPLEX
#define COMPLEX

#include <ostream>
#include <iostream>

template <typename T>
class Complex
{
public:
    Complex()
    {
        r = i = 0;
    }
    Complex(T real, T imagine)
    {
        r = real;
        i = imagine;
    }
private:
    T r, i;
    template <typename U>
    friend std::ostream & operator<<(std::ostream & os, const Complex<U> & c)
    {
        std::cout << c.r << "+" << c.i << "i";
        return os;
    }
};

#endif
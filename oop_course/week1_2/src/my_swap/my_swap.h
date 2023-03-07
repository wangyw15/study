#ifndef MY_SWAP
#define MY_SWAP

#include <string.h>

template <typename T>
void my_swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template <std::size_t N>
void my_swap(char (&a)[N], char (&b)[N])
{
    char tmp[N];
    memcpy(tmp, a, N);
    memcpy(a, b, N);
    memcpy(b, tmp, N);
}

template < >
void my_swap<char *&>(char*& a, char*& b)
{
    char *tmp;
    tmp = a;
    a = b;
    b = a;
}

#endif

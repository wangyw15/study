#include "String.h"

#include <cstring>
#include <cstddef>
#include <iostream>

String::String(const String &source)
{
    delete [] str;
    str = new char[source.Length() + 1];
    strcpy(str, source.str);
}

String::String(const char *source)
{
    str = new char[strlen(source) + 1];
    strcpy(str, source);
}

String::String(const char *source, int len)
{
    if (len < 0)
    {
        len = 0;
    }
    str = new char[len + 1];
    for(int i = 0; i < len; i++)
    {
        str[i] = source[i];
    }
    str[len] = '\0';
}

String::String(const char *source, int start, int len)
{
    if (len < 0)
    {
        len = 0;
    }
    str = new char[len + 1];
    for(int i = start; i < len; i++)
    {
        str[i] = source[i];
    }
    str[len] = '\0';
}

String::~String()
{
    delete [] str;
}

String& String::operator=(const String &source)
{
    if (&source == this)
    {
        return *this;
    }
    str = new char[source.Length() + 1];
    strcpy(str, source.str);
    return *this;
}

void String::operator=(const char *source)
{
    str = new char[strlen(source) + 1];
    strcpy(str, source);
}

String& operator+(const String &a, const String &b)
{
    auto temp = new String;
    temp->str = new char[a.Length() + b.Length() + 1];
    strcpy(temp->str, a.str);
    strcat(temp->str, b.str);
    return *temp;
}

String& String::operator+=(const String &addition)
{
    String temp(*this);
    delete [] str;
    str = new char[temp.Length() + addition.Length() + 1];
    strcpy(str, temp.str);
    strcat(str, addition.str);
    return *this;
}

int String::Length() const
{
    return strlen(str);
}

bool String::IsEmpty() const
{
    return strlen(str) == 0;
}

std::ostream & operator<<(std::ostream &os, const String &source)
{
    os << source.str;
    return os;
}


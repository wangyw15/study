#ifndef MY_STRING
#define MY_STRING

#include <cstddef>
#include <ostream>
#include <istream>

class String
{
public:
    String(const char *source = "");
    String(const char *source, int len);
    String(const char *source, int start, int len);
    String(const String &source);
    ~String();

    int Length() const;
    bool IsEmpty() const;

    String& operator=(const String &source);
    void operator=(const char *source);
    friend String& operator+(const String &a, const String &b);
    String& operator+=(const String &source);
    friend std::ostream& operator<<(std::ostream &os, const String &source);
    // friend std::istream& operator>>(std::istream &is, const String &source);
private:
    char *str;
};

#endif
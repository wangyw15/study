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
    String(const char *source, int start, int end);
    String(const String &source);
    ~String();
    
  
    int Length() const;
    void MyInsert(int k, const char *t);
    void Copy_s(const char *source, int start, int end);
    void Erase(int index, int num);
    void Clear();
    void Replace(int start, int len, char *strr);
    bool Empty() const;
    void Swap(String &source);
    String Substr(int pos,int len,String &source);
    int Find(char *pat, int p);
    
    String& operator=(const String &source);
    void operator=(const char *source);
    friend String operator+(const String &a, const String &b);
    String& operator+(const String &st);
    String& operator+(const char* st);
    String& operator+=(const String &source);
    friend std::ostream& operator<<(std::ostream &os, const String &source);
    char& operator[](int index);
    char& operator[](int index) const;
    
private:
    char *str;
};

#endif
#include <bits/stdc++.h>
#include "String.h"

String::String(const String &source)//拷贝函数
{
    str = new char[source.Length() + 1];
    strcpy(str, source.str);
    std::cout << "Copy constructing an object of string: " << str << std::endl;
}

String::String(const char *source)//构造函数
{
    str = new char[strlen(source) + 1];
    strcpy(str, source);
    std::cout << "Constructing an object of string: " << str << std::endl;
}

String::String(const char *source, int len)//从source的起始位置取一段长度为len的字符构造对象
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
    std::cout << "Constructing an object of string: " << str << std::endl;
}

String::String(const char *source, int start, int end) //从souce中取小标为start-end的字符构造对象
{
    if (end < 0)
    {
        end = 0;
    }
    str = new char[end - start + 2];
    int i;
    for(i = 0; i < end - start + 1; i++)
    {
        str[i] = source[i + start];
    }
    str[end-start+1] = '\0';
    std::cout << "Constructing an object of string: " << str << std::endl;   
}

String String::Substr(int pos,int len,String &source) //从当前对象中pos下标的位置开始取一段长为len的字串
{
    if(pos<0)
    {
        pos = 0;
    }
    if(len<0)
    {
        len = source.Length();
    }
    String temp(*this);
    int i = 0;
    for(i = 0;i < len; i++)
    {
        temp.str[i]=source.str[i+pos];
        temp.str[len]='\0';
    };
    return temp;
}

void String::Copy_s(const char *source, int start, int end) //把source中start到end下标范围内的
{
    if (end < 0)
    {
        end = 0;
    }
    
    if (end > strlen(str)-1)
    {
        end = strlen(str) - 1;
    }
    for(int i = start; i <= end ; i++)
    {
        str[i] = source[i];
    }   
}


void String::MyInsert(int k, const char *t) //在当前字符串下标为k的字符后插入字符串t
{
    String temp(*this);
    int len = strlen(str);
    delete [] str;
    str = new char[len + strlen(t) + 1];
    String str1(temp.str,k);
    String str2(temp.str,k,len);
    strcpy(str,str1.str);
    strcat(str,t);
    strcat(str,str2.str);
 
}

void String::Erase(int index, int num) //去除当前字符串中index下标开始数量为num的字符
{
    String temp(*this);
    int len = strlen(str);
    delete [] str;
    str = new char[len + 1 - num];
    String str1(temp.str,index);
    String str2(temp.str,index + num, len-1);
    strcpy(str,str1.str);
    strcat(str,str2.str);
 
}

void String::Clear()//清除当前字符串的内容
{
	*str='\0';
}

void String::Replace(int start, int len, char *strr) //将当前字符串start下标开始长为len的内容替换为strr的内容
{
	String temp(*this);
    int len1 = strlen(strr);
    int len0 = strlen(str);
    delete [] str;
    str = new char[len0 - len + len1 + 1];
    String str1(temp.str, start);
    String str2(temp.str,start + len, len0 - 1);
    strcpy(str,str1.str);
    strcat(str,strr);
    strcat(str,str2.str);
}

int String::Length() const
{
    return strlen(str);
}

bool String::Empty() const
{
    if(strlen(str)==0)
        return true;
    else
        return false;
}

void String::Swap(String &source)
{
    char *temp = new char[source.Length()+1];
    temp = source.str;
    source.str = str;
    str = temp;
}

int String::Find(char *pat, int p) //字符串模式匹配函数（BF算法）
{
     int i = p, j = 0;
    while((i < strlen(str) && j < strlen(pat)) && ((strlen(pat) - j) <= (strlen(str) - i))) 
    {
        if (str[i] == pat[j])   //继续比较后续字符
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1;   //指针回退，重新开始新的匹配
            j = 0;
        }
    }
        if (j >= strlen(pat))  //匹配成功
            {return i - j;}
        else
            {return -1; }  //匹配失败
}



String::~String() //析构函数
{
    std:: cout << "destructing an object of String: " << str << std::endl;
    delete [] str;
   
}

String& String::operator=(const String &source) //深赋值运算函数
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

String operator+(const String &a, const String &b) //+运算符重载
{
    String temp;
    temp.str = new char[a.Length() + b.Length() + 1];
    strcpy(temp.str, a.str);
    strcat(temp.str, b.str);
    return temp;
}

String& String::operator+(const String &st)
{
    String temp(*this);
    delete [] str;
    str = new char[temp.Length() + st.Length() + 1];
    strcpy(str, temp.str);
    strcat(str, st.str);
    return *this;
}

String & String::operator+(const char* st)
{
    String temp(*this);
    delete [] str;
    str = new char[temp.Length() + strlen(st) + 1];
    strcpy(str, temp.str);
    strcat(str, st);
    return *this;
}


String& String::operator+=(const String &addition) //+=运算符重载
{
    String temp(*this);
    delete [] str;
    str = new char[temp.Length() + addition.Length() + 1];
    strcpy(str, temp.str);
    strcat(str, addition.str);
    return *this;
}

char& String::operator[](int index) //[]运算符重载
{
     return this -> str[index];
}

char& String::operator[](int index) const
{
     return this -> str[index];
}

std::ostream & operator<<(std::ostream &os, const String &source) //<<运算符重载
{
    os << source.str;
    return os;
}



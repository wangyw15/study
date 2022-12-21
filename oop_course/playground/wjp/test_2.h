#include <iostream>

using namespace std;

class Shape
{
public:
    Shape(char *color="no color"){}
    virtual double cal_c();
    virtual double cal_s();
    virtual void Show();

    virtual ~Shape(){}

protected:
    char *color[20];
};

class Circle : public Shape
{
public:
    Circle(const double r=0,char *color="no color")
    {}

    double cal_c()
    {
        double R=r,*c;
        *c=2*3.14*R;
        cout<<"C="<<*c<<endl;
        return *c;
    }

    double cal_s()
    {
        double R=r,*s;
        *s=3.14*R*R;
        cout<<"S="<<*s<<endl;
        return *s;
    }

    void Show()
    {
        cout<<"Name=Circle,r="<<r<<" ,s="<<cal_s()<<" ,c="<<cal_c()<<endl;
        cout<<"Color="<<*color<<endl;
    }

    ~Circle(){}

private:
    double r;
};

class Rectangle:public Shape
{
public:
    Rectangle (double height=0,double width=0,char *color="no color");

    double cal_c()
    {
        double *c;
        *c=2*((height)+(width));
        cout<<"C="<<*c<<endl;
        return *c;
    }

    double cal_s()
    {
        double *s;
        *s=(height)*(width);
        cout<<"S="<<*s<<endl;
        return *s;
    }

    void Show()
    {
        cout<<"Name=Rectangle,height="<<height<<" ,width="<<width<<" ,s="<<cal_s()<<" ,c="<<cal_c()<<endl;
        cout<<"Color="<<*color<<endl;
    }

    ~Rectangle(){}

private:
    double height, width;
};
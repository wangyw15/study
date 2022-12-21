#ifndef SHAPE
#define SHAPE

#include <ios>
#include <iostream>
#include <string>

class Shape {
protected:
  std::string _color;

public:
  Shape(std::string color = "black") : _color(color) {}

  std::string GetColor() const { return _color; }

  virtual double GetCircumference() const = 0;

  virtual double GetArea() const = 0;

  friend std::ostream &operator<<(std::ostream &out, const Shape &s) {
    out << "Shape with color: " << s._color;
    return out;
  }
};

class Rectangle : public Shape {
protected:
  double _width;
  double _height;

public:
  Rectangle(std::string color = "black", double w = 0, double h = 0)
      : Shape(color), _width(w), _height(h) {}

  double GetCircumference() const { return 2 * (_width + _height); }

  double GetArea() const { return _width * _height; }

  friend std::ostream &operator<<(std::ostream &out, const Rectangle &s) {
    out << "Rectangle with color: " << s._color << ", width: " << s._width
        << ", height: " << s._height;
    return out;
  }
};

class Circle : public Shape {
protected:
  double _radius;

public:
  Circle(std::string color = "black", double r = 0)
      : Shape(color), _radius(r) {}

  double GetRadius() const { return _radius; }

  double GetCircumference() const { return 2 * 3.14 * _radius; }

  double GetArea() const { return 3.14 * _radius * _radius; }

  friend std::ostream &operator<<(std::ostream &out, const Circle &s) {
    out << "Circle with color: " << s._color << ", radius: " << s._radius;
    return out;
  }
};

#endif
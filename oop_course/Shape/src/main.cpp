#include <iostream>
#include "Shape/shape.h"

int main()
{
	Shape* r = new Rectangle("red", 10, 5);
	std::cout << *r << std::endl;
	std::cout << r->GetCircumference() << std::endl;
	std::cout << r->GetArea() << std::endl;

	Circle* c = new Circle("red", 10);
	std::cout << *c << std::endl;
	std::cout << c->GetCircumference() << std::endl;
	std::cout << c->GetArea() << std::endl;
	return 0;
}
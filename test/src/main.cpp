#include <iostream>
#include <iomanip>

#include "Polynomial.h"

int main()
{
	Polynomial a{};
	Polynomial b{};

	std::cout << "Polynomials should observe the following format: ( a1x^b1 [+/-] a2x^b2 [+/-] ... [+/-] anx^bn )\n";
	std::cout << "Where for every i, ai is an integer or floating point and bi is a Natural number!\n";
	std::cout << "Negative exponents are not supported!\n";
	std::cout << "Spaces are optional and ignored\n";
	std::cout << "Example of a valid Polynomial: 0.5x^10 + x^2 - x - 9\n\n";
	
	std::cout << "Enter polynomial a: ";
	std::cin >> a;

	std::cout << "Enter polynomial b: ";
	std::cin >> b;

	std::cout << std::boolalpha;
	std::cout << "\n--------------------\n";
	
	std::cout << "Derivative of a: " << a.derivative() << '\n';
	std::cout << "Derivative of b: " << b.derivative() << '\n';
	std::cout << "a * b : " << a * b << '\n';
	std::cout << "a + b : " << a + b << '\n';
	std::cout << "a - b : " << a - b << '\n';
	std::cout << "a == b : " << (a == b) << '\n';

	std::cout << "a coefficients: ";
	for (size_t i{ 0 }; i <= a.getMaxDegree(); ++i)
		std::cout << a.getCoef(i) << ' ';
	std::cout << '\n';
	
	std::cout << "b coefficients: ";
	for (size_t i{ 0 }; i <= b.getMaxDegree(); ++i)
		std::cout << b.getCoef(i) << ' ';
	
	std::cout << "\n--------------------\n\n";

	double c{};
	std::cout << "Enter a Number to evaluate a and b: ";
	std::cin >> c;
	std::cout << "a(" << c << "): " << a.eval(c) << '\n';
	std::cout << "b(" << c << "): " << b.eval(c) << '\n';

	return 0;
}
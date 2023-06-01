#pragma once

#include <string>
#include <sstream>
#include <cmath>
#include <limits>

class Polynomial
{
private:
	double* m_coefs;
	size_t m_size;

public:
	// Constructors Start
	Polynomial();
	Polynomial(const double coefs[], size_t size);		// Gets Polynomial directly using coefficient C array and C array size
	Polynomial(const Polynomial& rhs);					// Deep Copy Constructor
	Polynomial(Polynomial&& rhs) noexcept;				// Move Constructor
	
	/*
	* string should observe the following format: "± a1x^b1 ± a2x^b2 ± ... ± anx^bn"
	* where for every i, ai is a double ( coefficient is equal to 1 then writing it can be avoided )
	* and for every i, bi is an integer ( if exponent is equal to 1 or 0 then writing '^1' or 'x^0' can be avoided )
	*/
	Polynomial(const std::string& polstr);		// Gets Polynomial From String

	// Functionalities Start
	void setCoef(size_t degree, double newcoef);
	double getCoef(size_t degree) const;
	std::string str() const;					// Used to string represent the Polynomial
	double eval(double x) const;				// Evaluates the result of function for x
	Polynomial derivative() const;				// Returns derivative of the function
	Polynomial& refresh();						// Used to collapse a Polynomial to smaller Polynomial if it has its biggest degrees with zero coef
	size_t getMaxDegree() const;				// Used to return m_size-1 !


	// Binary Operators
	friend std::ostream& operator<<(std::ostream& out, const Polynomial& rhs);
	friend std::istream& operator>>(std::istream& in, Polynomial& rhs);
	friend Polynomial operator*(const Polynomial& lhs, const Polynomial& rhs);
	friend Polynomial operator*(const Polynomial& lhs, const double rhs);
	friend Polynomial operator*(const double rhs, const Polynomial& lhs);
	friend Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
	friend Polynomial operator-(const Polynomial& lhs);
	friend Polynomial operator-(const Polynomial& lhs, const Polynomial& rhs);

	// Comparison Operator
	friend bool operator==(const Polynomial& lhs, const Polynomial rhs);

	// Assignments Operators
	Polynomial& operator*=(const Polynomial& rhs);
	Polynomial& operator=(const Polynomial& rhs);		// Deep Copy Assignment
	Polynomial& operator=(Polynomial&& rhs) noexcept;	// Move Assignment 

	// Destructor
	~Polynomial();
};
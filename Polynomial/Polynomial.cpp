#include "Polynomial.h"


Polynomial::Polynomial()
	: m_coefs{ new double[1] {} }, m_size{ 1 }
{
}


Polynomial::Polynomial(const double coefs[], size_t size)
{
	size_t newsize{ size };
	for (size_t i{ size }; i != 0; --i)
	{
		if (i - 1 == 0)
			break;
		if (coefs[i - 1] != 0)
			break;
		newsize--;
	}

	m_coefs = new double[newsize];
	m_size = newsize;
	for (size_t i{ 0 }; i != m_size; ++i)
		m_coefs[i] = coefs[i];
}


Polynomial::Polynomial(const std::string& polstr)
{
	// Space Free String
	std::string sfstr{ polstr };

	// Delete Spaces
	for (size_t i{ 0 }; i < sfstr.size(); ++i)
	{
		if (sfstr[i] == ' ')
			sfstr.erase(i, 1);

	}

	// Find max Degree
	size_t maxDegree{};
	for (size_t i{ 0 }; i < sfstr.size(); ++i)
	{
		if (sfstr[i] == '^')
		{
			int currentPower = std::stoi(sfstr.substr(i + 1));
			if (currentPower > maxDegree)
				maxDegree = currentPower;
		}
	}
	if (maxDegree == 0 && sfstr.find('x') != sfstr.npos)
		maxDegree = 1;

	m_size = maxDegree+1;
	m_coefs = new double[maxDegree+1] {};

	// Iterating over Tokens
	std::stringstream st{sfstr};
	std::string token{};
	while (std::getline(st, token, '+'))
	{
		std::stringstream st2(token);
		std::string subtoken{};
		int sign{ +1 };
		int c{};
		while (std::getline(st2, subtoken, '-'))
		{
			if (c == 1)
				sign = -1;
			// Tokens here
			size_t xpos{ subtoken.find('x') };
			if ( xpos != subtoken.npos)
			{
				if (xpos != subtoken.size() - 1)
				{
					if (subtoken[xpos + 1] == '^')
					{
						int exponent{ std::stoi(subtoken.substr(xpos + 2)) };
						double coef{ 1 };
						if (xpos != 0)
							coef = std::stod(subtoken);
						m_coefs[exponent] += sign * coef;
					}
				}
				else
				{
					if (xpos == 0)
						m_coefs[1] += sign;
					else
						m_coefs[1] += sign * std::stod(subtoken);
				}
			}
			else if(subtoken.size() != 0)
			{
				m_coefs[0] += sign * std::stod(subtoken);
			}
			c++;
		}
	}
}


Polynomial::Polynomial(const Polynomial& rhs)
{
	m_size = rhs.m_size;
	m_coefs = new double[m_size];
	for (size_t i{ 0 }; i < m_size; ++i)
		m_coefs[i] = rhs.m_coefs[i];
}


Polynomial::Polynomial(Polynomial&& rhs) noexcept
	: m_coefs{ rhs.m_coefs }, m_size{ rhs.m_size }
{
	rhs.m_coefs = nullptr;
}


std::string Polynomial::str() const
{
	// Print Zero if Polynomial is empty
	// This is an exception that is not handled by the loop
	if (m_size == 1 && m_coefs[0] == 0)
		return "0";

	std::stringstream result{};

	for (size_t i{ m_size }; i != 0; --i)
	{
		// Signing
		if (m_coefs[i - 1] > 0 && i != m_size)
			result << "+ ";
		else if (m_coefs[i - 1] < 0)
		{
			result << "-";
			if (i != m_size)
				result << ' ';
		}
	
		// Check if it has Coefficient
		if (m_coefs[i - 1] != 0)
		{
			// Printing Coefficient if it doesn't have |1| coefficient or it is coefficient of x^0
			if ((m_coefs[i - 1] != 1 && m_coefs[i-1] != -1) || i == 1)
				result << std::abs(m_coefs[i - 1]);

			//Printing variable and exponent if needed
			if (i == 2)
				result << "x ";
			else if (i > 2)
			{
				result << "x^" << std::to_string(i - 1) << ' ';
			}
		}

	}

	return result.str();
}


double Polynomial::eval(double x) const
{
	double result{};
	for (int i{ 0 }; i < m_size; ++i)
	{
		result += std::pow(x, i) * m_coefs[i];
	}
	return result;
}


void Polynomial::setCoef(size_t degree, double newcoef)
{
	if (degree < m_size)
	{
		m_coefs[degree] = newcoef;
		return;
	}

	double* coefs = new double[degree + 1] {};
	coefs[degree] = newcoef;
	for (size_t i{ 0 }; i < m_size; ++i)
		coefs[i] = m_coefs[i];

	delete[] m_coefs;
	m_coefs = coefs;
	m_size = degree + 1;
}


double Polynomial::getCoef(size_t degree) const
{
	if (degree < m_size)
		return m_coefs[degree];
	return 0;
}


Polynomial Polynomial::derivative() const
{	
	size_t size = m_size - 1;
	double* coefs = new double[m_size-1];

	for (int i{ 1 }; i < m_size; ++i)
	{
		coefs[i - 1] = m_coefs[i] * i;
	}

	Polynomial derivated{ coefs, size };
	delete[] coefs;
	return derivated;
}


Polynomial& Polynomial::refresh()
{
	*this = Polynomial{ m_coefs, m_size };
	return *this;
}


size_t Polynomial::getMaxDegree() const
{
	return m_size-1;
}


std::ostream& operator<<(std::ostream& out, const Polynomial& rhs)
{
	out << rhs.str();
	return out;
}


std::istream& operator>>(std::istream& in, Polynomial& rhs)
{
	std::string temp{};
	std::getline(in, temp);
	rhs = Polynomial{temp};
	
	return in;
}


Polynomial operator*(const Polynomial& lhs, const Polynomial& rhs)
{
	Polynomial result{};
	result.m_size = lhs.m_size + rhs.m_size - 1;
	result.m_coefs = new double[result.m_size] {};
	
	for (size_t i{ 0 }; i < lhs.m_size; ++i)
		for (size_t j{ 0 }; j < rhs.m_size; ++j)

#pragma warning(disable: 6385)
			result.m_coefs[i + j] += lhs.m_coefs[i] * rhs.m_coefs[j];
#pragma warning(default: 6385)

	
	return result.refresh();
}


Polynomial operator*(const Polynomial& lhs, const double rhs)
{
	Polynomial temp{lhs.m_coefs, lhs.m_size};
	for (size_t i{ 0 }; i < temp.m_size; ++i)
		temp.m_coefs[i] *= rhs;
	return temp.refresh();
}


Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs)
{
	size_t bsize;
	double* bcoefs;
	size_t ssize;
	double* scoefs;

	if (lhs.m_size >= rhs.m_size)
	{
		bsize = lhs.m_size;
		bcoefs = lhs.m_coefs;
		ssize = rhs.m_size;
		scoefs = rhs.m_coefs;
	}
	else
	{
		bsize = rhs.m_size;
		bcoefs = rhs.m_coefs;
		ssize = lhs.m_size;
		scoefs = lhs.m_coefs;
	}

	Polynomial temp{ bcoefs, bsize };
	for (size_t i{ 0 }; i < ssize; ++i)
		temp.m_coefs[i] += scoefs[i];

	return temp.refresh();
}


Polynomial operator*(const double rhs, const Polynomial& lhs)
{
	return operator*(lhs, rhs);
}


Polynomial operator-(const Polynomial& lhs)
{
	return lhs * -1;
}


Polynomial operator-(const Polynomial& lhs, const Polynomial& rhs)
{
	return lhs + (-1 * rhs);
}


bool operator==(const Polynomial& lhs, const Polynomial rhs)
{
	if (&lhs == &rhs)
		return true;

	if (lhs.m_size != rhs.m_size)
		return false;
	
	for (size_t i{ 0 }; i < lhs.m_size; ++i)
	{
		if (lhs.m_coefs[i] != rhs.m_coefs[i])
			return false;
	}

	return true;
}


Polynomial& Polynomial::operator*=(const Polynomial& rhs)
{
	*this = *this * rhs;
	return *this;
}


Polynomial& Polynomial::operator=(const Polynomial& rhs)
{
	if (&rhs == this)
		return *this;
	
	delete[] m_coefs;
	m_size = rhs.m_size;
	m_coefs = new double[m_size];
	for (size_t i{ 0 }; i < m_size; ++i)
		m_coefs[i] = rhs.m_coefs[i];
	return *this;
}


Polynomial& Polynomial::operator=(Polynomial&& rhs) noexcept
{
	if (&rhs == this )
		return *this;

	delete[] m_coefs;
	m_coefs = rhs.m_coefs;
	m_size = rhs.m_size;
	rhs.m_coefs = nullptr;
	
	return *this;
}


Polynomial::~Polynomial()
{
	delete[] m_coefs;
	m_size = 0;
}


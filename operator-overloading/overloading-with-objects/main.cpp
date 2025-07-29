#include <iostream>

class ComplexNumber
{
public:
	ComplexNumber(double, double);

	double getSize() const;

	double getRe() const;
	double getIm() const;

	// overloading the assignment operator is not necessary in this case cuz the default will do the same
	bool operator==(const ComplexNumber&) const;
	bool operator>(const ComplexNumber&) const;
	bool operator>(double) const;

	ComplexNumber operator+(const ComplexNumber&) const;

	void print() const;

private:
	double m_re{}, m_im{1.0};
};

ComplexNumber::ComplexNumber(double re, double im)
{
	m_re = re;
	m_im = im;
}

double ComplexNumber::getSize() const
{
	return (m_re * m_re + m_im * m_im);
}

double ComplexNumber::getRe() const
{
	return m_re;
}

double ComplexNumber::getIm() const
{
	return m_im;
}

bool ComplexNumber::operator==(const ComplexNumber& in_number) const
{
	return(m_re == in_number.getRe()) && (m_im == in_number.getIm());
}

bool ComplexNumber::operator>(const ComplexNumber& in_number) const
{
	return getSize() > in_number.getSize();
}

bool ComplexNumber::operator>(double in_number) const
{
	return getSize() > in_number;
}

ComplexNumber ComplexNumber::operator+(const ComplexNumber& in_number) const
{
	double res_re = m_re + in_number.getRe();
	double res_im = m_im + in_number.getIm();

	return ComplexNumber(res_re, res_im);
}

void ComplexNumber::print() const
{
	std::cout << m_re << " + " << m_im << "i" << std::endl;	
}

int main(int argc, char const *argv[])
{
	ComplexNumber comp1{1.1, 2.3};
	ComplexNumber comp2{2.5, 3.7};
	if(comp1 > comp2) std::cout << "comp1 is greater than comp2" << std::endl;
	else std::cout << "comp1 is NOT greater than comp2" << std::endl;

	(comp1 + comp2).print();

	return 0;
}
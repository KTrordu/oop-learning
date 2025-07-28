#include <iostream>

class ComplexNumber
{
public:
	ComplexNumber(double, double);

	double getSize() const;
	bool operator>(const ComplexNumber&) const;

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

bool ComplexNumber::operator>(const ComplexNumber& in_number) const
{
	return getSize() > in_number.getSize();
}

int main(int argc, char const *argv[])
{
	ComplexNumber comp1{1.1, 2.3};
	ComplexNumber comp2{2.5, 3.7};
	if(comp1 > comp2) std::cout << "comp1 is greater than comp2" << std::endl;
	else std::cout << "comp1 is NOT greater than comp2" << std::endl;

	return 0;
}
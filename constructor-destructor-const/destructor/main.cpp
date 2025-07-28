#include <iostream>
#include <cstring>

class String
{
public:
	String(const char *);
	// default copy constructor is created by compiler by default
	// String(const String&); copy constructor could be explicitly created like this
	// String(const String&) = delete; copy constructor can be avoided like this, or it can be made private
	void print() const;
	~String();

private:
	size_t m_size;
	char *m_contents;
};

String::String(const char *in_data)
{
	m_size = std::strlen(in_data);
	m_contents = new char[m_size + 1];
	if(m_contents)
	{
		for(unsigned index = 0; index < m_size + 1; index++)
		{
			m_contents[index] = in_data[index];
		}
	}
}

void String::print() const
{
	std::cout << m_contents << std::endl;
}

String::~String() // destructor works when an object is destroyed
{
	delete[] m_contents;
}

int main(int argc, char const *argv[])
{
	String *name = new String("akyuez");
	name->print();
	delete name;

	String surname {"akyuz"};
	surname.print();

	// this is a copy constructor
	String copySurname {surname};
	copySurname.print();

	return 0;
}
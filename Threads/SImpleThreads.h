#include <iostream>

class HelloWorld
{
public :
	void operator()() { Salute(); }

private :
	void Salute()
	{
		std::cout << "Hello world! \n";
	}
};

class HelloAgainWorld
{
public :
	void operator()() { Salute(); }

private :
	void Salute()
	{
		std::cout << "Hello again, world. \n";
	}
};
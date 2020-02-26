#include <iostream>

int main()
{
	int i = std::rand();

	std::string s = [=]() {
		switch(i%4)
		{
			case 0:
				return "long string is mod 0";
			case 1:
				return "long string is mod 1";
			case 2:
				return "long string is mod 2";
			case 3:
				return "long string is mod 3";
		}
	}();

	std::cout << i << std::endl;

	std::cout << s << std::endl;

	return i%4;

}

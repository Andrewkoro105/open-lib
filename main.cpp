#include <iostream>
#include "lib/openLib.hpp"

int main() {
	openLib::DL dL{"./liblib"};
	std::cout << dL.getSim<int(*)(int, int)>("foo")(3, 3) << '\n' << dL.getSim<int>("value") << std::endl;
	return 0;
}

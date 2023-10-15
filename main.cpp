#include <iostream>
#include <open-lib/DynamicLibrary.hpp>

int main() {
	open_lib::DL dL{"./liblib"   , {"foo", "value"}};
	std::cout << dL.get_sim<int(*)(int, int)>("foo")(3, 3) << '\n' << dL.get_sim<int>("value") << std::endl;
	return 0;
}

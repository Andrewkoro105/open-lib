#include <iostream>
#include <open-lib/DynamicLibrary.hpp>

int main() {
	open_lib::DL dL{"./liblib"   , {"foo", "value"}};
	std::cout << dL.get_sim<int(*)(int, int)>("foo")(3, 3) << std::endl << dL.get_sim<int>("value") << std::endl << open_lib::get_extension() << std::endl;
	return 0;
}

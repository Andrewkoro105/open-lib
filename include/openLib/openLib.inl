#include <utility>

namespace openLib {
	
	template<typename T>
	T DynamicLibrary::getSim(std::string simStr) {
		void* sim;
		if(sims[simStr]) {
			sim = sims[simStr];
		} else {
			sim = detail::loadSymbol(lib, std::move(simStr));
			detail::printLibError();
			sims[simStr] = sim;
		}
		if constexpr(std::is_pointer_v<T>) {
			return (T)(sim);
		} else {
			return *(T*)(sim);
		}
	}
	
	template<typename T>
	T DynamicLibrary::getSimFromDB(std::string simStr) {
		void* sim = sims[simStr];
		if constexpr(std::is_reference_v<T>) {
			return static_cast<T>(sim);
		} else {
			return *static_cast<T*>(sim);
		}
	}
	
	template<typename T>
	T DynamicLibrary::getSimFromLib(std::string simStr) {
		void* sim = detail::loadSymbol(lib, std::move(simStr));
		detail::printLibError();
		sims[simStr] = sim;
		if constexpr(std::is_pointer_v<T> || std::is_reference_v<T>) {
			return static_cast<T>(sim);
		} else {
			return *static_cast<T*>(sim);
		}
	}
}
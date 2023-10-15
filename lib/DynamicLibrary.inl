#include <utility>

namespace open_lib {
	
	template<typename T>
	T DynamicLibrary::get_sim(std::string sim_str) {
		void* sim;
		if(sims[sim_str]) {
			sim = sims[sim_str];
		} else {
			sim = detail::load_symbol(lib, std::move(sim_str));
			detail::print_lib_error();
			sims[sim_str] = sim;
		}
		if constexpr(std::is_pointer_v<T>) {
			return (T)(sim);
		} else {
			return *(T*)(sim);
		}
	}
	
	template<typename T>
	T DynamicLibrary::get_sim_from_d_b(std::string sim_str) {
		void* sim = sims[sim_str];
		if constexpr(std::is_reference_v<T>) {
			return static_cast<T>(sim);
		} else {
			return *static_cast<T*>(sim);
		}
	}
	
	template<typename T>
	T DynamicLibrary::get_sim_from_lib(std::string sim_str) {
		void* sim = detail::load_symbol(lib, std::move(sim_str));
		detail::print_lib_error();
		sims[sim_str] = sim;
		if constexpr(std::is_pointer_v<T> || std::is_reference_v<T>) {
			return static_cast<T>(sim);
		} else {
			return *static_cast<T*>(sim);
		}
	}
}
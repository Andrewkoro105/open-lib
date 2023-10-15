#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

namespace open_lib {
	namespace detail {
		void print_lib_error();
		
		void* open_lib(const std::string& lib_name);
		
		int close_lib(void* lib_handle);
		
		void* load_symbol(void* lib_handle, std::string sym);
	}
	class DynamicLibrary {
	protected:
		void* lib;
		std::unordered_map<std::string, void*> sims;
	
	public:
		DynamicLibrary(const std::filesystem::path& path, std::vector<std::string> sims = {});
		
		template<typename T = void*>
		T get_sim(std::string sim_str);
		
		template<typename T = void*>
		T get_sim_from_d_b(std::string sim_str);
		
		template<typename T = void*>
		T get_sim_from_lib(std::string sim_str);
		
		~DynamicLibrary();
	};
	
	using DL = DynamicLibrary;
}

#include "DynamicLibrary.inl"
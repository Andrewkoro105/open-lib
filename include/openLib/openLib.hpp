#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

namespace openLib {
	namespace detail {
		void printLibError();
		
		void* openLib(const std::string& libName);
		
		int closeLib(void* libHandle);
		
		void* loadSymbol(void* libHandle, std::string sym);
	}
	class DynamicLibrary {
	protected:
		void* lib;
		std::unordered_map<std::string, void*> sims;
		
	public:
		DynamicLibrary(const std::filesystem::path& path, std::vector<std::string> sims = {});
		
		template<typename T = void*>
		T getSim(std::string simStr);
		
		template<typename T = void*>
		T getSimFromDB(std::string simStr);
		
		template<typename T = void*>
		T getSimFromLib(std::string simStr);
		
		~DynamicLibrary();
	};
	
	using DL = DynamicLibrary;
}

#include "openLib.inl"
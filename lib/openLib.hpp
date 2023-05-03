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
	class DL {
	protected:
		void* lib;
		std::unordered_map<std::string, void*> sims;
		bool allLoad;
		
	public:
		DL(const std::filesystem::path& path, std::vector<std::string> sims = {}, bool allLoad = false);
		
		template<typename T = void*>
		T getSim(std::string simStr);
		
		template<typename T = void*>
		T getSimFromDB(std::string simStr);
		
		template<typename T = void*>
		T getSimFromLib(std::string simStr, bool allLoad = false);
		
		~DL();
	};
}

#include "openLib.inl"
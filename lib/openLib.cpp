#include "openLib.hpp"

#include <memory>
#include <iostream>

#if _WIN32
#include <windows.h>
#else

#include <dlfcn.h> //dlopen

#endif

namespace openLib {
	namespace detail {
		void printLibError() {
#if _WIN32
			auto err =  GetLastError();
			if(err)
				throw std::runtime_error(std::to_string(err));
#else
			auto err = dlerror();
			if(err)
				throw std::runtime_error(err);
#endif
		}
		
		void* openLib(const std::string& libName) {
#if _WIN32
			return LoadLibrary((libName + ".dll").c_str());
#else
			return dlopen((libName + ".so").c_str(), RTLD_LAZY);
#endif
		}
		
		int closeLib(void* libHandle) {
#if _WIN32
			return FreeLibrary((HMODULE)libHandle);
#else
			return dlclose(libHandle);
#endif
		}
		
		void* loadSymbol(void* libHandle, std::string sym) {
#if _WIN32
			return (void *)GetProcAddress((HMODULE)libHandle, sym.c_str());
#else
			return dlsym(libHandle, sym.c_str());
#endif
		}
	}
	
	
	DynamicLibrary::DynamicLibrary(const std::filesystem::path& path, std::vector<std::string> sims) {
		lib = detail::openLib(path.string());
		detail::printLibError();
		for(const auto& sim: sims) {
			this->sims[sim] = detail::loadSymbol(lib, sim);
		}
	}
	
	DynamicLibrary::~DynamicLibrary() {
		detail::closeLib(lib);
	}
}
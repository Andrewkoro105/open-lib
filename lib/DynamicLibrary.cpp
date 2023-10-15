#include "DynamicLibrary.hpp"

#include <memory>
#include <iostream>

#if _WIN32
#include <windows.h>
#else

#include <dlfcn.h> //dlopen

#endif

namespace open_lib {
	namespace detail {
		void print_lib_error() {
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
		
		void* open_lib(const std::string& lib_name) {
#if _WIN32
			return LoadLibrary((lib_name + ".dll").c_str());
#else
			return dlopen((lib_name + ".so").c_str(), RTLD_LAZY);
#endif
		}
		
		int close_lib(void* lib_handle) {
#if _WIN32
			return FreeLibrary((HMODULE)lib_handle);
#else
			return dlclose(lib_handle);
#endif
		}
		
		void* load_symbol(void* lib_handle, std::string sym) {
#if _WIN32
			return (void *)GetProcAddress((HMODULE)lib_handle, sym.c_str());
#else
			return dlsym(lib_handle, sym.c_str());
#endif
		}
	}
	
	
	DynamicLibrary::DynamicLibrary(const std::filesystem::path& path, std::vector<std::string> sims) {
		lib = detail::open_lib(path.string());
		detail::print_lib_error();
		for(const auto& sim: sims) {
			this->sims[sim] = detail::load_symbol(lib, sim);
		}
	}
	
	DynamicLibrary::~DynamicLibrary() {
		detail::close_lib(lib);
	}
}
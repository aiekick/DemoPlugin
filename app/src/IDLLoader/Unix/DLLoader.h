#pragma once

#ifdef UNIX
#include <iostream>
#include <dlfcn.h>
#include <IDLLoader/IDLLoader.h>

namespace dlloader
{
	template <class T>
	class DLLoader : public IDLLoader<T>
	{

	private:
		void			*_handle;
		std::string		_pathToLib;
		std::string		_allocClassSymbol;
		std::string		_deleteClassSymbol;

	public:
        DLLoader() = default;
		DLLoader(std::string const &pathToLib,
			std::string const &allocClassSymbol = "allocator",
			std::string const &deleteClassSymbol = "deleter") :
			_handle(nullptr), _pathToLib(pathToLib),
			_allocClassSymbol(allocClassSymbol), _deleteClassSymbol(deleteClassSymbol)
		{
		}

		~DLLoader() = default;

        bool IsValid() const
        {
            return _handle != nullptr;
        }

		void DLOpenLib() override
		{
			if (!(_handle = dlopen(_pathToLib.c_str(), RTLD_NOW | RTLD_LAZY))) {
                printf("Can't open and load %s : %s\n", _pathToLib.c_str(), dlerror());
			}
		}

		std::shared_ptr<T> DLGetInstance() override
		{
			using allocClass = T *(*)();
			using deleteClass = void (*)(T *);

			auto allocFunc = reinterpret_cast<allocClass>(
                dlsym(_handle, _allocClassSymbol.c_str()));
			auto deleteFunc = reinterpret_cast<deleteClass>(
                dlsym(_handle, _deleteClassSymbol.c_str()));

			if (!allocFunc || !deleteFunc) {
				DLCloseLib();
                printf("Can't find allocator or deleter symbol in %s : %s\n", _pathToLib.c_str(), dlerror());
            }

            return std::shared_ptr<T>(allocFunc(), [deleteFunc](T *p) { deleteFunc(p); });
        }

		void DLCloseLib() override
		{
			if (dlclose(_handle) != 0) {
                printf("Can't close %s : %s\n", _pathToLib.c_str(), dlerror());
			}
		}
	};
}

#endif
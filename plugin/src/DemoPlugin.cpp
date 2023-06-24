// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "DemoPlugin.h"
#include <Singleton.h>

std::string DemoPlugin::getName() {
    return "DemoPlugin";
}

std::string DemoPlugin::getVersion() {
    return "0.0.1";
}

std::string DemoPlugin::getDescription() {
    return "A Plugin demo";
}

extern "C"
{
#ifdef WIN32
#define PLUGIN_PREFIX __declspec (dllexport)
#else
#define PLUGIN_PREFIX
#endif

	PLUGIN_PREFIX DemoPlugin* allocator()
	{
		return new DemoPlugin();
	}

	PLUGIN_PREFIX void deleter(DemoPlugin* ptr)
	{
		delete ptr;
	}
}
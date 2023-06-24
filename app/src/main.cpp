#include <iostream>
#include <cstdlib>

#include <PluginManager.h>
#include <Singleton.h>

int main(int, char** argv)
{
    Singleton::Instance()->setName("App");

	PluginManager::Instance(argv[0])->LoadPlugins();

	return EXIT_SUCCESS;
}
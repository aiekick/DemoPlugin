#include <iostream>
#include <cstdlib>

#include <PluginManager.h>
#include <Singleton.h>

int main(int, char** argv)
{
    printf("=================\n");
    printf("From the App\n\t");
    Singleton::Instance()->setName("App");
    Singleton::Instance()->print();
	PluginManager::Instance(argv[0])->LoadPlugins();

	return EXIT_SUCCESS;
}
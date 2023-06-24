#include "APlugin.h"
#include <cassert>

#include <Singleton.h>

APlugin::~APlugin()
{
	Unit();
}

bool APlugin::Init(Singleton* vGuiHelperPtr)
{
    printf("=================\n");
    printf("From the plugin \"%s\"\n", getName().c_str());

    printf("The static instance of the singleton was reinit during the plugin loading\n\t");
	Singleton::Instance()->print();

	printf("So we transfer the singleton instance from the app to the plugin\n\t");
	Singleton::Instance(vGuiHelperPtr);
	Singleton::Instance()->print();

	return true;
}

void APlugin::Unit()
{
	
}
#include "APlugin.h"
#include <cassert>

#include <Singleton.h>

APlugin::~APlugin()
{
	Unit();
}

bool APlugin::Init(Singleton* vGuiHelperPtr)
{
	// the static instance of the singleton was reinit during the plugin loading
	Singleton::Instance()->print();

	// so we transfer the singleton instance from the app to the plugin
	Singleton::Instance(vGuiHelperPtr);
	Singleton::Instance()->print();

	return true;
}

void APlugin::Unit()
{
	
}
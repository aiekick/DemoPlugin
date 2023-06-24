#include "APlugin.h"
#include <cassert>

#include <Singleton.h>

APlugin::~APlugin()
{
	Unit();
}

bool APlugin::Init(Singleton* vGuiHelperPtr)
{
	Singleton::Instance()->print();

	Singleton::Instance(vGuiHelperPtr);
	Singleton::Instance()->print();

	return true;
}

void APlugin::Unit()
{
	
}
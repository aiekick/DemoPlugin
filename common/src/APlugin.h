#pragma once

#include <Export.h>

#include <memory> // weak_ptr, shared_ptr
#include <string>

class APlugin;
typedef std::weak_ptr<APlugin> APluginWeak;
typedef std::shared_ptr<APlugin> APluginPtr;

class Singleton;
class COMMON_API APlugin {
public:
	APlugin() = default;
	virtual ~APlugin();
	virtual bool Init(Singleton* vGuiHelperPtr);
	virtual void Unit();
    virtual std::string getName() = 0;
    virtual std::string getVersion() = 0;
    virtual std::string getDescription() = 0;
};
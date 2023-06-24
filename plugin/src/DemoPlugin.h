#pragma once

#include <APlugin.h>

class Singleton;
class DemoPlugin : public APlugin
{
public:
    DemoPlugin()          = default;
    virtual ~DemoPlugin() = default;

    std::string getName() override;
    std::string getVersion() override;
    std::string getDescription() override;
};
#pragma once

#include <map>
#include <string>
#include <memory>

#ifdef WIN32
#include <IDLLoader/Windows/DLLoader.h>
#else
#include <IDLLoader/Unix/DLLoader.h>
#endif

#include <APlugin.h>

class PluginInstance;
typedef std::weak_ptr<PluginInstance> PluginInstanceWeak;
typedef std::shared_ptr<PluginInstance> PluginInstancePtr;

class PluginInstance
{
private:
	dlloader::DLLoader<APlugin> m_Loader;
	APluginPtr m_PluginInstance = nullptr;
	std::string m_Name;

public:
	PluginInstance();
	~PluginInstance();

	bool Init(const std::string& vName, const std::string& vFilePathName);
	void Unit();

	APluginWeak Get();
};

class PluginManager
{
private:
	std::string m_AppPath;
	std::map<std::string, PluginInstancePtr> m_Plugins;

public:
	void LoadPlugins();
	void Clear();

private:
	PluginInstanceWeak Get(const std::string& vPluginName);

public:
	static PluginManager* Instance(const std::string& vAppPath = "")
	{
		static PluginManager _instance(vAppPath);
		return &_instance;
	}

protected:
	PluginManager(const std::string& vAppPath); // Prevent construction
	PluginManager(const PluginManager&) = delete; // Prevent construction by copying
	PluginManager& operator =(const PluginManager&) = delete; // Prevent assignment
	~PluginManager() = default; // Prevent unwanted destruction
};
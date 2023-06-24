#include "PluginManager.h"
#include <Singleton.h>
#include <filesystem>

namespace fs = std::filesystem;

#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32) || defined(__WIN64__) || defined(WIN64) || defined(_WIN64) || defined(_MSC_VER)
#define MODULE_EXTENTION "dll"
#elif defined(__linux__) || defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(__EMSCRIPTEN__)
#define MODULE_EXTENTION "so"
#elif defined(__APPLE__)
#define MODULE_EXTENTION "dylib"
#endif

//////////////////////////////////////////////////////////////////////////////
////// PluginInstance ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

PluginInstance::PluginInstance() {
}

PluginInstance::~PluginInstance() {
    Unit();
}

bool PluginInstance::Init(const std::string& vName, const std::string& vFilePathName) {
    m_Name   = vName;
    m_Loader = dlloader::DLLoader<APlugin>(vFilePathName);
    m_Loader.DLOpenLib();
    if (m_Loader.IsValid()) {
        m_PluginInstance = m_Loader.DLGetInstance();
        if (m_PluginInstance) {
            if (!m_PluginInstance->Init(Singleton::Instance())) {
                m_PluginInstance.reset();
            } else {
                return true;
            }
        }
    }
    return false;
}

void PluginInstance::Unit() {
    m_PluginInstance.reset();
    m_Loader.DLCloseLib();
}

APluginWeak PluginInstance::Get() {
    return m_PluginInstance;
}

//////////////////////////////////////////////////////////////////////////////
////// PluginLoader //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

PluginManager::PluginManager(const std::string& vAppPath) {
    m_AppPath = std::filesystem::path(vAppPath).parent_path().string();
}

void PluginManager::Clear() {
    m_Plugins.clear();
}

void PluginManager::LoadPlugins() {
    printf("-----------\n");
    printf("Availables Plugins :\n");
    if (std::filesystem::exists(m_AppPath)) {
        const auto dir_iter = std::filesystem::directory_iterator(m_AppPath);
        for (const auto& file : dir_iter) {
            if (file.is_regular_file()) {
                auto file_path_name = file.path().string();
                if (file_path_name.find(MODULE_EXTENTION) != std::string::npos) {
                    const auto& path = fs::path(file_path_name);
                    auto resPtr      = std::make_shared<PluginInstance>();
                    const auto& file_name = path.filename().string();
                    if (!resPtr->Init(file_name, file_path_name)) {
                        resPtr.reset();
                        printf("Plugin %s fail to load\n", file_name.c_str());
                    } else {
                        auto pluginInstancePtr = resPtr->Get().lock();
                        if (pluginInstancePtr) {
                            char spaceBuffer[40 + 1] = "";
                            spaceBuffer[0]           = '\0';

                            auto name = pluginInstancePtr->getName();
                            if (name.size() < 15U) {
                                size_t of = 15U - name.size();
                                memset(spaceBuffer, 32, of);  // 32 is ' ' in ASCII table
                                spaceBuffer[of] = '\0';
                                name += spaceBuffer;
                            } else {
                                name = name.substr(0, 15U);
                            }

                            auto version = pluginInstancePtr->getVersion();
                            if (version.size() < 10U) {
                                size_t of = 10U - version.size();
                                memset(spaceBuffer, 32, of);  // 32 is ' ' in ASCII table
                                spaceBuffer[of] = '\0';
                                version += spaceBuffer;
                            } else {
                                version = version.substr(0, 10U);
                            }

                            auto desc = pluginInstancePtr->getDescription();

                            printf("Plugin loaded : %s v%s (%s)\n", name.c_str(), version.c_str(), desc.c_str());
                        }

                        m_Plugins[file_name] = resPtr;
                    }
                }
            }
        }
    }
    printf("-----------\n");
}

//////////////////////////////////////////////////////////////
//// PRIVATE /////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

PluginInstanceWeak PluginManager::Get(const std::string& vPluginName) {
    if (!vPluginName.empty()) {
        if (m_Plugins.find(vPluginName) != m_Plugins.end()) {
            return m_Plugins.at(vPluginName);
        }
    }
    return {};
}

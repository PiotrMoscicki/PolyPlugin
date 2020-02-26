#include <filesystem>
#include <windows.h>

#include <pp/IntentRouter.hpp>

//------------------------------------------------------------------------------------------------------------------------------------------
class IPlugin
{
public:
    virtual ~IPlugin() = default;
    
    virtual void init(std::shared_ptr<IntentRouter> router) = 0;
    virtual void deinit(std::shared_ptr<IntentRouter> router) = 0;
    virtual const PluginInfo& getPluginInfo() const = 0;
};

using PluginCreatorType = std::unique_ptr<IPlugin>(__stdcall *)();

#define POLY_PLUGIN_ENTRY() \
	std::unique_ptr<IPlugin> __declspec(dllexport) __stdcall createPlugin()

//------------------------------------------------------------------------------------------------------------------------------------------
class PluginsContainer
{
public:
	PluginsContainer() : m_intentRouter(std::make_shared<IntentRouter>()) {}
	PluginsContainer(std::shared_ptr<IntentRouter> router) : m_intentRouter(std::move(router)) {}
    
    std::vector<std::weak_ptr<IPlugin>> load(std::filesystem::path path, bool reccursive)
    {
		HINSTANCE hGetProcIDDLL = LoadLibrary(LPCSTR(path.c_str()));
		if (!hGetProcIDDLL) 
			return {};

		PluginCreatorType creator = (PluginCreatorType)GetProcAddress(hGetProcIDDLL, "createPlugin");
		if (!creator)
			return {};

		std::shared_ptr<IPlugin> newPlugin = creator();
		m_plugins.push_back(newPlugin);

		return { std::move(newPlugin) };
    }
    
private:
	std::vector<std::shared_ptr<IPlugin>> m_plugins;
    std::shared_ptr<IntentRouter> m_intentRouter;
};
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
	std::unique_ptr<IPlugin> __declspec(dllexport) __stdcall createPolyPlugin()

//------------------------------------------------------------------------------------------------------------------------------------------
class PluginsContainer
{
public:
	PluginsContainer() : m_intentRouter(std::make_shared<IntentRouter>()) {}
	PluginsContainer(std::shared_ptr<IntentRouter> router) : m_intentRouter(std::move(router)) {}
    
    std::vector<std::weak_ptr<IPlugin>> load(std::filesystem::path root, bool reccursive)
    {
		std::vector<std::weak_ptr<IPlugin>> result;

		for (const std::filesystem::path& path : getAllSharedLibs(root, reccursive))
		{
			HINSTANCE hGetProcIDDLL = LoadLibrary(LPCSTR(path.c_str()));
			if (!hGetProcIDDLL)
				continue;

			PluginCreatorType creator = (PluginCreatorType)GetProcAddress(hGetProcIDDLL, "createPolyPlugin");
			if (!creator)
				continue;

			std::shared_ptr<IPlugin> newPlugin(creator().release());
			m_plugins.push_back(newPlugin);

			newPlugin->init(m_intentRouter);

			result.push_back(std::move(newPlugin));
		}

		return result;
    }
    
private:
	std::vector<std::filesystem::path> getAllSharedLibs(std::filesystem::path path, bool reccursive)
	{
		if (!std::filesystem::exists(path))
			return {};

		std::vector<std::filesystem::path> result;

		if (std::filesystem::is_directory(path))
		{
			if (reccursive)
			{
				std::filesystem::recursive_directory_iterator it(path);
				std::filesystem::recursive_directory_iterator endit;

				while (it != endit)
				{
					if (std::filesystem::is_regular_file(*it) && it->path().extension() == "dll")
						result.push_back(it->path());
				}
			}
			else
			{
				std::filesystem::directory_iterator it(path);
				std::filesystem::directory_iterator endit;

				while (it != endit)
				{
					if (std::filesystem::is_regular_file(*it) && it->path().extension() == "dll")
						result.push_back(it->path());
				}
			}
		}
		else
		{
			if (std::filesystem::is_regular_file(path) && path.extension() == "dll")
				result.push_back(path);
		}

		return result;
	}

	std::vector<std::shared_ptr<IPlugin>> m_plugins;
    std::shared_ptr<IntentRouter> m_intentRouter;
};
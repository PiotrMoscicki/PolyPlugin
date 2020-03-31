#include <iostream>

#include <pp/PolyPlugin.hpp>

#include <AddIntent.hpp>

//------------------------------------------------------------------------------------------------------------------------------------------
class Plugin : public pp::IPlugin
{
public:
	void init(std::shared_ptr<pp::IntentRouter> router) final
	{
		router->registerReceiver<AddIntent>(m_info, [this] (AddIntent intent) { return addIntentReceiver(std::move(intent)); });
	}

	void deinit(std::shared_ptr<pp::IntentRouter> router) final
	{

	}

	const pp::PluginInfo& getPluginInfo() const final
	{
		return m_info;
	}

private:
	AddIntent::Result addIntentReceiver(AddIntent intent)
	{
		return intent.a + intent.b;
	}

	pp::PluginInfo m_info = { "Calculator", { 1, 0, 0} };
};

//------------------------------------------------------------------------------------------------------------------------------------------
POLY_PLUGIN_ENTRY()
{
	return new Plugin();
}
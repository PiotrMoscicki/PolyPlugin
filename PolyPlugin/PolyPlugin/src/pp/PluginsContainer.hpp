#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <typeindex>
#include <memory>
#include <optional>
/*
//------------------------------------------------------------------------------------------------------------------------------------------
class IPlugin
{
public:
    virtual ~IPlugin() = default;
    
    virtual void init(shared_ptr<IntentRouter> router) = 0;
    virtual void deinit(shared_ptr<IntentRouter> router) = 0;
    virtual const PluginInfo& getPluginInfo() const = 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------
class PluginsContainer
{
public:
    IntentRouter() : m_intentRouter(std::make_shared<IntentRouter>()) {}
    IntentRouter(std::shared_ptr<IntentRouter> router) : m_intentRouter(std::move(router)) {}
    
    std::vector<std::weak_ptr<IPlugin>> load(std::filesystem::path path, bool reccursive)
    {
        
    }
    
    void unload(std::vector<std::weak_ptr<IPlugin>> plugins)
    {
        for ()
    }
    
private:
    std::shared_ptr<IntentRouter> m_intentRouter;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
class AddIntent
{
public:
    using Result = int;
    static inline IntentInfo Info = {};
    
    int a = 0;
    int b = 0;
};

//------------------------------------------------------------------------------------------------------------------------------------------
class TestReceiverSelector : public IReceiverSelector
{
public:
    int selectReceiver(IntentInfo intent, std::vector<PluginInfo> receivers) { return receivers.size() - 1; } 
};

//------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
    IntentRouter router(std::make_shared<TestReceiverSelector>());
    
    AddIntent addIntent = { 3, 4 };
    std::cout << router.processIntent(addIntent).has_value() << std::endl;
    
    router.registerReceiver(PluginInfo{"Test"}, std::function([](AddIntent i) { return i.a + i.b; }));
    std::cout << router.processIntent(addIntent).value() << std::endl;
    
    router.registerReceiver(PluginInfo{"Test"}, std::function([](AddIntent i) { return i.a - i.b; }));
    std::cout << router.processIntent(addIntent).value() << std::endl;
    
    printf("Hello World");
    return 0;
}*/
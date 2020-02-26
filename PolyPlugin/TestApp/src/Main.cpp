#include <iostream>

#include <pp/PolyPlugin.hpp>

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
    int selectReceiver(IntentInfo intent, std::vector<PluginInfo> receivers) { return static_cast<int>(receivers.size() - 1); } 
};

//------------------------------------------------------------------------------------------------------------------------------------------
int main()
{	
    IntentRouter router(std::make_shared<TestReceiverSelector>());
    
    AddIntent addIntent = { 3, 4 };
    std::cout << router.processIntent(addIntent).has_value() << std::endl;
    
    router.registerReceiver<AddIntent>(PluginInfo{"Test"}, std::function([](AddIntent i) { return i.a + i.b; }));
    std::cout << router.processIntent(addIntent).value() << std::endl;
    
    router.registerReceiver<AddIntent>(PluginInfo{"Test"}, std::function([](AddIntent i) { return i.a - i.b; }));
    std::cout << router.processIntent(addIntent).value() << std::endl;
    

    std::cout << std::endl << std::endl;

    return 0;
}
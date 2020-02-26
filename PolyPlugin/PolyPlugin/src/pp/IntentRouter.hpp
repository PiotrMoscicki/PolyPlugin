#pragma once
#include <typeindex>
#include <memory>
#include <optional>
#include <map>
#include <cassert>

#include <pp/ReceiversCollection.hpp>

//------------------------------------------------------------------------------------------------------------------------------------------
class IReceiverSelector
{
public:
    virtual ~IReceiverSelector() = default;
    
    virtual int selectReceiver(IntentInfo intent, std::vector<PluginInfo> receivers) = 0; 
};

//------------------------------------------------------------------------------------------------------------------------------------------
class DefaultReceiverSelector : public IReceiverSelector
{
public:
    int selectReceiver(IntentInfo intent, std::vector<PluginInfo> receivers) { return 0; } 
};

//------------------------------------------------------------------------------------------------------------------------------------------
class IntentRouter 
{
public:
    IntentRouter() : m_selector(std::make_shared<DefaultReceiverSelector>()) {}
    IntentRouter(std::shared_ptr<IReceiverSelector> selector) : m_selector(std::move(selector)) {}

    template <typename T>
    void registerReceiver(PluginInfo info, std::function<typename T::Result(T)> receiver)
    {
        const auto it = m_receivers.find(T::Info);
        if (it != m_receivers.end())
            static_cast<ReceiversCollection<T>*>(it->second.get())->push_back({ std::move(info), std::move(receiver) });
        else
        {
            auto newCollection = std::make_unique<ReceiversCollection<T>>();
            newCollection->push_back({ std::move(info), std::move(receiver) });
            m_receivers.insert({ T::Info, std::move(newCollection) });
        }
    }
    
    void unregisterReceivers(PluginInfo info)
    {
        assert(false); // implement this
    }
    
    template <typename T>
    std::optional<typename T::Result> processIntent(T intent)
    {
        const auto it = m_receivers.find(T::Info);
        if (it != m_receivers.end())
        {
            const auto receiversCollection = static_cast<ReceiversCollection<T>*>(it->second.get());
            const int chosenReceiver = m_selector->selectReceiver(T::Info, receiversCollection->getPluginsInfo());
            return receiversCollection->at(chosenReceiver).second(std::move(intent));
        }
        else
            return {};
    }

private:
    std::shared_ptr<IReceiverSelector> m_selector;
    std::map<IntentInfo, std::unique_ptr<ReceiversCollectionBase>> m_receivers;
};
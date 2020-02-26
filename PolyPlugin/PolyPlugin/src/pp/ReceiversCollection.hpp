#include <vector>
#include <functional>
#include <utility>

#include <pp/IntentInfo.hpp>
#include <pp/PluginInfo.hpp>

//------------------------------------------------------------------------------------------------------------------------------------------
class ReceiversCollectionBase 
{
public:
    virtual ~ReceiversCollectionBase() = default;

    virtual const IntentInfo& getIntentInfo() const = 0;
    virtual std::vector<PluginInfo> getPluginsInfo() const = 0;
};

//------------------------------------------------------------------------------------------------------------------------------------------
template <typename T>
class ReceiversCollection : 
    public ReceiversCollectionBase,
    public std::vector<std::pair<PluginInfo, std::function<typename T::Result(T)>>>
{
public:
    static inline IntentInfo handledIntentInfo = T::Info;

    const IntentInfo& getIntentInfo() const final { return handledIntentInfo; }
    std::vector<PluginInfo> getPluginsInfo() const final 
    {
        std::vector<PluginInfo> result;
        for (auto[key, value] : *this) 
            result.push_back(key);
        return result;
    }
};
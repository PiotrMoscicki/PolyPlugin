#include <iostream>

#include <pp/PolyPlugin.hpp>
#include <AddIntent.hpp>

//------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
	PluginsContainer container;
	char ownPth[MAX_PATH];

	HMODULE hModule = GetModuleHandle(NULL);
	if (hModule != NULL)
	{
		GetModuleFileName(hModule, ownPth, (sizeof(ownPth)));
		container.load(std::filesystem::path(ownPth).parent_path(), false);
	}
    
	AddIntent intent{ 2, 3 };
	std::cout << container.getIntentRouter()->processIntent(std::move(intent)).value();

    std::cout << std::endl << std::endl;

    return 0;
}
#include <iostream>

#include <pp/PolyPlugin.hpp>
#include <AddIntent.hpp>

//------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
	PluginsContainer container;
	char ownPth[MAX_PATH];

	// When NULL is passed to GetModuleHandle, the handle of the exe itself is returned
	HMODULE hModule = GetModuleHandle(NULL);
	if (hModule != NULL)
	{
		// Use GetModuleFileName() with module handle to get the path
		GetModuleFileName(hModule, ownPth, (sizeof(ownPth)));
		std::cout << std::filesystem::path(ownPth).parent_path() << std::endl;

		container.load(std::filesystem::path(ownPth).parent_path(), false);
	}
    

    std::cout << std::endl << std::endl;

    return 0;
}
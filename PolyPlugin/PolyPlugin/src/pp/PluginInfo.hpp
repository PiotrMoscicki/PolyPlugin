#pragma once

#include <string>

namespace pp
{
	//------------------------------------------------------------------------------------------------------------------------------------------
	class Version
	{						// https://semver.org/
	public:
		int major = 0;      // incompatible API changes
		int minor = 0;      // functionality added in a backwards compatible manner
		int patch = 0;      // backwards compatible bug fixes
	};

	//------------------------------------------------------------------------------------------------------------------------------------------
	class PluginInfo
	{
	public:
		const std::string name;

		const Version version;
	};
}
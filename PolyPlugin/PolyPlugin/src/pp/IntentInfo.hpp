#include <string>

//------------------------------------------------------------------------------------------------------------------------------------------
class IntentInfo
{
public:
	std::string name;

	class Version
	{         // https://semver.org/
		int major = 0;      // incompatible API changes
		int minor = 0;      // functionality added in a backwards compatible manner
		int patch = 0;      // backwards compatible bug fixes
	} version;
};
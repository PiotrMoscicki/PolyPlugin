#pragma once
#include <string>

//------------------------------------------------------------------------------------------------------------------------------------------
class IntentInfo
{
public:
	std::string name;

	class Version			// https://semver.org/
	{         
	public:
		int major = 0;      // incompatible API changes
		int minor = 0;      // functionality added in a backwards compatible manner
		int patch = 0;      // backwards compatible bug fixes
	} version;
};

bool operator== (const IntentInfo& left, const IntentInfo& right)
{
	return left.name == right.name && left.version.major == right.version.major;
}
bool operator!= (const IntentInfo& left, const IntentInfo& right)
{
	return !(left == right);
}
bool operator< (const IntentInfo& left, const IntentInfo& right)
{
	return left.version.major < right.version.major;
}
bool operator> (const IntentInfo& left, const IntentInfo& right)
{
	return left.version.major > right.version.major;
}
bool operator<= (const IntentInfo& left, const IntentInfo& right)
{
	return left.version.major <= right.version.major;
}
bool operator>= (const IntentInfo& left, const IntentInfo& right)
{
	return left.version.major >= right.version.major;
}
#pragma once

#include <string>

namespace pp
{
	//------------------------------------------------------------------------------------------------------------------------------------------
	class IntentInfo
	{
	public:
		std::string name;
		int version = 0; // there are no backwards compatible fixes in intents API
	};

	bool operator== (const IntentInfo& left, const IntentInfo& right)
	{
		return left.name == right.name && left.version == right.version;
	}
	bool operator!= (const IntentInfo& left, const IntentInfo& right)
	{
		return !(left == right);
	}
	bool operator< (const IntentInfo& left, const IntentInfo& right)
	{
		return left.version < right.version || left.name < right.name;
	}
	bool operator> (const IntentInfo& left, const IntentInfo& right)
	{
		return left.version > right.version || left.name > right.name;
	}
	bool operator<= (const IntentInfo& left, const IntentInfo& right)
	{
		return left.version <= right.version || left.name <= right.name;
	}
	bool operator>= (const IntentInfo& left, const IntentInfo& right)
	{
		return left.version >= right.version || left.name >= right.name;
	}
} // namespace pp
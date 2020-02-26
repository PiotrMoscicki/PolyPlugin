#pragma once

#include <pp/IntentInfo.hpp>

//------------------------------------------------------------------------------------------------------------------------------------------
class AddIntent
{
public:
	using Result = int;
	static inline IntentInfo Info = { "AddIntent", { 2, 1, 1 } };

	int a = 0;
	int b = 0;
};
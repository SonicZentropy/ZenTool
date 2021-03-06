/* ==============================================================================
//  ZenDebug.h
//  Part of the Zentropia JUCE Collection
//  Zentropia is hosted on Github at [https://github.com/SonicZentropy]
//  @author Casey Bailey (<a href="SonicZentropy@gmail.com">email</a>)
//  @version 0.1
//  @date 2015/08/30
//  Copyright (C) 2015 by Casey Bailey
//  Provided under the GNU license
//
//  Details: Static Utility Class for Debug-related code
================================================================================*/

#ifndef ZEN_UTILS_DEBUG_H_INCLUDED
#define ZEN_UTILS_DEBUG_H_INCLUDED
#include <ctime>

class ZenDebug
{
public:

	/// <summary>Sets desired time threshold between debug prints.</summary>
	/// <param name="inSeconds">The desired number of seconds between prints.</param>
	static void setSecondsBetweenDebugPrints(const int& inSeconds);
	static int getSecondsBetweenDebugPrints();

	static bool isPrintTimerThresholdReached();
private:
	static clock_t inTime;
	static int numSecondsBetweenDebugPrints;
	
};

#endif  // ZEN_UTILS_DEBUG_H_INCLUDED
/* ==============================================================================
//  AssociatedButton.cpp
//  Part of the Zentropia JUCE Collection
//  Zentropia is hosted on Github at [https://github.com/SonicZentropy]
//  @author Casey Bailey (<a href="SonicZentropy@gmail.com">email</a>)
//  @version 0.1
//  @date 8/21/2015
//  Copyright (C) 2015 by Casey Bailey
//  Provided under the GNU license
//
//  Details: Contains a Button component and its associated Parameter
===============================================================================*/


#include "AssociatedButton.h"

// No reason to ever use this constructor, technically
AssociatedButton::AssociatedButton() : Button("GLITCHASSOCIATEDBUTTONCONSTRUCTOR")
{
	DBG("Should never call this constructor at all (AssociatedButton)");
}

// No reason to ever use this constructor, technically
AssociatedButton::AssociatedButton(const String& componentName) : Button(componentName)
{
	DBG("Should never call this constructor at all (AssociatedButton)");
}

AssociatedButton::AssociatedButton(const String& componentName, AudioProcessorParameter* associatedParam)
: Button(componentName), AssociatedParameter(associatedParam)
{
	
}

AssociatedButton::AssociatedButton(const String& componentName, AudioProcessorParameter* associatedParam, const String& desiredUnitLabel) 
: Button(componentName), AssociatedParameter(associatedParam), unitLabel(desiredUnitLabel)
{
}

/*
  ==============================================================================

    StereoWidthCtrlSlider.cpp
    Created: 12 Aug 2015 1:38:56am
    Author:  Zentropy

  ==============================================================================
*/

#include "StereoWidthCtrlSlider.h"
#ifndef noexcept
#define noexcept throw()
#endif


StereoWidthCtrlSlider::StereoWidthCtrlSlider()
{
	DBG("SHOULD NEVER CALL THIS StereoWidthCtrlSlider.cpp CONSTRUCTOR");
}


StereoWidthCtrlSlider::StereoWidthCtrlSlider(const String& componentName) 
	: AssociatedSlider(componentName)
{
	DBG("SHOULD NEVER CALL THIS StereoWidthCtrlSlider.cpp CONSTRUCTOR");
}

StereoWidthCtrlSlider::StereoWidthCtrlSlider(const String& componentName, AudioProcessorParameter* associatedParam)
	: AssociatedSlider(componentName, associatedParam)
{
	setValue(associatedParam->getValue());
}

StereoWidthCtrlSlider::StereoWidthCtrlSlider(const String& componentName, AudioProcessorParameter* associatedParam, const String& desiredUnitLabel)
	: AssociatedSlider(componentName, associatedParam, desiredUnitLabel)
{
	this->setTextValueSuffix(desiredUnitLabel);
}



StereoWidthCtrlSlider::~StereoWidthCtrlSlider()
{
	
}

String StereoWidthCtrlSlider::getTextFromValue(double value)
{
	
	return String( String(value * 200.0f) + this->getTextValueSuffix());
}

double StereoWidthCtrlSlider::getValueFromText(const String& text)
{
	double parsedValue = text.getDoubleValue();
	parsedValue /= 200.0f;
	return parsedValue;
}

// void StereoWidthCtrlSlider::setWidth(const float& width)
// {
// 	stereoWidthValue = width;
// 	float widthDenormalized = stereoWidthValue * 2.0f;
// 	float temp;
// 	if (1.0f + width > 2.0f)
// 	{
// 		temp = 1.0f / (1.0f + widthDenormalized);
// 	}
// 	else temp = 1.0f / 2.0f;
// 	diffGain = widthDenormalized * temp;  ///diffGain is gain coefficient for Side 
// 	sumGain = temp;  ///sumGain is gain coefficient for Mid
// }





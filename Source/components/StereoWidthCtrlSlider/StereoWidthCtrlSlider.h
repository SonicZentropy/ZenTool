/*
  ==============================================================================

    StereoWidthCtrl.h
    Created: 12 Aug 2015 1:39:08am
    Author:  Zentropy
	Volume-Normalized Stereo Width Control - DSP from Michael Gruhn
	'width' is stretch factor of stereo field:
	width < 1: decrease stereo width
	width = 1: no change
	width > 1: increase width
	width = 0: MONO conversion

  ==============================================================================
*/

#ifndef STEREOWIDTHCTRL_H_INCLUDED
#define STEREOWIDTHCTRL_H_INCLUDED

#include "../../zen_utils/components/AssociatedSlider.h"



class StereoWidthCtrlSlider : public AssociatedSlider
{
public:

	StereoWidthCtrlSlider(const String& componentName, AudioProcessorParameter* associatedParam);
	StereoWidthCtrlSlider(const String& componentName, AudioProcessorParameter* associatedParam, const String& desiredUnitLabel);
	~StereoWidthCtrlSlider();

	/// <summary>Returns GUI Text from Value, appending unit.</summary>
	/// <param name="value">Value to be converted to GUI Text</param>
	/// <returns>The text string representing the GUI</returns>
	String getTextFromValue(double value) override;

	/// <summary>Return normalized 0-1.0 value from GUI text</summary>
	/// <param name="text">The text from GUI.</param>
	/// <returns>Normalized value representing GUI text.</returns>
	double getValueFromText(const String& text) override;
	
private:

};

#endif  // STEREOWIDTHCTRL_H_INCLUDED

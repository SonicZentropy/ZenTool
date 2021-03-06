/* ==============================================================================
//  PluginEditor.h
//  Part of the Zentropia JUCE Collection
//  @author Casey Bailey (<a href="SonicZentropy@gmail.com">email</a>)
//  @version 0.1
//  @date 2015/08/20
//  Copyright (C) 2015 by Casey Bailey
//  Provided under the [GNU license]
//
//  Details: GUI Editor Header
//
//  Zentropia is hosted on Github at [https://github.com/SonicZentropy]
===============================================================================*/

#ifndef JUCE_STEREO_WIDTH_PLUGIN_EDITOR
#define JUCE_STEREO_WIDTH_PLUGIN_EDITOR

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "components/StereoWidthCtrlSlider/StereoWidthCtrlSlider.h"
#include "components/GainCtrlSlider/GainCtrlSlider.h"
#include "components/PanSlider/PanSlider.h"

//==============================================================================

/// <summary> GUI Editor Handler </summary>
/// <seealso cref="T:AudioProcessorEditor"/>
/// <seealso cref="T:Timer"/>
/// <seealso cref="T:SliderListener"/>
/// <seealso cref="T:ButtonListener"/>
class ZenToolGUIEditor : public AudioProcessorEditor,
											public Timer,
											public SliderListener,
											public ButtonListener
{
public:
	//==============================================================================
	explicit ZenToolGUIEditor(ZenToolAudioProcessor& ownerFilter);
	~ZenToolGUIEditor();

	//==============================================================================

	void timerCallback() override;

	ZenToolAudioProcessor* getProcessor() const
	{
		return static_cast<ZenToolAudioProcessor*>(getAudioProcessor());
	}

	void paint(Graphics& g) override;
	void resized() override;

	void sliderValueChanged(Slider* sliderThatWasMoved) override;

	void buttonClicked(Button* buttonThatWasClicked) override;

private:

	AudioProcessor* processor;

	//ScopedPointer<TabbedComponent> tabbedComponent;
 	ScopedPointer<StereoWidthCtrlSlider> stereoWidthSldCtrl;
 	ScopedPointer<TextButton> bypassBtnCtrl;
 	ScopedPointer<Label> widthLabel;
 	ScopedPointer<TextButton> muteBtnCtrl;
 	ScopedPointer<GainCtrlSlider> gainSldCtrl;
 	ScopedPointer<TextButton> lockGainBtnCtrl;
 	ScopedPointer<ToggleButton> invertLeftBtnCtrl;
 	ScopedPointer<ToggleButton> invertRightBtnCtrl;
 	ScopedPointer<Label> invertLabel;
	ScopedPointer<Label> gainLabel;
	ScopedPointer<PanSlider> stereoPanSldCtrl;
	ScopedPointer<Label> panLabel;


	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZenToolGUIEditor)
};

#endif //JUCE_STEREO_WIDTH_PLUGIN_EDITOR


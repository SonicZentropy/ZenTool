/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.2.0 

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/
#include "PluginEditor.h"
#include <exception>



using namespace juce;

//==============================================================================
StereoWidthCtrlAudioProcessorEditor::StereoWidthCtrlAudioProcessorEditor(StereoWidthCtrlAudioProcessor& ownerFilter)
	: AudioProcessorEditor(ownerFilter), processor(&ownerFilter)
{
	//Audio Processor reference
	StereoWidthCtrlAudioProcessor* audioProc = getProcessor();
		
	addAndMakeVisible(stereoWidthSldCtrl = new StereoWidthCtrlSlider("Width Factor Slider", audioProc->stereoWidthParam, "%"));
	stereoWidthSldCtrl->setTooltip(TRANS("Stereo Width"));
	stereoWidthSldCtrl->setRange(0, 1, 0.005);
	stereoWidthSldCtrl->setSliderStyle(Slider::LinearHorizontal);
	stereoWidthSldCtrl->setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
	stereoWidthSldCtrl->addListener(this);
	
	addAndMakeVisible(gainSldCtrl = new GainCtrlSlider("Gain Knob", audioProc->audioGainParam, "dB", 12.0));
	gainSldCtrl->setRange(0.0, 1.0, 0.0);
	gainSldCtrl->setSkewFactor(0.5);
	gainSldCtrl->setSliderStyle(Slider::LinearVertical);
	gainSldCtrl->setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
	gainSldCtrl->setColour(Slider::backgroundColourId, Colour(0x00868181));
	gainSldCtrl->setColour(Slider::trackColourId, Colour(0x7fffffff));
	gainSldCtrl->setColour(Slider::rotarySliderFillColourId, Colour(0x7fbcbcff));
	gainSldCtrl->setColour(Slider::rotarySliderOutlineColourId, Colour(0x66ffffff));
	gainSldCtrl->addListener(this);
	

	addAndMakeVisible(bypassBtnCtrl = new TextButton("Bypass Button"));
	bypassBtnCtrl->setButtonText(TRANS("Bypass"));
	bypassBtnCtrl->addListener(this);
	bypassBtnCtrl->setColour(TextButton::buttonColourId, Colour(0xffe2e2e2));

	addAndMakeVisible(widthLabel = new Label("Width Label", TRANS("Stereo Width Factor:")));
	widthLabel->setFont(Font(15.00f, Font::plain));
	widthLabel->setJustificationType(Justification::centredLeft);
	widthLabel->setEditable(false, false, false);
	widthLabel->setColour(Label::textColourId, Colours::grey);
	widthLabel->setColour(TextEditor::textColourId, Colours::black);
	widthLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(muteBtnCtrl = new TextButton("Mute Button"));
	muteBtnCtrl->setButtonText(TRANS("Mute"));
	muteBtnCtrl->addListener(this);
	muteBtnCtrl->setColour(TextButton::buttonColourId, Colour(0xffe2e2e2));

	addAndMakeVisible(lockGainBtnCtrl = new TextButton("Lock Gain"));
	lockGainBtnCtrl->setButtonText(TRANS("Lock Gain to 0db"));
	lockGainBtnCtrl->addListener(this);
	lockGainBtnCtrl->setColour(TextButton::buttonColourId, Colour(0xffe2e2e2));

	addAndMakeVisible(invertLeftBtnCtrl = new ToggleButton("Invert Left"));
	invertLeftBtnCtrl->setTooltip(TRANS("Phase invert Left Channel"));
	invertLeftBtnCtrl->setButtonText(String::empty);
	invertLeftBtnCtrl->addListener(this);

	addAndMakeVisible(invertRightBtnCtrl = new ToggleButton("Invert Right"));
	invertRightBtnCtrl->setTooltip(TRANS("Phase invert Right Channel"));
	invertRightBtnCtrl->setButtonText(String::empty);
	invertRightBtnCtrl->addListener(this);
	invertRightBtnCtrl->setColour(ToggleButton::textColourId, Colours::black);

	addAndMakeVisible(invertLabel = new Label("Invert Label",
											TRANS("Invert Phase\n"
												"L       R")));
	invertLabel->setFont(Font(15.00f, Font::plain));
	invertLabel->setJustificationType(Justification::centredBottom);
	invertLabel->setEditable(false, false, false);
	invertLabel->setColour(Label::textColourId, Colours::grey);
	invertLabel->setColour(TextEditor::textColourId, Colours::black);
	invertLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	// #TODO: Change these to use getDefaultValue from param
	gainSldCtrl->setDoubleClickReturnValue(true, 0.5f);
	stereoWidthSldCtrl->setDoubleClickReturnValue(true, 0.5f);

	// GUI Size 
	setSize(375, 500);

	getProcessor()->RequestUIUpdate(); //UI Update must be performed every time a new editor is constructed
	startTimer(200); // Start timer poll with 200ms rate
	bypassBtnCtrl->setClickingTogglesState(true);
	muteBtnCtrl->setClickingTogglesState(true);
	lockGainBtnCtrl->setClickingTogglesState(true);
	invertLeftBtnCtrl->setClickingTogglesState(true);
	invertRightBtnCtrl->setClickingTogglesState(true);
	gainSldCtrl->setAssociatedParameter(getProcessor()->audioGainParam);
	DBG("Just set associated Parameter: " + String(getProcessor()->audioGainParam->getName(20)));
}

///
StereoWidthCtrlAudioProcessorEditor::~StereoWidthCtrlAudioProcessorEditor()
{
	stereoWidthSldCtrl = nullptr;
	bypassBtnCtrl = nullptr;
	widthLabel = nullptr;
	muteBtnCtrl = nullptr;
	gainSldCtrl = nullptr;
	lockGainBtnCtrl = nullptr;
	invertLeftBtnCtrl = nullptr;
	invertRightBtnCtrl = nullptr;
	invertLabel = nullptr;
}

//==============================================================================
void StereoWidthCtrlAudioProcessorEditor::paint(Graphics& g)
{
	g.fillAll(Colours::black);
}

void StereoWidthCtrlAudioProcessorEditor::resized()
{
	stereoWidthSldCtrl->setBounds(16, 40, 352, 24);
	bypassBtnCtrl->setBounds(8, 234, 360, 24);
	widthLabel->setBounds(8, 8, 150, 24);
	muteBtnCtrl->setBounds(16, 194, 150, 24);
	gainSldCtrl->setBounds(200, 72, 150, 104);
	lockGainBtnCtrl->setBounds(208, 184, 150, 24);
	invertLeftBtnCtrl->setBounds(33, 118, 25, 20);
	invertRightBtnCtrl->setBounds(71, 118, 25, 20);
	invertLabel->setBounds(12, 80, 100, 32);
}

/// <summary> Called by JUCE when slider is moved.  Casts slider as Associated and passes to associatedSliderValueChanged</summary>
/// <param name="sliderThatWasMoved"> The slider that was moved.</param>
void StereoWidthCtrlAudioProcessorEditor::sliderValueChanged(Slider* sliderThatWasMoved)
{
	DBG("Entered method: StereoWidthCtrlAudioProcessorEditor:sliderValueChanged(sliderThatWasMoved)");
	try
	{
		AudioProcessorParameter* param = static_cast<AssociatedSlider*>(sliderThatWasMoved)->getAssociatedParameter();
		if (sliderThatWasMoved == stereoWidthSldCtrl)
		{
			DBG("Changing Width SliderValue from: " + String(param->getValue()) + " to: " + static_cast<String>(stereoWidthSldCtrl->getValue()));
			param->setValueNotifyingHost(static_cast<float>(stereoWidthSldCtrl->getValue()));
		} else if (sliderThatWasMoved == gainSldCtrl)
		{
			try
			{   
				DBG("Gain slider value changing from: " + String(param->getValue()) + " to: " + static_cast<String>(sliderThatWasMoved->getValue()));
				param->setValueNotifyingHost(static_cast<float>(gainSldCtrl->getValue()));
				DBG("audioGainParam is now: " + static_cast<String>(param->getValue()));
			}
			catch (...)
			{
				DBG("Access Violation Exception Caught In PluginEditor.cpp::sliderValueChanged ");
			}
		}
	}
	catch (std::exception& e)
	{
		DBG("Casting >" + sliderThatWasMoved->getName() +"< to AssociatedSlider* Failed: " + String(e.what()));
	}
}



void StereoWidthCtrlAudioProcessorEditor::buttonClicked(Button* buttonThatWasClicked)
{
	DBG("Entered method: StereoWidthCtrlAudioProcessorEditor:buttonClicked(buttonThatWasClicked)");

	StereoWidthCtrlAudioProcessor* audioProc = getProcessor();

	if (buttonThatWasClicked == bypassBtnCtrl)
	{
	 	if (AudioProcessorParameter* param = audioProc->masterBypassParam)
	 	{
	 		DBG("Changing buttonClicked");
	 		param->setValue(static_cast<float>(bypassBtnCtrl->getToggleState()));
	 		DBG("Button->getToggleState = " + String(bypassBtnCtrl->getToggleState()) + " and ourProc Bypass = " + String(param->getValue()));
	 	}
	}
	else if (buttonThatWasClicked == muteBtnCtrl)
	if (buttonThatWasClicked == muteBtnCtrl)
	{
		if (AudioProcessorParameter* param = audioProc->muteAudioParam)
		{
			DBG("Changing muteButton");
			param->setValue(static_cast<float>(muteBtnCtrl->getToggleState()));
		}
	}
	 	else if (buttonThatWasClicked == lockGainBtnCtrl)
	 	{
	 		if (AudioProcessorParameter* param = audioProc->lockGainParam)
	 		{
	 			DBG("Changing Lock Gain");
	 			param->setValue(static_cast<float>(lockGainBtnCtrl->getToggleState()));
	 			if (lockGainBtnCtrl->getToggleState())
	 			{
					// #TODO: THIS IS ALL FUCKED UP
					throw std::logic_error("NO In lockGain button clicked");
	 				/*gainSldCtrl->setValue(std::min(0.251189f, static_cast<float>(gainSldCtrl->getValue())));
	 				gainSldCtrl->repaint();
	 				param->setValue(Decibels::decibelsToGain(static_cast<float>(gainSldCtrl->getValue())));
	 				
	 				getProcessor()->RequestUIUpdate();*/
	 			}
	 			else
	 			{
					throw std::logic_error("NO In lockGain button clicked");
					/*gainSldCtrl->setRange(-96, 12, 0.1);
	 				gainSldCtrl->repaint();
	 				getProcessor()->RequestUIUpdate();*/
	 			}
	 		}
	 	}
	 	else if (buttonThatWasClicked == invertLeftBtnCtrl)
	 	{
	 		if (AudioProcessorParameter* param = audioProc->invertLeftParam)
	 		{
	 			DBG("Before Inverting Left is : " + String(param->getValue()));
	 			param->setValue(static_cast<float>(invertLeftBtnCtrl->getToggleStateValue().getValue()));
	 			DBG("Inverted is: " + String(param->getValue()) + " From toggle : " + String(static_cast<float>(invertLeftBtnCtrl->getToggleStateValue().getValue())));
	 		}
	 	}
	 	else if (buttonThatWasClicked == invertRightBtnCtrl)
	 	{
	 		if (AudioProcessorParameter* param = audioProc->invertRightParam )
	 		{
				DBG("Before Inverting Right is : " + String(param->getValue()));
	 			param->setValue(static_cast<float>(invertRightBtnCtrl->getToggleStateValue().getValue()));
	 
	 			DBG("Inverted is: " + String(param->getValue()) + " From toggle : " + String(static_cast<float>(invertRightBtnCtrl->getToggleStateValue().getValue())));
	 		}
	 	}
}

/// <summary>This method is called automatically every 200ms to update GUI if required</summary>
void StereoWidthCtrlAudioProcessorEditor::timerCallback()
{
	StereoWidthCtrlAudioProcessor* ourProcessor = getProcessor();
	//exchange data between UI Elements and the Plugin (ourProcessor)
	if (ourProcessor->needsUIUpdate())
	{
		// #TODO: THIS IS WRONG timerCallback()
		DBG("In editor->timeCallback");
		muteBtnCtrl->setToggleState(1.0f == ourProcessor->muteAudioParam->getValue(), sendNotification);
		bypassBtnCtrl->setToggleState(1.0f == ourProcessor->masterBypassParam->getValue(), sendNotification);

		DBG("Changing Width SliderValue from proc: " + String(ourProcessor->stereoWidthParam->getValue()) + " to WidthSld/2: " + static_cast<String>(stereoWidthSldCtrl->getValue() ));	
		stereoWidthSldCtrl->setValue(ourProcessor->stereoWidthParam->getValue() , sendNotification);

		DBG("Changing gainSldCtrl Value: " + String(gainSldCtrl->getValue()) + " to audioGainParam: " + String(ourProcessor->audioGainParam->getValue()) );
		gainSldCtrl->setValue(Decibels::gainToDecibels(ourProcessor->audioGainParam->getValue()), sendNotification);
		DBG("gainSldCtrl value set (converted gain to Decibels) : " + String(gainSldCtrl->getValue()));
		
		ourProcessor->ClearUIUpdateFlag();
	}
}
//END==============================================================================
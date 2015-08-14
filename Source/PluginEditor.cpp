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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
StereoWidthCtrlAudioProcessorEditor::StereoWidthCtrlAudioProcessorEditor (StereoWidthCtrlAudioProcessor& ownerFilter)
    : AudioProcessorEditor(ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (WidthCtrlSld = new Slider ("Width Factor Slider"));
    WidthCtrlSld->setRange (0, 5, 0.1);
    WidthCtrlSld->setSliderStyle (Slider::LinearHorizontal);
    WidthCtrlSld->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    WidthCtrlSld->addListener (this);

    addAndMakeVisible (BypassBtn = new TextButton ("Bypass Button"));
    BypassBtn->setButtonText (TRANS("Bypass"));
    BypassBtn->addListener (this);
    BypassBtn->setColour (TextButton::buttonColourId, Colour (0xffe2e2e2));

    addAndMakeVisible (widthLabel = new Label ("Width Label",
                                               TRANS("Stereo Width Factor:")));
    widthLabel->setFont (Font (15.00f, Font::plain));
    widthLabel->setJustificationType (Justification::centredLeft);
    widthLabel->setEditable (false, false, false);
    widthLabel->setColour (Label::textColourId, Colours::grey);
    widthLabel->setColour (TextEditor::textColourId, Colours::black);
    widthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (muteBtn = new TextButton ("Mute Button"));
    muteBtn->setButtonText (TRANS("Mute"));
    muteBtn->addListener (this);
    muteBtn->setColour (TextButton::buttonColourId, Colour (0xffe2e2e2));

    addAndMakeVisible (gainKnob = new GainSlider ("Gain Knob"));
    gainKnob->setRange (-96, 18, 0.1);
    gainKnob->setSliderStyle (Slider::LinearVertical);
    gainKnob->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    gainKnob->setColour (Slider::backgroundColourId, Colour (0x00868181));
    gainKnob->setColour (Slider::trackColourId, Colour (0x7fffffff));
    gainKnob->setColour (Slider::rotarySliderFillColourId, Colour (0x7fbcbcff));
    gainKnob->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    gainKnob->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (375, 500);


    //[Constructor] You can add your own custom stuff here..
	getProcessor()->RequestUIUpdate(); //UI Update must be performed every time a new editor is constructed
	startTimer(200); // Start timer poll with 200ms rate
	BypassBtn->setClickingTogglesState(true);
	muteBtn->setClickingTogglesState(true);
    //[/Constructor]
}

StereoWidthCtrlAudioProcessorEditor::~StereoWidthCtrlAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    WidthCtrlSld = nullptr;
    BypassBtn = nullptr;
    widthLabel = nullptr;
    muteBtn = nullptr;
    gainKnob = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void StereoWidthCtrlAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void StereoWidthCtrlAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    WidthCtrlSld->setBounds (16, 40, 352, 24);
    BypassBtn->setBounds (8, 192, 360, 24);
    widthLabel->setBounds (8, 8, 150, 24);
    muteBtn->setBounds (16, 152, 150, 24);
    gainKnob->setBounds (200, 72, 150, 104);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void StereoWidthCtrlAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
	StereoWidthCtrlAudioProcessor* ourProcessor = getProcessor();
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == WidthCtrlSld)
    {
        //[UserSliderCode_WidthCtrlSld] -- add your slider handling code here..
		DBG("Changing Width SliderValue from: " + String(StereoWidthCtrlAudioProcessor::StereoWidth) + " to: " + static_cast<String>(WidthCtrlSld->getValue()));
		ourProcessor->setParameter(StereoWidthCtrlAudioProcessor::StereoWidth, static_cast<float>(WidthCtrlSld->getValue()));
        //[/UserSliderCode_WidthCtrlSld]
    }
    else if (sliderThatWasMoved == gainKnob)
    {
        //[UserSliderCode_gainKnob] -- add your slider handling code here..
		DBG("Gain slider value changing from: " + String(StereoWidthCtrlAudioProcessor::AudioGain) + " to: " + static_cast<String>(gainKnob->getValue()));
		ourProcessor->setParameter(StereoWidthCtrlAudioProcessor::AudioGain, static_cast<float>(gainKnob->getValue()));
        //[/UserSliderCode_gainKnob]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void StereoWidthCtrlAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
	StereoWidthCtrlAudioProcessor* ourProcessor = getProcessor();
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == BypassBtn)
    {
        //[UserButtonCode_BypassBtn] -- add your button handler code here..
		DBG("Changing buttonClicked");
		ourProcessor->setParameter(StereoWidthCtrlAudioProcessor::MasterBypass, static_cast<float>(BypassBtn->getToggleState()));
		DBG("Button->getToggleState = " + String(BypassBtn->getToggleState()) + " and ourProc Bypass = " + String(ourProcessor->getParameter(StereoWidthCtrlAudioProcessor::MasterBypass)));
        //[/UserButtonCode_BypassBtn]
    }
    else if (buttonThatWasClicked == muteBtn)
    {
        //[UserButtonCode_muteBtn] -- add your button handler code here..
		DBG("Changing muteButton");
		ourProcessor->setParameter(StereoWidthCtrlAudioProcessor::MuteAudio, static_cast<float>(muteBtn->getToggleState()));
        //[/UserButtonCode_muteBtn]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void StereoWidthCtrlAudioProcessorEditor::timerCallback()
{
	StereoWidthCtrlAudioProcessor* ourProcessor = getProcessor();
	//exchange data between UI Elements and the Plugin (ourProcessor)
	if (ourProcessor->needsUIUpdate())
	{
		BypassBtn->setToggleState(1.0f == ourProcessor->getParameter(StereoWidthCtrlAudioProcessor::MasterBypass),
			dontSendNotification);
		WidthCtrlSld->setValue(ourProcessor->getParameter(StereoWidthCtrlAudioProcessor::StereoWidth), dontSendNotification);
		muteBtn->setToggleState(1.0f == ourProcessor->getParameter(StereoWidthCtrlAudioProcessor::MuteAudio), dontSendNotification);
		gainKnob->setValue(ourProcessor->getParameter(StereoWidthCtrlAudioProcessor::AudioGain), dontSendNotification);
		ourProcessor->ClearUIUpdateFlag();
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="StereoWidthCtrlAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="StereoWidthCtrlAudioProcessor&amp; ownerFilter"
                 variableInitialisers="AudioProcessorEditor(ownerFilter)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="0"
                 initialWidth="375" initialHeight="500">
  <BACKGROUND backgroundColour="ff000000"/>
  <SLIDER name="Width Factor Slider" id="8506fc7967803b22" memberName="WidthCtrlSld"
          virtualName="" explicitFocusOrder="0" pos="16 40 352 24" min="0"
          max="5" int="0.10000000000000001" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="Bypass Button" id="7af29ac990473e08" memberName="BypassBtn"
              virtualName="" explicitFocusOrder="0" pos="8 192 360 24" bgColOff="ffe2e2e2"
              buttonText="Bypass" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="Width Label" id="d43333b7c7118250" memberName="widthLabel"
         virtualName="" explicitFocusOrder="0" pos="8 8 150 24" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="Stereo Width Factor:"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="Mute Button" id="914591cf8043a819" memberName="muteBtn"
              virtualName="" explicitFocusOrder="0" pos="16 152 150 24" bgColOff="ffe2e2e2"
              buttonText="Mute" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="Gain Knob" id="dd791eb940d88513" memberName="gainKnob"
          virtualName="" explicitFocusOrder="0" pos="200 72 150 104" bkgcol="868181"
          trackcol="7fffffff" rotarysliderfill="7fbcbcff" rotaryslideroutline="66ffffff"
          min="-96" max="18" int="0.10000000000000001" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

/* ==============================================================================
//  PluginProcessor.cpp
//  Part of the Zentropia JUCE Collection
//  @author Casey Bailey (<a href="SonicZentropy@gmail.com">email</a>)
//  @version 0.1
//  @date 2015/08/17
//  Copyright (C) 2015 by Casey Bailey
//  Provided under the [GNU license]
//
//  Details: Handles main VST processing via reactions to automation
//    	     (which calls the .setParameter() method) as well as GUI handling from PluginEditor.cpp
//
//  Zentropia is hosted on Github at [https://github.com/SonicZentropy]
================================================================================*/

#pragma warning (disable : 4100 )  // get rid of unused param warnings

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "zen_utils/processing/BufferSampleProcesses.h"
#include "zen_utils/converters/DecibelConversions.h"


//==============================================================================
ZenToolAudioProcessor::ZenToolAudioProcessor()
{
	//DBGM("In ZenToolAudioProcessor::ZenToolAudioProcessor() ");
 	addParameter(masterBypassParam = new BoolParameter(0.0f, "MasterBypass"));
 	addParameter(stereoWidthParam = new FloatParameter(0.5f, "StereoWidth"));
	addParameter(muteAudioParam = new BoolParameter(0.0f, "MuteAudio"));
 	addParameter(audioGainParam = new FloatParameter(0.5f, "AudioGain")); //0.5f is 0 gain with this range
 	addParameter(lockGainParam = new BoolParameter(0.0f, "LockGain"));
 	addParameter(invertLeftParam = new BoolParameter(0.0f, "InvertLeft"));
 	addParameter(invertRightParam = new BoolParameter(0.0f, "InvertRight"));
	addParameter(midOnlyParam = new BoolParameter(0.0f, "MidOnly"));
	addParameter(stereoPanParam = new FloatParameter(0.5f, "Pan"));
		
	UIUpdateFlag = true; //flag UI for update
}

ZenToolAudioProcessor::~ZenToolAudioProcessor()
{

}

//==============================================================================

/// <summary>	Process the block. </summary>
/// <remarks>	Zentropy, 8/30/2015. </remarks>
/// <param name="buffer">	   	[in,out] The buffer. </param>
/// <param name="midiMessages">	[in,out] The MIDI messages. </param>
void ZenToolAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	/*
	// Assumes Stereo channels only
	// Assumes Equal number of inputs and outputs
	*/
	if (getNumInputChannels() >= 2 && masterBypassParam->getValue() != 1.0)  //Process channel data here **MAIN LOOP**
	{
		float* leftData = buffer.getWritePointer(0);  //leftData references left channel now
		float* rightData = buffer.getWritePointer(1); //right data references right channel now
		bool stereoWidthProcess = false, audioGainProcess = false, invertLeftProcess = false, invertRightProcess = false, panProcess = false;
		float stereoWidthValue = stereoWidthParam->getValue();
		float audioGainValue = audioGainParam->getValue();
		float invertLeftValue = invertLeftParam->getValue();
		float invertRightValue = invertRightParam->getValue();
		float lockGainValue = lockGainParam->getValue();
		float panValue = stereoPanParam->getValue();

		//Handle Muting
		if (muteAudioParam->getValue())  // MUTE ALL Audio
		{
			for (long i = 0; i  < buffer.getNumSamples(); i++)
			{
				leftData[i] = 0.0f;
				rightData[i] = 0.0f;
			}
			return;
		}		
		else // IF NOT BYPASSED AND NOT MUTED 
		{
			if (stereoWidthValue != stereoWidthParam->getDefaultValue())
			{
				stereoWidthProcess = true;
			}
			if (audioGainValue != audioGainParam->getDefaultValue())
			{
				audioGainProcess = true;
				//convert Audio Gain value to a raw decibel gain value
				audioGainValue = DecibelConversions::decibelRangeGainToRawDecibelGain<float>(audioGainValue, MaxDecibelsInRange, -96.0f);
			}
			if (invertLeftValue != 0.0)
			{
				invertLeftProcess = true;
			}
			if (invertRightValue != 0.0)
			{
				invertRightProcess = true;
			}
			if (panValue != 0.5)
			{
				panProcess = true;
			}
			if (lockGainValue != 0.0 && audioGainValue > 1.0f) //Gain is converted to raw decibel gain now from above
			{
				// #TODO: SOMETHING WRONG WITH LOCK GAIN AFFECTING MID/SIDE
				audioGainProcess = false;
			}
				for (long i = 0; i < buffer.getNumSamples(); i++)
			{
				if (stereoWidthProcess)
				{
					BufferSampleProcesses::processStereoWidth(&leftData[i], &rightData[i], stereoWidthValue);					
				}
				if(audioGainProcess)  //Don't process gain if it's default OR if gain's locked at 0db and gain value > 0db
				{	
					//Process gain					
					BufferSampleProcesses::processGain(&leftData[i], &rightData[i], audioGainValue);
				}
				// Handle polarity inversion
				if (invertLeftProcess)
				{
					BufferSampleProcesses::processInvertLeftChannel(&leftData[i]);
				}
				if (invertRightProcess)
				{
					BufferSampleProcesses::processInvertRightChannel(&rightData[i]);
				}
				if (panProcess)
				{
					//Pan processing
					BufferSampleProcesses::processPanning(&leftData[i], &rightData[i], panValue);
				}

				// Always process these FOR TESTING
				{
					
				}
				// End of Always-Process block
			}
		}
	}
}

//==============================================================================
void ZenToolAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
	XmlElement root("Root");
	XmlElement* el;

	el = root.createNewChildElement("Bypass");
	el->addTextElement(String(masterBypassParam->getValue()));
	el = root.createNewChildElement("StereoWidth");
	el->addTextElement(String(stereoWidthParam->getValue()));
	el = root.createNewChildElement("MuteAudio");
	el->addTextElement(String(muteAudioParam->getValue()));
	el = root.createNewChildElement("Gain");
	el->addTextElement(String(audioGainParam->getValue()));
	el = root.createNewChildElement("InvertLeft");
	el->addTextElement(String(invertLeftParam->getValue()));
	el = root.createNewChildElement("InvertRight");
	el->addTextElement(String(invertRightParam->getValue()));
	el = root.createNewChildElement("LockGain");
	el->addTextElement(String(lockGainParam->getValue()));

	el = root.createNewChildElement("StereoPan");
	el->addTextElement(String(stereoPanParam->getValue()));

	copyXmlToBinary(root, destData);
}

void ZenToolAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
	XmlElement* pRoot = getXmlFromBinary(data, sizeInBytes);
	if (pRoot != nullptr)
	{
		forEachXmlChildElement((*pRoot), pChild)
		{
			if (pChild->hasTagName("Bypass"))
			{
				String text = pChild->getAllSubText();
				setParameter(masterBypassParam->getParameterIndex(), text.getFloatValue());
			} else if (pChild->hasTagName("StereoWidth"))
			{
				String text = pChild->getAllSubText();
				setParameter(stereoWidthParam->getParameterIndex(), text.getFloatValue() );
			} else if (pChild->hasTagName("MuteAudio"))  //This shouldn't work?  Switch MuteAudio to Mute
			{
				String text = pChild->getAllSubText();
				setParameter(muteAudioParam->getParameterIndex(), text.getFloatValue());
			} else if (pChild->hasTagName("Gain"))
			{
				String text = pChild->getAllSubText();
				setParameter(audioGainParam->getParameterIndex(), text.getFloatValue());
			} else if (pChild->hasTagName("InvertLeft"))
			{
				String text = pChild->getAllSubText();
				setParameter(invertLeftParam->getParameterIndex(), text.getFloatValue());
			} else if (pChild->hasTagName("InvertRight"))
			{
				String text = pChild->getAllSubText();
				setParameter(invertRightParam->getParameterIndex(), text.getFloatValue());
			} else if (pChild->hasTagName("LockGain"))
			{
				String text = pChild->getAllSubText();
				setParameter(lockGainParam->getParameterIndex(), text.getFloatValue());
			} else if (pChild->hasTagName("StereoPan"))
			{
				String text = pChild->getAllSubText();
				setParameter( stereoPanParam->getParameterIndex(), text.getFloatValue() );
			}

		}
		delete pRoot;
		UIUpdateFlag = true;
	}
	
}

//==============================================================================

#pragma region overrides
const String ZenToolAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

const String ZenToolAudioProcessor::getInputChannelName(int channelIndex) const
{
	return String(channelIndex + 1);
}

const String ZenToolAudioProcessor::getOutputChannelName(int channelIndex) const
{
	return String(channelIndex + 1);
}

bool ZenToolAudioProcessor::isInputChannelStereoPair(int index) const
{
	return true;
}

bool ZenToolAudioProcessor::isOutputChannelStereoPair(int index) const
{
	return true;
}

bool ZenToolAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool ZenToolAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool ZenToolAudioProcessor::silenceInProducesSilenceOut() const
{
	return true;
}

double ZenToolAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int ZenToolAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
				// so this should be at least 1, even if you're not really implementing programs.
}

int ZenToolAudioProcessor::getCurrentProgram()
{
	return 0;
}

void ZenToolAudioProcessor::setCurrentProgram(int index)
{

}

const String ZenToolAudioProcessor::getProgramName(int index)
{
	return String();
}

void ZenToolAudioProcessor::changeProgramName(int index, const String& newName)
{

}

//==============================================================================

void ZenToolAudioProcessor::prepareToPlay(double inSampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
	//sampleRate = inSampleRate;
	//samplesPerBlock = samplesPerBlock;
}


void ZenToolAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

//==============================================================================
bool ZenToolAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ZenToolAudioProcessor::createEditor()
{
	return new ZenToolGUIEditor(*this);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new ZenToolAudioProcessor();
}
#pragma endregion overrides

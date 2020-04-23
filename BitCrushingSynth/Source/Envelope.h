/*
  ==============================================================================

    Envelope.h
    Created: 12 Apr 2020 4:27:25pm
    Author:  Admin

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Envelope	  : public Component
{
public:
    Envelope(NewProjectAudioProcessor& p);
    ~Envelope();

    void paint (Graphics&) override;
    void resized() override;

private:
	NewProjectAudioProcessor& processor; // reference to processor 

	Slider attackSlider, decaySlider, sustainSlider, releaseSlider;
	
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> sliderAttachAttack, sliderAttachDecay, sliderAttachSustain, sliderAttachRelease;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};

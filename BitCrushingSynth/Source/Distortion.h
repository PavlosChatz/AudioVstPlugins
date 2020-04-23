/*
  ==============================================================================

    Distortion.h
    Created: 20 Apr 2020 10:17:34pm
    Author:  Admin

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Distortion    : public Component
{
public:
    Distortion(NewProjectAudioProcessor& p);
    ~Distortion();

    void paint (Graphics&) override;
    void resized() override;

private:
	NewProjectAudioProcessor& processor;

	Slider distAmount, distDryWet;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> distAmountAttach, distDryWetAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Distortion)
};

/*
  ==============================================================================

    BitCrush.h
    Created: 20 Apr 2020 10:17:54pm
    Author:  Admin

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class BitCrush    : public Component
{
public:
    BitCrush(NewProjectAudioProcessor& p);
    ~BitCrush();

    void paint (Graphics&) override;
    void resized() override;

private:
	NewProjectAudioProcessor& processor;

	Slider bitRedux, rateRedux;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> bitReduxAttach, rateReduxAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BitCrush)
};

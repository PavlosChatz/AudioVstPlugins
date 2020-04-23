/*
  ==============================================================================

    Lfo.h
    Created: 14 Apr 2020 11:23:28pm
    Author:  Admin

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Lfo    : public Component
{
public:
    Lfo(NewProjectAudioProcessor& );
    ~Lfo();

    void paint (Graphics&) override;
    void resized() override;

private:
	Slider lfo1Freq, lfo2Freq;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> lfo1FreqAttach, lfo2FreqAttach;

	ComboBox lfo1Menu, lfo2Menu;
	ScopedPointer < AudioProcessorValueTreeState::ComboBoxAttachment> lfo1MenuAttach, lfo2MenuAttach;

	NewProjectAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Lfo)
};

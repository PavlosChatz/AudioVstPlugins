/*
  ==============================================================================

    Oscillator.h
    Created: 12 Apr 2020 4:26:24pm
    Author:  Admin

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Oscillator    : public Component,
	private  ComboBox::Listener
{
public:
    Oscillator(NewProjectAudioProcessor& );
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;
	void comboBoxChanged(ComboBox*) override;

private:
	NewProjectAudioProcessor& processor; // reference to processor 
	ComboBox osc1Menu, osc2Menu;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> wave1Selection, wave2Selection;
	Slider oscMix;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> oscMixAttachment;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};

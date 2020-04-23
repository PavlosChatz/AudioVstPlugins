/*
  ==============================================================================

    Filter.h
    Created: 12 Apr 2020 3:48:33pm
    Author:  Admin

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Filter    : public Component
{
public:
    Filter(NewProjectAudioProcessor& p);
    ~Filter();

    void paint (Graphics&) override;
    void resized() override;

private:
	Slider filterCutoff, filterRes;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterCutoffAttach, filterResAttach;

	ComboBox filterMenu;
	ScopedPointer < AudioProcessorValueTreeState::ComboBoxAttachment> filterMenuAttach;

	NewProjectAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};

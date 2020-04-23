/*
  ==============================================================================

    Filter.cpp
    Created: 12 Apr 2020 3:48:33pm
    Author:  Admin

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"

//==============================================================================
Filter::Filter(NewProjectAudioProcessor& p) : processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
	setSize(200, 200);

	filterMenu.addItem("Low Pass", 1);
	filterMenu.addItem("High Pass", 2);
	filterMenu.addItem("Band Pass", 3);
	filterMenu.setJustificationType(Justification::centred);
	addAndMakeVisible(&filterMenu);

	filterMenuAttach = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "filterType", filterMenu);
	
	filterCutoff.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	filterCutoff.setRange(20.0, 15000.0);
	filterCutoff.setValue(1000.0);
	filterCutoff.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&filterCutoff);
	filterCutoff.setSkewFactorFromMidPoint(1000.0); // Log control - after addandMakevisible


	filterRes.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	filterRes.setRange(1.0, 5.0);
	filterRes.setValue(1.0);
	filterRes.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&filterRes);

	filterCutoffAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "filterCutoff", filterCutoff);
	filterResAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "filterRes", filterRes);
}

Filter::~Filter()
{
}

void Filter::paint (Graphics& g)
{
	Rectangle<int> titleArea(0, 10, getWidth(), 20);
	g.fillAll(Colours::black);
	g.setColour(Colours::white);
	g.drawText("Filter", titleArea, Justification::centredTop);

	Rectangle<float> area(25, 25, 150, 150);

	g.setColour(Colours::yellow);
	g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Filter::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
	Rectangle<int> area = getLocalBounds().reduced(40);

	filterMenu.setBounds(area.removeFromTop(20));
	filterCutoff.setBounds(30, 100, 70, 70);
	filterRes.setBounds(100, 100, 70, 70);
}

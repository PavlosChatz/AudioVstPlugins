/*
  ==============================================================================

    Oscillator.cpp
    Created: 12 Apr 2020 4:26:24pm
    Author:  Admin

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(NewProjectAudioProcessor& p) : processor(p) //, unsigned int index
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

	setSize(200, 200);

	osc1Menu.addItem("Sine", 1);
	osc1Menu.addItem("Saw", 2);
	osc1Menu.addItem("Square", 3);
	addAndMakeVisible(&osc1Menu);
	osc1Menu.addListener(this);
	osc1Menu.setJustificationType(Justification::centred);

	wave1Selection = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "waveshape1", osc1Menu); //+std::to_string(index)

	osc2Menu.addItem("Sine", 1);
	osc2Menu.addItem("Saw", 2);
	osc2Menu.addItem("Square", 3);
	addAndMakeVisible(&osc2Menu);
	osc2Menu.addListener(this);
	osc2Menu.setJustificationType(Justification::centred);

	wave2Selection = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "waveshape2", osc2Menu); //+std::to_string(index)

	oscMix.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	oscMix.setRange(0.0, 1.0);
	oscMix.setValue(0.7);
	oscMix.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&oscMix);
	//oscMix.setSkewFactorFromMidPoint(0.1); // Log control - after addandMakevisible

	oscMixAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "oscMix", oscMix);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
{
	Rectangle<int> titleArea(0, 10, getWidth(), 20);

	g.fillAll(Colours::black);
	g.setColour(Colours::white);
	g.drawText("Oscillators", titleArea, Justification::centredTop);

	Rectangle<float> area(25, 25, 150, 150);

	g.setColour(Colours::yellow);
	g.drawRoundedRectangle(area, 20.0f, 2.0f);

}

void Oscillator::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
	Rectangle<int> rect = getLocalBounds().reduced(40);

	osc1Menu.setBounds(rect.removeFromTop(20));
	osc2Menu.setBounds(rect.removeFromBottom(20));

	oscMix.setBounds(rect.removeFromRight(50));
}

void Oscillator::comboBoxChanged(ComboBox* box) {

}
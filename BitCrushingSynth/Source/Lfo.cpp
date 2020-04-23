/*
  ==============================================================================

    Lfo.cpp
    Created: 14 Apr 2020 11:23:28pm
    Author:  Admin

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Lfo.h"
#include "PluginProcessor.h"

//==============================================================================
Lfo::Lfo(NewProjectAudioProcessor& p) : processor(p)
{
	setSize(200, 200);

	lfo1Menu.addItem("Triangle", 1);
	lfo1Menu.addItem("Square", 2);
	lfo1Menu.setJustificationType(Justification::centred);
	addAndMakeVisible(&lfo1Menu);
	lfo1MenuAttach = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "lfo1Shape", lfo1Menu);

	lfo1Freq.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	lfo1Freq.setRange(0.01, 10.0);
	lfo1Freq.setValue(1.0);
	lfo1Freq.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&lfo1Freq);
	lfo1Freq.setSkewFactorFromMidPoint(0.1); // Log control - after addandMakevisible
	lfo1FreqAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "lfo1Freq", lfo1Freq);


	lfo2Menu.addItem("Triangle", 1);
	lfo2Menu.addItem("Square", 2);
	lfo2Menu.setJustificationType(Justification::centred);
	addAndMakeVisible(&lfo2Menu);
	lfo2MenuAttach = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "lfo2Shape", lfo2Menu);

	lfo2Freq.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	lfo2Freq.setRange(0.01, 10.0);
	lfo2Freq.setValue(1.0);
	lfo2Freq.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	lfo2Freq.setSkewFactorFromMidPoint(0.1); // Log control - after addandMakevisible
	addAndMakeVisible(&lfo2Freq);
	lfo2FreqAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "lfo2Freq", lfo2Freq);

}

Lfo::~Lfo()
{
}

void Lfo::paint (Graphics& g)
{

	Rectangle<int> titleArea(0, 10, getWidth(), 20);
	g.fillAll(Colours::black);
	g.setColour(Colours::white);
	g.drawText("LFOs", titleArea, Justification::centredTop);

	Rectangle<float> area(25, 25, 150, 150);
	g.setColour(Colours::red);
	g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Lfo::resized()
{
	int width = 50, height = 80;

	Rectangle<int> area = getLocalBounds().reduced(30);
	height = area.getHeight() / 2;
	Rectangle<int> firstRow = area.removeFromTop(height);
	Rectangle<int> secondRow = area.removeFromBottom(height);
	lfo1Freq.setBounds(firstRow.removeFromLeft(width));
	lfo1Menu.setBounds(firstRow.removeFromLeft(70).removeFromBottom(25));
	lfo2Freq.setBounds(secondRow.removeFromLeft(width));
	lfo2Menu.setBounds(secondRow.removeFromLeft(70).removeFromBottom(25));
}
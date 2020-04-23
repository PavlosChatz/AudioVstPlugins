/*
  ==============================================================================

    BitCrush.cpp
    Created: 20 Apr 2020 10:17:54pm
    Author:  Admin

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "BitCrush.h"

//==============================================================================
BitCrush::BitCrush(NewProjectAudioProcessor& p) : processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

	setSize(200, 200);

	bitRedux.setName("Bits");
	bitRedux.setSliderStyle(Slider::SliderStyle::LinearVertical);
	bitRedux.setRange(1.0, 16.0);
	bitRedux.setValue(16.0);
	bitRedux.setColour(Slider::textBoxTextColourId, Colours::white);
	bitRedux.setTextBoxStyle(Slider::TextBoxBelow, false, 200, 20);
	addAndMakeVisible(&bitRedux);

	bitReduxAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "bitRedux", bitRedux);

	rateRedux.setName("Rate");
	rateRedux.setSliderStyle(Slider::SliderStyle::LinearVertical);
	rateRedux.setRange(1.0, 32.0);
	rateRedux.setValue(1.0);
	rateRedux.setColour(Slider::textBoxTextColourId, Colours::white);
	rateRedux.setTextBoxStyle(Slider::TextBoxBelow, false, 200, 20);
	addAndMakeVisible(&rateRedux);

	rateReduxAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "rateRedux", rateRedux);


}

BitCrush::~BitCrush()
{
}

void BitCrush::paint(Graphics& g)
{
	/* This demo code just fills the component's background and
	   draws some placeholder text to get you started.

	   You should replace everything in this method with your own
	   drawing code..
	*/

	Rectangle<int> titleArea(0, 10, getWidth(), 20);

	g.fillAll(Colours::black);
	g.setColour(Colours::white);
	g.drawText("Bit Crusher", titleArea, Justification::centredTop);

	Rectangle<float> area(25, 25, 150, 150);

	g.setColour(Colours::red);
	g.drawRoundedRectangle(area, 20.0f, 2.0f);

	g.setColour(Colours::beige);
	int labelW = 100;
	g.drawText("Bit Crush", bitRedux.getX() + bitRedux.getWidth() / 2 - labelW / 2, 25, labelW, 20, Justification::centredBottom);
	g.drawText("Rate Crush", rateRedux.getX() + rateRedux.getWidth() / 2 - labelW / 2, 25, labelW, 20, Justification::centredBottom);

}

void BitCrush::resized()
{
	Rectangle<int> area = getLocalBounds();
	const int compWidth = 100, compHeight = 200;

	bitRedux.setBounds(area.removeFromLeft(compWidth).removeFromTop(compHeight).reduced(30).withTrimmedTop(30));
	rateRedux.setBounds(area.removeFromLeft(compWidth).removeFromTop(compHeight).reduced(30).withTrimmedTop(30));

}

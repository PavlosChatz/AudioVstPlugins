/*
  ==============================================================================

    Distortion.cpp
    Created: 20 Apr 2020 10:17:34pm
    Author:  Admin

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Distortion.h"

//==============================================================================
Distortion::Distortion(NewProjectAudioProcessor& p) : processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

	setSize(200, 200);

	distAmount.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	distAmount.setRange(1.0, 10.0);
	distAmount.setValue(1.0);
	distAmount.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&distAmount);

	distAmountAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "distAmount", distAmount);

	distDryWet.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	distDryWet.setRange(0.0, 1.0);
	distDryWet.setValue(1.0);
	distDryWet.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&distDryWet);

	distDryWetAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "distDryWet", distDryWet);

}

Distortion::~Distortion()
{
}

void Distortion::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

	Rectangle<int> titleArea(0, 10, getWidth(), 20);

	g.fillAll(Colours::black);
	g.setColour(Colours::white);
	g.drawText("Distortion", titleArea, Justification::centredTop);

	Rectangle<float> area(25, 25, 150, 150);

	g.setColour(Colours::yellow);
	g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Distortion::resized()
{
	Rectangle<int> rect = getLocalBounds().reduced(50);

	distAmount.setBounds(rect.removeFromTop(50));
	distDryWet.setBounds(rect.removeFromBottom(50));

}

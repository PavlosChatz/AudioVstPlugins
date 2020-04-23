/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), osc1Gui(p), lfoGui(p), envGui(p), filGui(p), bitGui(p), distGui(p)
{
    setSize (600, 400);

	addAndMakeVisible(&osc1Gui);
	addAndMakeVisible(&lfoGui);
	addAndMakeVisible(&envGui);
	addAndMakeVisible(&filGui);
	addAndMakeVisible(&distGui);
	addAndMakeVisible(&bitGui);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    //g.setColour (Colours::white);
    //g.setFont (15.0f);
   // g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
	Rectangle<int> rect = getLocalBounds();
	const int compWidth = 200, compHeight = 200;

	osc1Gui.setBounds(rect.removeFromLeft(compWidth).removeFromTop(compHeight));
	envGui.setBounds(rect.removeFromLeft(compWidth).removeFromTop(compHeight));
	filGui.setBounds(rect.removeFromLeft(compWidth).removeFromTop(compHeight));
	rect = getLocalBounds();
	lfoGui.setBounds(0, 200, compWidth, compHeight);
	distGui.setBounds(200, 200, compWidth, compHeight);
	bitGui.setBounds(400, 200, compWidth, compHeight);
}



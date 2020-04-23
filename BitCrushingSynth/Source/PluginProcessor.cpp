/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
tree(*this, nullptr)

#endif
{
	NormalisableRange<float> attackParam(0.1, 5000.0f);
	NormalisableRange<float> decayParam(0.1, 2000.0f);
	NormalisableRange<float> sustainParam(0.1, 1.0f);
	NormalisableRange<float> releaseParam(0.1, 5000.0f);
	tree.createAndAddParameter("attack", "Attack", "Attack", attackParam, 1000.0f, nullptr, nullptr);
	tree.createAndAddParameter("decay", "Decay", "Decay", decayParam, 200.0f, nullptr, nullptr);
	tree.createAndAddParameter("sustain", "Sustain", "Sustain", sustainParam, 0.8f, nullptr, nullptr);
	tree.createAndAddParameter("release", "Release", "Release", releaseParam, 3000.0f, nullptr, nullptr);
	
	NormalisableRange<float> waveShape1Param(0, 2);
	NormalisableRange<float> waveShape2Param(0, 2);
	NormalisableRange<float> oscMixParam(0.01, 0.99);
	tree.createAndAddParameter("waveshape1", "Waveshape1", "waveshape1", waveShape1Param, 0, nullptr, nullptr);
	tree.createAndAddParameter("waveshape2", "Waveshape2", "waveshape2", waveShape2Param, 2, nullptr, nullptr);
	tree.createAndAddParameter("oscMix", "oscMix", "oscMix", oscMixParam, 0.5, nullptr, nullptr);

	NormalisableRange<float> filterTypeParam(0, 2);
	NormalisableRange<float> filterCutParam(20.0f, 2000.0f);
	NormalisableRange<float> filterResParam(1.0f, 20.0f);
	tree.createAndAddParameter("filterType", "filterType", "filterType", filterTypeParam, 0, nullptr, nullptr);
	tree.createAndAddParameter("filterCutoff", "filterCutoff", "filterCutoff", filterCutParam, 250.0f, nullptr, nullptr);
	tree.createAndAddParameter("filterRes", "filterRes", "filterRes", filterResParam, 4.0f, nullptr, nullptr);

	NormalisableRange<float> lfo1ShapeParam(0, 1);
	NormalisableRange<float> lfo2ShapeParam(0, 1);
	NormalisableRange<float> lfo1FreqParam(0.01f, 10.0f);
	NormalisableRange<float> lfo2FreqParam(0.01f, 10.0f);
	tree.createAndAddParameter("lfo1Shape", "lfo1Shape", "lfo1Shape", lfo1ShapeParam, 0, nullptr, nullptr);
	tree.createAndAddParameter("lfo2Shape", "lfo2Shape", "lfo2Shape", lfo2ShapeParam, 1, nullptr, nullptr);
	tree.createAndAddParameter("lfo1Freq", "lfo1Freq", "lfo1Freq", lfo1FreqParam, 0.5, nullptr, nullptr);
	tree.createAndAddParameter("lfo2Freq", "lfo2Freq", "lfo2Freq", lfo2FreqParam, 7.0, nullptr, nullptr);

	NormalisableRange<float> distAmountParam(1.0, 10.0);
	NormalisableRange<float> distDryWetParam(0.0f, 1.0f);
	tree.createAndAddParameter("distAmount", "distAmount", "distAmount", distAmountParam, 5.0, nullptr, nullptr);
	tree.createAndAddParameter("distDryWet", "distDryWet", "distDryWet", distDryWetParam, 0.7, nullptr, nullptr);

	NormalisableRange<float> bitReduxParam(1.0, 16.0);
	NormalisableRange<float> rateReduxParam(1.0f, 30.0f);
	tree.createAndAddParameter("bitRedux", "bitRedux", "bitRedux", bitReduxParam, 4.0, nullptr, nullptr);
	tree.createAndAddParameter("rateRedux", "rateRedux", "rateRedux", rateReduxParam, 3.0, nullptr, nullptr);

	mySynth.clearVoices();
	for (int i = 0; i < 5; i++) {
		mySynth.addVoice(new SynthVoice());
	}
	mySynth.clearSounds();
	mySynth.addSound(new SynthSound());
}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
}

//==============================================================================
const String NewProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NewProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NewProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NewProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewProjectAudioProcessor::setCurrentProgram (int index)
{
}

const String NewProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void NewProjectAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void NewProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	ignoreUnused(samplesPerBlock);
	lastSampleRate = sampleRate;
	mySynth.setCurrentPlaybackSampleRate(lastSampleRate);

}

void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void NewProjectAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }


	for (int i = 0; i < mySynth.getNumVoices(); i++) {
		if (myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))) {
			myVoice->getEnvelopeParams(tree.getRawParameterValue("attack"),
										tree.getRawParameterValue("decay"),
										tree.getRawParameterValue("sustain"),
										tree.getRawParameterValue("release"));
			myVoice->getOscParams(tree.getRawParameterValue("waveshape1"),
									tree.getRawParameterValue("waveshape2"),
									tree.getRawParameterValue("oscMix"));
			myVoice->getLfoParams(tree.getRawParameterValue("lfo1Shape"),
									tree.getRawParameterValue("lfo2Shape"),
									tree.getRawParameterValue("lfo1Freq"),
									tree.getRawParameterValue("lfo2Freq"));
			myVoice->getFilterParams(tree.getRawParameterValue("filterType"),
									 tree.getRawParameterValue("filterCutoff"),
									 tree.getRawParameterValue("filterRes"));
			myVoice->getBitCrushParams(tree.getRawParameterValue("bitRedux"),
									tree.getRawParameterValue("rateRedux"));
			myVoice->getDistortionParams(tree.getRawParameterValue("distAmount"),
									tree.getRawParameterValue("distDryWet"));
		}
	}


	buffer.clear();
	mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

}

//==============================================================================
bool NewProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
    return new NewProjectAudioProcessorEditor (*this);
}

//==============================================================================
void NewProjectAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NewProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}

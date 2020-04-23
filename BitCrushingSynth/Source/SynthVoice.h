/*
  ==============================================================================

    SynthVoice.h
    Created: 29 Mar 2020 9:49:11pm
    Author:  Admin

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public SynthesiserVoice {
public:

	bool canPlaySound(SynthesiserSound* sound) {
		return dynamic_cast<SynthSound*>(sound) != nullptr;
	}
	// ==================================
	void getOscParams(float* selection1, float* selection2, float* mix) {
		waveShape1 = (int)*selection1;
		waveShape2 = (int)*selection2;
		oscMix = (double) *mix;
	}
	double sampleOsc1() {
		if (waveShape1 == 0)
			return osc1.sinewave(modulate(frequency, lfo2ModAmount * 0.01 * frequency, sampleLfo2()));
		else if (waveShape1 == 1)
			return osc1.saw(modulate(frequency, lfo2ModAmount * 0.01 * frequency, sampleLfo2()));
		else if (waveShape1 == 2)
			osc1.square(modulate(frequency, lfo2ModAmount * 0.01 * frequency, sampleLfo2()));
		else
			osc1.sinewave(frequency);
	}
	double sampleOsc2() {
		if (waveShape2 == 0)
			return osc2.sinewave(modulate(frequency, lfo2ModAmount * 0.01 * frequency, sampleLfo2()));
		else if (waveShape2 == 1)
			return osc2.saw(modulate(frequency, lfo2ModAmount * 0.01 * frequency, sampleLfo2()));
		else if (waveShape2 == 2)
			osc2.square(modulate(frequency, lfo2ModAmount * 0.01 * frequency, sampleLfo2()));
		else
			osc2.sinewave(frequency);
	}
	// ==================================
	void getLfoParams(float* selection1, float* selection2, float* freq1, float* freq2) {
		lfo1Shape = (int)*selection1;
		lfo2Shape = (int)*selection2;
		lfo1Freq = (double)*freq1;
		lfo2Freq = (double)*freq2;
		lfo1ModAmount = 0.0;
		lfo2ModAmount = 1.0;
	}

	double sampleLfo1() {
		switch (lfo1Shape) {
		case 0: return lfo1.triangle(lfo1Freq);
		case 1: return lfo1.square(lfo1Freq);
		}
	}
	double sampleLfo2() {
		switch (lfo2Shape) {
		case 0: return lfo2.triangle(lfo2Freq);
		case 1: return lfo2.square(lfo2Freq);
		}
	}

	double modulate(double toMod, double modAmount, double lfovalue) {
		return toMod + modAmount * lfovalue;
	}
	// ==================================
	void getEnvelopeParams(float *attack, float* decay, float* sustain, float *release) {
		env1.setAttack(double(*attack));
		env1.setDecay(double(*decay));
		env1.setSustain(double(*sustain));
		env1.setRelease(double(*release));
	}

	double applyEnvelope() {
		return env1.adsr(mix(sampleOsc1(), sampleOsc2(), oscMix), env1.trigger);
	}

	double mix(double value1, double value2, double mix) {
		return value1 * (1 - mix)+ value2 * mix;
	}
	// ==================================
	void getFilterParams(float* fType, float* fCutoff, float* fRes) {
		cutoff = double(*fCutoff);
		res = double(*fRes);
		filterType = (int)*fType;
	}
	
	double applyFilter() {
		switch (filterType) {
		case 0: return fil1.lores(applyEnvelope(), modulate(cutoff, lfo1ModAmount, sampleLfo1()), res); break;
		case 1: return fil1.hires(applyEnvelope(), modulate(cutoff, lfo1ModAmount, sampleLfo1()), res); break;
		case 2: return fil1.bandpass(applyEnvelope(), modulate(cutoff, lfo1ModAmount, sampleLfo1()), res); break;
		}
		return fil1.lores(applyEnvelope(), modulate(cutoff, lfo1ModAmount, sampleLfo1()), res);
	}

	// ==================================
	void getDistortionParams(float *amount, float* dryWet){
		distAmount = (double)*amount;
		distDryWet = (double)*dryWet;
	}
	double applyDistortion() {
		return dist1.fastAtanDist(applyFilter(), distAmount);
	}
	// ==================================
	void getBitCrushParams(float* bitDepth, float* rateRatio) {
		bitRedux = *bitDepth;
		rateRedux = (int) *rateRatio;
	}

	// ==================================
	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) {
		
		env1.trigger = 1;
		frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
		level = velocity;
	}

	void stopNote(float velocity, bool allowTailOff) {
		
		env1.trigger = 0;
		allowTailOff = true;
		if (velocity == 0)
			clearCurrentNote();

	}

	void pitchWheelMoved(int newPitchWheelValue) {

	}

	void controllerMoved(int controllerNumber, int newControllerValue) {

	}
	
	void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) {

		for (int sample = 0; sample < numSamples; sample++) {

			for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++) {
				outputBuffer.addSample(channel, startSample, applyDistortion());
			}
			startSample++;
		}
		
		for (int chan = 0; chan < outputBuffer.getNumChannels(); chan++) { // or outputBuffer
			float* data = outputBuffer.getWritePointer(chan);
			for (int i = 0; i < numSamples; i++) {

				/// Bit Depth Reduction
				float numQuantizationLevels = powf(2, bitRedux);
				float remainder = fmodf(data[i], 1.0f / numQuantizationLevels);
				data[i] -= remainder;

				if (rateRedux > 1) {
					if (i % rateRedux != 0) data[i] = data[i - i % rateRedux];
				}

				data[i] = fil2.hires(data[i], 30, 2.0); // for freqs <20, >10000
				//data[i] = fil3.lopass(data[i], 15000.0);
			}
		}

	}

private:
	maxiOsc osc1, osc2;
	maxiOsc lfo1, lfo2;
	maxiEnv env1;
	maxiFilter fil1, fil2, fil3; 
	maxiDistortion dist1;
	double sample;
	int waveShape1, waveShape2; // Osc
	double frequency, oscMix, level;
	int filterType; // Fil
	double cutoff, res;
	int lfo1Shape, lfo2Shape; // Lfo
	double lfo1Freq, lfo2Freq; 
	double lfo1ModAmount, lfo2ModAmount;
	double distAmount, distDryWet; // Disto
	int rateRedux; // Bit
	float bitRedux;
	//float numQuantizationLevels, remainder;
};
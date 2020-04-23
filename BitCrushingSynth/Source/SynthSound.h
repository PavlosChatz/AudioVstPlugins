/*
  ==============================================================================

    SynthSound.h
    Created: 29 Mar 2020 9:49:04pm
    Author:  Admin

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound {
public:
	bool appliesToNote(int /*midiNoteNumber*/) {
		return true;
	}
	bool appliesToChannel(int /*midiChannel*/) {
		return true;
	}
};


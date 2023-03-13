/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"
#include "ui/PhaseViewer.h"
#include "ui/SimpleSlider.h"
#include "ui/WaveViewer.h"

//==============================================================================
/**
*/
class SimpleFlangerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit SimpleFlangerAudioProcessorEditor (SimpleFlangerAudioProcessor&);

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleFlangerAudioProcessor& audioProcessor;
    PhaseViewer m_phaseViewer;
    WaveViewer m_waveViewer;
    simpleFlanger::Knob m_beginDelay;
    simpleFlanger::Knob m_endDelay;
    simpleFlanger::Knob m_feedback;
    simpleFlanger::Knob m_lfoRate;
    simpleFlanger::Knob m_drywet;
    simpleFlanger::Knob m_rawMix;
    simpleFlanger::Knob m_processedMix;
    simpleFlanger::Knob m_widePhase;
    simpleFlanger::Knob m_waveTablePos;
    simpleFlanger::Knob m_numNoiseGen;
    simpleFlanger::Knob m_noiseJitter;
    simpleFlanger::Knob m_feedbackDamp;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleFlangerAudioProcessorEditor)
};

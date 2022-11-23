/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "ui/SimpleSlider.h"
#include "ui/PhaseViewer.h"
#include "ui/WaveViewer.h"

//==============================================================================
/**
*/
class SimpleFlangerAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                    juce::Slider::Listener
{
public:
    SimpleFlangerAudioProcessorEditor (SimpleFlangerAudioProcessor&);
    ~SimpleFlangerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider);
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleFlangerAudioProcessor& audioProcessor;

    // universal param
    SimpleSlider m_beginDelaySlider;
    SimpleSlider m_endDelaySlider;
    SimpleSlider m_mixSlider;
    SimpleSlider m_DelayMixSlider;
    SimpleSlider m_feedbackSlider;
    SimpleSlider m_dryWetSlider;

    // lfo param
    SimpleSlider m_lfoRateSlider;
    SimpleSlider m_lfoSyncRateSlider;
    juce::ToggleButton m_followBPM;

    // stereo param
    SimpleSlider m_phaseSlider;

    // viewer
    PhaseViewer m_viewer;

    // waveTable view
    WaveViewer m_waveViewer;
    SimpleSlider m_sampleBeginSlider;
    SimpleSlider m_sampleEndSlider;

    static constexpr auto kTextSize = 80;
    static constexpr auto kTextHeight = 14;
    static constexpr int kSliderHeight = 20;
    static constexpr int kSliderInterver = 30;
    static constexpr int kSliderInterver2 = 35;
    static constexpr int kToggleWidth = 80;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleFlangerAudioProcessorEditor)
};

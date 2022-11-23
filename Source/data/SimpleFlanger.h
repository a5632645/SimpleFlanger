/*
  ==============================================================================

    SimpleFlanger.h
    Created: 30 Oct 2022 10:01:56am
    Author:  mana

  ==============================================================================
*/

#pragma once
#include "DelayTimeSupportor/IDelayTimeSupportor.h"
#include "DelayTimeSupportor/lfo.h"
#include "MonoFlanger.h"

class SimpleFlanger
{
public:
    SimpleFlanger();

    void prepare(float fs, int frameExpected);
    void processceBlock(juce::AudioBuffer<float>& buffer);

    void setDryWet(float var) {
        m_wet.setTargetValue(var);
        m_dry.setTargetValue(1.f - var);
    }

    IDelayTimeSupportor* m_Supportor;

public:
    DTSupportor::lfoSupportor m_lfo;


    MonoFlanger m_left;
    MonoFlanger m_right;

    juce::SmoothedValue<float> m_mix;
    juce::SmoothedValue<float> m_DelayMix;
    juce::SmoothedValue<float> m_feedback;

private:
    float m_leftLastSample;
    float m_rightLastSample;

    std::vector<float> m_lTime, m_rTime;

public:
    // dry wet param
    juce::SmoothedValue<float> m_dry;
    juce::SmoothedValue<float> m_wet;
    juce::AudioBuffer<float> m_dryBuffer;
};
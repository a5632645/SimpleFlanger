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
#include "MonoDelayLine.h"

class SimpleFlanger
{
public:
    class LPF {
    public:
        void setCutOffFrequency(float cutoff) {
            m_cutoff = cutoff;
            auto g = float(std::tan(juce::MathConstants<double>::pi * m_cutoff / sampleRate));
            G = g / (1 + g);
        }

        float process(float inputValue) {
            auto v = G * (inputValue - s);
            auto y = v + s;
            s = y + v;
            return y;
        }

        float m_cutoff = 24000.f;
        float sampleRate = 48000.f;
    private:
        float s = 0.f;
        float G = 0.f;
    };

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


    MonoDelayLine m_left;
    MonoDelayLine m_right;
    LPF m_leftDampLPF;
    LPF m_rightDampLPF;

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
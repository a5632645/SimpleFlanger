/*
  ==============================================================================

    MonoFlanger.h
    Created: 30 Oct 2022 9:01:21pm
    Author:  mana

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MonoFlanger
{
public:
    MonoFlanger()
        :m_sampleRate(48000.f), m_wpos(0), m_delayTime(0.f)
    {
    }

    void prepare(float fs, int frameExpected)
    {
        m_sampleRate = fs;
        m_delayBuffer.setSize(1, (int)std::ceil(fs * kMaxDelayTime / 1000.f + 1.f));
        m_delayBuffer.clear();

        juce::ignoreUnused(frameExpected);
    }

    forcedinline void pushSample(float in)
    {
        m_delayBuffer.setSample(0, m_wpos, in);

        m_wpos = (++m_wpos) % m_delayBuffer.getNumSamples();
    }

    forcedinline float popSample(float delay)
    {
        delay = juce::jlimit(0.f, kMaxDelayTime, delay);

        m_delayTime.setTargetValue(delay);

        float delayTime = m_delayTime.getNextValue();

        float rpos = fmodf(m_wpos - delayTime * m_sampleRate / 1000.f - 1.f + m_delayBuffer.getNumSamples(), (float)m_delayBuffer.getNumSamples());

        int previous = (int)floorf(rpos);
        int next = (previous+1) % m_delayBuffer.getNumSamples();

        float fractor = rpos - previous;
        float out = m_delayBuffer.getSample(0, previous) + fractor * (m_delayBuffer.getSample(0, next) - m_delayBuffer.getSample(0, previous));

        return out;
    }

    float getDelayTime() const
    {
        return m_delayTime.getTargetValue();
    }

    static constexpr float kMaxDelayTime = 100.f;// this value control total max delay time
private:
    float m_sampleRate;
    int m_wpos;

    juce::SmoothedValue<float> m_delayTime;
    juce::AudioBuffer<float> m_delayBuffer;
};
/*
  ==============================================================================

    SimpleFlanger.cpp
    Created: 30 Oct 2022 10:01:56am
    Author:  mana

  ==============================================================================
*/

#include "SimpleFlanger.h"

SimpleFlanger::SimpleFlanger()
    :m_mix(0.f), m_feedback(0.f),
    m_leftLastSample(0.f), m_rightLastSample(0.f),
    m_dry(1.f), m_wet(0.f), m_Supportor(&m_lfo)
{
}

void SimpleFlanger::prepare(float fs, int frameExpected)
{
    m_Supportor->prepare(fs,frameExpected);

    m_left.prepare(fs, frameExpected);
    m_right.prepare(fs, frameExpected);

    m_dryBuffer.setSize(2, frameExpected);

    m_lTime.resize(frameExpected);
    m_rTime.resize(frameExpected);
}

void SimpleFlanger::processceBlock(juce::AudioBuffer<float>& buffer)
{
    m_dryBuffer.copyFrom(0, 0, buffer.getReadPointer(0), buffer.getNumSamples());
    m_dryBuffer.copyFrom(1, 0, buffer.getReadPointer(1), buffer.getNumSamples());
    m_dry.applyGain(m_dryBuffer, m_dryBuffer.getNumSamples());

    float* lptr = buffer.getWritePointer(0);
    float* rptr = buffer.getWritePointer(1);

    auto size = buffer.getNumSamples();

    m_Supportor->getDelayTimes(m_lTime, m_rTime);

    for (int i = 0; i < size; ++i) 
    {
        float delayMix = m_DelayMix.getNextValue();
        float mix = m_mix.getNextValue();
        float feedback = m_feedback.getNextValue();


        m_left.pushSample(lptr[i] + feedback * m_leftLastSample);
        m_leftLastSample = m_left.popSample(m_lTime[i]);
        lptr[i] = m_leftLastSample * delayMix + lptr[i] * mix;

        m_right.pushSample(rptr[i] + feedback * m_rightLastSample);
        m_rightLastSample = m_right.popSample(m_rTime[i]);
        rptr[i] = m_rightLastSample * delayMix + rptr[i] * mix;
    }

    m_wet.applyGain(buffer, buffer.getNumSamples());
    buffer.addFrom(0, 0, m_dryBuffer.getReadPointer(0), m_dryBuffer.getNumSamples());
    buffer.addFrom(1, 0, m_dryBuffer.getReadPointer(1), m_dryBuffer.getNumSamples());
}

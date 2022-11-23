/*
  ==============================================================================

    IDelayTimeSupportor.h
    Created: 30 Oct 2022 10:02:37am
    Author:  mana

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class IDelayTimeSupportor
{
//public:
//    enum Type
//    {
//        Static,
//        LFO,
//        Envelop
//    };
//
//    //static float sine(float phase)
//    //{
//    //    return std::sinf(phase * juce::MathConstants<float>::pi);
//    //}
//
//    // static float ramp(float phase)
//    // {
//    //     return phase;
//    // }
//
//    // static float tri(float phase)
//    // {
//    //     if (phase < 0.5f) {
//    //         return phase / 0.5f;
//    //     }
//    //     else {
//    //         return (1.f - phase) / 0.5f;
//    //     }
//    // }
//
//     IDelayTimeSupportor()
//         :m_attack(0.001f), m_beginDelay(0.f), m_currentTime(0.f),
//         m_delay(0.001f), m_endDelay(0.f), m_envState(Init),
//         m_generator(std::bind(&IDelayTimeSupportor::LFOgen, this, std::placeholders::_1, std::placeholders::_2)), m_hold(0.f),
//         m_lfoFromLastPlace(true), m_lfoPhase(0.f), m_noteOn(false),
//         m_rate(0.f), m_release(0.001f), m_sampleRate(48000.f),
//         m_sustain(0.f), m_type(LFO), m_ignoreNote(true), m_lfoWave(&tri)
//     {
//         m_stereoPhase = 0.f;
//     }
//
//    virtual void getDelayTimes(float& ltime, float& rtime)
//    {
//        /*m_stereoPhase = phase;
//
//        float baseDelay = m_beginDelay.getNextValue();
//        float range = m_endDelay.getNextValue() - m_beginDelay.getNextValue();
//
//        float lp = 0.f, rp = 0.f;
//
//        m_generator(std::ref(lp), std::ref(rp));
//
//        ltime = baseDelay + lp * range;
//        rtime = baseDelay + fmodf(lp + phase + 1.f, 1.f) * range;*/
//    }
//
//    //==============================================================================
//   virtual  void noteOn()
//    {
//        switch (m_type)
//        {
//        case IDelayTimeSupportor::Static:
//            break;
//        case IDelayTimeSupportor::LFO:
//            if (m_ignoreNote)
//                break;
//
//            if (!m_lfoFromLastPlace) {
//                m_lfoPhase = 0.f;
//            }
//
//            break;
//        case IDelayTimeSupportor::Envelop:
//            m_envState = Attack;
//            m_currentTime = 0.f;
//
//            break;
//        }
//
//        m_noteOn = true;
//    }
//
//    virtual void noteOff()
//    {
//        switch (m_type)
//        {
//        case IDelayTimeSupportor::Static:
//            break;
//        case IDelayTimeSupportor::LFO:
//            if (m_ignoreNote)
//                break;
//
//            if (!m_lfoFromLastPlace) {
//                m_lfoPhase = 0.f;
//            }
//
//            break;
//        case IDelayTimeSupportor::Envelop:
//            m_envState = Release;
//            m_currentTime = 0.f;
//
//            break;
//        }
//
//        m_noteOn = false;
//    }
//
//    //==============================================================================
//    void setGeneratorType(Type type)
//    {
//        switch (type)
//        {
//        case IDelayTimeSupportor::Static:
//            m_generator = std::bind(&IDelayTimeSupportor::Staticgen, this, std::placeholders::_1, std::placeholders::_2);
//            break;
//        case IDelayTimeSupportor::LFO:
//            m_generator = std::bind(&IDelayTimeSupportor::LFOgen, this, std::placeholders::_1, std::placeholders::_2);
//            break;
//        case IDelayTimeSupportor::Envelop:
//            m_generator = std::bind(&IDelayTimeSupportor::Envgen, this, std::placeholders::_1, std::placeholders::_2);
//            break;
//        }
//    }
//
//private:
//    //==============================================================================
//    //void LFOgen(float& l,float& r)// should be 0~1
//    //{
//    //    if (!m_ignoreNote)
//    //        if (!m_noteOn){}
//    //            
//
//    //    float varL = m_lfoPhase;
//    //    float varR = m_lfoPhase + m_stereoPhase;
//
//    //    m_lfoPhase += m_rate.getNextValue() / m_sampleRate;
//
//    //    while (m_lfoPhase > 1.f)
//    //        m_lfoPhase -= 1.f;
//    //    while (m_lfoPhase < 0.f)
//    //        m_lfoPhase += 1.f;
//
//    //    while (varR > 1.f)
//    //        varR -= 1.f;
//    //    while (varR < 0.f)
//    //        varR += 1.f;
//
//    //    l = m_lfoWave(varL);
//    //    r = m_lfoWave(varR);
//    //}
//
//    //==============================================================================
//    void Envgen(float& l,float& r)
//    {
//        float var = 0.f;
//        switch (m_envState)
//        {
//
//        case IDelayTimeSupportor::Init:
//
//            break;
//        case IDelayTimeSupportor::Attack:
//            var = m_currentTime / m_attack.getNextValue();
//
//            break;
//        case IDelayTimeSupportor::Hold:
//            var = 1.f;
//
//            break;
//        case IDelayTimeSupportor::Delay:
//            m_currentTime -= (m_attack.getNextValue() + m_hold.getNextValue());
//            var = 1.f - m_currentTime / m_delay.getNextValue() * (1.f - m_sustain.getNextValue());
//
//            break;
//        case IDelayTimeSupportor::Sustain:
//            var = m_sustain.getNextValue();
//
//            break;
//        case IDelayTimeSupportor::Release:
//            var = (1.f - m_currentTime / m_release.getNextValue()) * m_sustain.getNextValue();
//
//            break;
//        }
//        updateEnvTime();
//    }
//
//    void updateEnvTime()
//    {
//        switch (m_envState)
//        {
//        case IDelayTimeSupportor::Init:
//            m_currentTime = 0.f;
//            return;
//
//        case IDelayTimeSupportor::Attack:
//            m_currentTime += 1.f / m_sampleRate;
//            if (m_currentTime > m_attack.getNextValue())
//                m_envState = Hold;
//
//            break;
//        case IDelayTimeSupportor::Hold:
//            m_currentTime += 1.f / m_sampleRate;
//            if (m_currentTime > m_attack.getNextValue() + m_hold.getNextValue())
//                m_envState = Delay;
//
//            break;
//        case IDelayTimeSupportor::Delay:
//            m_currentTime += 1.f / m_sampleRate;
//            if (m_currentTime > m_attack.getNextValue() + m_hold.getNextValue() + m_delay.getNextValue())
//                m_envState = Sustain;
//
//            break;
//        case IDelayTimeSupportor::Sustain:
//            m_currentTime = 0.f;
//            return;
//
//        case IDelayTimeSupportor::Release:
//            m_currentTime += 1.f / m_sampleRate;
//            if (m_currentTime > m_release.getNextValue())
//                m_envState = Init;
//
//            break;
//        }
//    }
//
//    //==============================================================================
//    void Staticgen(float& l,float& r)
//    {
//        float var = m_beginDelay.getNextValue();
//        l = var;
//        r = var;
//    }
//
//    //==============================================================================
//private:
//    //// lfo need
//    //bool m_ignoreNote;
//    //bool m_lfoFromLastPlace;
//    //float m_lfoPhase;
//    //float m_stereoPhase;
//    //juce::SmoothedValue<float> m_rate;
//    //std::function<float(float)> m_lfoWave;
//
//    // env need
//    enum EnvState
//    {
//        Init,
//        Attack,
//        Hold,
//        Delay,
//        Sustain,
//        Release
//    }m_envState;
//    juce::SmoothedValue<float> m_attack;
//    juce::SmoothedValue<float> m_hold;
//    juce::SmoothedValue<float> m_delay;
//    juce::SmoothedValue<float> m_sustain;
//    juce::SmoothedValue<float> m_release;
//    float m_currentTime;
//
//protected:
//    // other param
//    float m_sampleRate;
//    juce::SmoothedValue<float> m_beginDelay;
//    juce::SmoothedValue<float> m_endDelay;
//
//    // which generator
//    Type m_type;
//
//    // note on note off
//    bool m_noteOn;
//
//    std::function<void(float&,float&)> m_generator;
public:
    virtual void getDelayTimes(std::vector<float>& left, std::vector<float>& right) = 0;
    virtual void noteOn() = 0;
    virtual void noteOff() = 0;

    virtual void prepare(float fs, int frameExcept) = 0;

    void setBeginDelay(float newTimeMS) {
        m_beginDelay.setTargetValue(newTimeMS);
    }

    float getBeginDelay() const {
        return m_beginDelay.getCurrentValue();
    }

    void setEndDelay(float newTimeMS) {
        m_endDelay.setTargetValue(newTimeMS);
    }

    float getEndDelay() const {
        return m_endDelay.getCurrentValue();
    }

protected:
    float m_sampleRate = 48000.f;
    juce::SmoothedValue<float> m_beginDelay;
    juce::SmoothedValue<float> m_endDelay;
    bool m_noteOn;
};
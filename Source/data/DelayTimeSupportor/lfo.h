/*
  ==============================================================================

    lfo.h
    Created: 12 Nov 2022 9:03:05pm
    Author:  mana

  ==============================================================================
*/

#pragma once
#include "IDelayTimeSupportor.h"
#include "waveTable.h"

namespace DTSupportor {
    class lfoSupportor : public IDelayTimeSupportor {

    public:
        lfoSupportor()
            :m_ignoreNote(false),
            m_lfoFromLastPlace(true),
            m_lfoLPhase(0.f)/*, m_lfoRPhase(0.f)*/,
            /*m_lastStereoPhase(0.f),*/ m_stereoPhase(0.f),
            m_rate(0.f)/*, m_lfoWave(&lfoSupportor::tri)*/ {}

        //enum WaveType
        //{
        //    Sine,
        //    Saw,
        //    Tri,
        //    Random,
        //};

        //static float sine(float phase)
        //{
        //    return std::sinf(phase * juce::MathConstants<float>::pi);
        //}

        //static float ramp(float phase)
        //{
        //    return phase;
        //}

        //static float tri(float phase)
        //{
        //    if (phase < 0.5f) {
        //        return phase / 0.5f;
        //    }
        //    else {
        //        return (1.f - phase) / 0.5f;
        //    }
        //}

        //static float random(float phase)
        //{
        //    return rand() / (float)INT16_MAX;
        //}

        WaveTable tableTest;
        //==============================================================================
        void getDelayTimes(std::vector<float>& left, std::vector<float>& right) override {
            int frame = (int)left.size();

            /*for (int i = 0; i < frame; ++i) {
                float begin = m_beginDelay.getNextValue();
                float end = m_endDelay.getNextValue();
                float range = end - begin;

                float rphase = fmodf(m_lfoLPhase + m_stereoPhase.getNextValue() + 1.f, 1.f);

                left[i] = m_lfoWave(m_lfoLPhase) * range + begin;
                right[i] = m_lfoWave(rphase) * range + begin;

                if (!m_ignoreNote && !m_noteOn) {
                }
                else {
                    updatePhase();
                }
            }*/

            for (int i = 0; i < frame; ++i) {
                m_rphase[i] = fmodf(m_lfoLPhase + m_stereoPhase.getNextValue() + 1.f, 1.f);
                m_lphase[i] = m_lfoLPhase;

                if (!m_ignoreNote && !m_noteOn) {
                }
                else {
                    updatePhase();
                }
            }

            tableTest.getNextBlock(m_lphase, left);
            tableTest.getNextBlock(m_rphase, right);

            for (int i = 0; i < frame; ++i) {
                float begin = m_beginDelay.getNextValue();
                float end = m_endDelay.getNextValue();
                float range = end - begin;

                left[i] = (left[i] + 1.f) * 0.5f * range + begin;
                right[i] = (right[i] + 1.f) * 0.5f * range + begin;
            }
        }

        void prepare(float fs, int frameExcept) override {
            m_sampleRate = fs;

            m_lphase.resize(frameExcept);
            m_rphase.resize(frameExcept);
        }

        void noteOn() override {
            m_noteOn = true;

            if (!m_ignoreNote) {
                if (!m_lfoFromLastPlace) {
                    m_lfoLPhase = 0.f;
                    //m_lfoRPhase = m_stereoPhase;
                }
            }
        }

        void noteOff() override {
            m_noteOn = false;
        }

        //void setLFOWave(WaveType wave) {
        //    switch (wave) {
        //    case DTSupportor::lfoSupportor::Sine:
        //        m_lfoWave = std::move(&lfoSupportor::sine);
        //        break;
        //    case DTSupportor::lfoSupportor::Saw:
        //        m_lfoWave = std::move(&lfoSupportor::ramp);
        //        break;
        //    case DTSupportor::lfoSupportor::Tri:
        //        m_lfoWave = std::move(&lfoSupportor::tri);
        //        break;
        //    case DTSupportor::lfoSupportor::Random:
        //        m_lfoWave = std::move(&lfoSupportor::random);
        //        break;
        //    default:
        //        jassertfalse;
        //        break;
        //    }
        //}

        //==============================================================================
        void setBPMRate(float val) {
            m_syncBPM = val;
            setRate(m_bpm / 60.f / m_syncBPM);
        }

        void setBPM(float bpm) {
            m_bpm = bpm;
            setRate(m_bpm / 60.f / m_syncBPM);
        }

        float getSyncBPM() const {
            return m_syncBPM;
        }

        void setRate(float newRate) {
            m_rate.setTargetValue(newRate);
        }

        float getRate()const {
            return m_rate.getTargetValue();
        }

        void setPhase(float p) {
            m_stereoPhase.setTargetValue(p);
        }

        float getPhase() const {
            return m_stereoPhase.getTargetValue();
        }
             
        //==============================================================================
    private:
        void updatePhase() {
            m_lfoLPhase += m_rate.getNextValue() / m_sampleRate;
            //m_lfoRPhase += m_rate.getNextValue() / m_sampleRate;
            while (m_lfoLPhase < 0.f)
                m_lfoLPhase += 1.f;
            while (m_lfoLPhase > 1.f)
                m_lfoLPhase -= 1.f;
        }

        bool m_ignoreNote; /* 振荡器永远振荡如果为true */
        bool m_lfoFromLastPlace;/* 触发midi时从上次的相位位置启动 */

        float m_lfoLPhase;/* 振荡器相位 */
        //float m_lfoRPhase;/* 右振荡器相位 */

        juce::SmoothedValue<float> m_stereoPhase;/* 相位 */
        //float m_lastStereoPhase;

        juce::SmoothedValue<float> m_rate;
        //std::function<float(float)> m_lfoWave;/* 0.f->1.f */

        std::vector<float> m_lphase;
        std::vector<float> m_rphase;

        float m_bpm = 0.f;
        float m_syncBPM = 0.f;
    };
}
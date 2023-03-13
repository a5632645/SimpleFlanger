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
			m_lfoLPhase(0.f),
			m_stereoPhase(0.f),
			m_rate(0.f) {}

		WaveTable tableTest;
		//==============================================================================

		void getDelayTimes(std::vector<float>& left, std::vector<float>& right) override {
			int frame = (int)left.size();

			for (int i = 0; i < frame; ++i) {
				m_rphase[i] = fmodf(m_lfoLPhase + m_stereoPhase.getNextValue() + 1.f, 1.f);
				m_lphase[i] = m_lfoLPhase;

				if (!m_ignoreNote && !m_noteOn) {
				}
				else {
					updatePhase();
				}
			}

			tableTest.getNextBlock(m_jitter, m_wtPos, m_lphase, left);
			tableTest.getNextBlock(m_jitter, m_wtPos, m_rphase, right);

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
				}
			}
		}

		void noteOff() override {
			m_noteOn = false;
		}

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

		void updatePhase() {
			m_lfoLPhase += m_rate.getNextValue() / m_sampleRate;
			while (m_lfoLPhase > 1.f)
				m_lfoLPhase -= 1.f;
		}

		bool m_ignoreNote; /* Õñµ´Æ÷ÓÀÔ¶Õñµ´Èç¹ûÎªtrue */
		bool m_lfoFromLastPlace;/* ´¥·¢midiÊ±´ÓÉÏ´ÎµÄÏàÎ»Î»ÖÃÆô¶¯ */
		float m_lfoLPhase;/* Õñµ´Æ÷ÏàÎ» */
		juce::SmoothedValue<float> m_stereoPhase;/* ÏàÎ» */
		juce::SmoothedValue<float> m_rate;
		std::vector<float> m_lphase;
		std::vector<float> m_rphase;
		float m_jitter = 0.f;
		float m_wtPos = 0.f;
		float m_bpm = 0.f;
		float m_syncBPM = 0.f;
	};
}
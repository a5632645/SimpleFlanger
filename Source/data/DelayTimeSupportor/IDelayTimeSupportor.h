/*
  ==============================================================================

    IDelayTimeSupportor.h
    Created: 30 Oct 2022 10:02:37am
    Author:  mana

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class IDelayTimeSupportor {
 public:
  virtual ~IDelayTimeSupportor() = default;
  virtual void getDelayTimes(std::vector<float>& left,
                             std::vector<float>& right) = 0;
  virtual void noteOn() = 0;
  virtual void noteOff() = 0;

  virtual void prepare(float fs, int frameExcept) = 0;

  void setBeginDelay(float newTimeMS) {
    m_beginDelay.setTargetValue(newTimeMS);
  }

  float getBeginDelay() const { return m_beginDelay.getCurrentValue(); }

  void setEndDelay(float newTimeMS) { m_endDelay.setTargetValue(newTimeMS); }

  float getEndDelay() const { return m_endDelay.getCurrentValue(); }

 protected:
  float m_sampleRate = 48000.f;
  juce::SmoothedValue<float> m_beginDelay;
  juce::SmoothedValue<float> m_endDelay;
  bool m_noteOn;
};
/*
  ==============================================================================

    MonoFlanger.h
    Created: 30 Oct 2022 9:01:21pm
    Author:  mana

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MonoDelayLine {
 public:
  static constexpr float kMaxDelayTime = 20.f;

  void prepare(float fs, int /*frameExpected*/) {
    m_sampleRate = fs;
    m_sampleRateDiv1000 = fs / 1000.f;

    auto size = (unsigned int)std::ceil(fs * kMaxDelayTime / 1000.f);
    size = makePOW2(size);
    m_mask = size - 1;

    m_delayBuffer.resize(size);
  }

  void pushSample(float in) {
    m_delayBuffer[m_wpos] = in;
    ++m_wpos;
    m_wpos &= m_mask;
  }

  float popSample(float delayInMs) {

      m_currentDelayTime = delayInMs >kMaxDelayTime?kMaxDelayTime : delayInMs;
      float delayInSample = m_currentDelayTime * m_sampleRateDiv1000;
      float fractor = delayInSample - std::floor(delayInSample);
      int rpos_next = m_wpos - static_cast<int>(delayInSample);
      int rpos = rpos_next - 1;
      rpos &= m_mask;
      rpos_next &= m_mask;

      float rsample = m_delayBuffer[rpos];
      float rsample_next = m_delayBuffer[rpos_next];

      return rsample + (rsample_next - rsample) * fractor;
  }

  float getDelayTime() const {return m_currentDelayTime;}

 private:
 static unsigned int makePOW2(unsigned int size) {
     --size;
     size |= size >> 1;
     size |= size >> 2;
     size |= size >> 4;
     size |= size >> 8;
     size |= size >> 16;
     ++size;
     return size;
 }

  float m_sampleRate = 48000.f;
  float m_sampleRateDiv1000 = 48.f;
  float m_currentDelayTime = 0.f;
  int m_wpos = 0;
  int m_mask = 0;

  std::vector<float> m_delayBuffer;
};
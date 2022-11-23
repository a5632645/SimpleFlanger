/*
  ==============================================================================

    waveTable.h
    Created: 18 Nov 2022 11:14:45am
    Author:  mana

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class WaveTable {
public:
    WaveTable()
        :m_formatMgr(new juce::AudioFormatManager),
        m_sampleBegin(0.f), m_sampleEnd(1.f)
    {
        initPreset();

        m_sample = &m_sine;

        m_formatMgr->registerBasicFormats();
    }

    void loadNewSample(juce::File file)
    {
        juce::ScopedLock lock(m_locker);

        auto* reader = m_formatMgr->createReaderFor(file);
        if (reader == nullptr) {
            return;
        }

        m_wavfile.setSize(1, reader->lengthInSamples);
        reader->read(&m_wavfile, 0, reader->lengthInSamples, 0, true, false);

        delete reader;
    }

    void loadPreset(const juce::String& name) {
        juce::ScopedLock lock(m_locker);

        if (name == "sine") {
            m_sample = &m_sine;
        }
        else if (name == "triangle") {
            m_sample = &m_tri;
        }
        else if (name == "sawtooth") {
            m_sample = &m_saw;
        }
        else if (name == "pulse") {
            m_sample = &m_pluse;
        }
        else if (name == "loopedNoise") {
            m_sample = &m_noise;
        }
        else if (name == "from file") {
            m_sample = &m_wavfile;
        }
    }

    void getNextBlock(const std::vector<float>& indexs, std::vector<float>& buffer)
    {
        juce::ScopedLock lock(m_locker);


        auto size = indexs.size();
        const float* data = m_sample->getReadPointer(0);
        const int length = m_sample->getNumSamples();

        for (size_t i = 0; i < size; ++i)
        {
            float sampleBegin = m_sampleBegin.getCurrentValue() * length;
            float sampleEnd = m_sampleEnd.getCurrentValue() * length;
            float range = sampleEnd - sampleBegin;

            float index = indexs[i] * range + sampleBegin;
            int before = (int)floor(index);
            if (before >= length)
                before -= (int)sampleBegin;

            int next = before + 1;
            if (next >= length)
                next -= (int)sampleEnd;
            float inter = index - (float)before;

            buffer[i] = data[before] + inter * (data[next] - data[before]);
        }
    }

    int getSampleLength() const {
        return m_sample->getNumSamples();
    }
private:
    static constexpr int kPresetSize = 2048;

    void initPreset() {
        m_sine.setSize(1, kPresetSize);
        m_tri.setSize(1, kPresetSize);
        m_saw.setSize(1, kPresetSize);
        m_noise.setSize(1, kPresetSize);
        m_pluse.setSize(1, kPresetSize);

        float* ptr = m_sine.getWritePointer(0);
        for (int i = 0; i < kPresetSize; ++i) {
            ptr[i] = sinf(i / static_cast<float>(kPresetSize) * juce::MathConstants<float>::twoPi);
        }

        ptr = m_tri.getWritePointer(0);
        for (int i = 0; i < kPresetSize; ++i) {
            ptr[i] = (acosf(sinf(i / static_cast<float>(kPresetSize) * juce::MathConstants<float>::twoPi)) / juce::MathConstants<float>::pi - 0.5f) * 2.f;
        }

        ptr = m_saw.getWritePointer(0);
        for (int i = 0; i < kPresetSize; ++i) {
            ptr[i] = (i / static_cast<float>(kPresetSize) - 0.5f) * 2.f;
        }

        ptr = m_noise.getWritePointer(0);
        for (int i = 0; i < kPresetSize; ++i) {
            ptr[i] = (rand() / float(INT16_MAX) - 0.5f) * 2.f;
        }

        ptr = m_pluse.getWritePointer(0);
        const float* rptr = m_sine.getReadPointer(0);
        for (int i = 0; i < kPresetSize; ++i) {
            ptr[i] = rptr[i] > 0.0f ? 1.0f : -1.0f;
        }

        m_wavfile = m_sine;
    }

    juce::AudioBuffer<float>* m_sample;
    juce::CriticalSection m_locker;

    std::unique_ptr<juce::AudioFormatManager> m_formatMgr;

    juce::AudioBuffer<float> m_sine, m_tri, m_saw, m_noise, m_pluse, m_wavfile;
public:
    juce::SmoothedValue<float> m_sampleBegin, m_sampleEnd;
};
/*
  ==============================================================================

    WaveViewer.h
    Created: 15 Nov 2022 8:37:36pm
    Author:  mana

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "..\data\DelayTimeSupportor\waveTable.h"

//==============================================================================
/*
*/

class WaveViewer  : public juce::Component
{
public:
    WaveViewer(WaveTable& table);
    ~WaveViewer() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    WaveTable& m_table;
    juce::TextButton m_buttonLoadWav;
    juce::FileChooser m_chooser;
    juce::ComboBox m_comboBoxWavType;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveViewer)
};

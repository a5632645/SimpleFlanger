/*
  ==============================================================================

    WaveViewer.h
    Created: 15 Nov 2022 8:37:36pm
    Author:  mana

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../data/DelayTimeSupportor/lfo.h"

//==============================================================================
/*
*/

class WaveViewer  : public juce::Component
{
public:
    explicit WaveViewer(DTSupportor::lfoSupportor& lfo);
    ~WaveViewer() override = default;

    void paint (juce::Graphics&) override;

private:
    DTSupportor::lfoSupportor& m_table;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveViewer)
};

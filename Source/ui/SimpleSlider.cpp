/*
  ==============================================================================

    SimpleSlider.cpp
    Created: 30 Oct 2022 10:05:47am
    Author:  mana

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SimpleSlider.h"

//==============================================================================
SimpleSlider::SimpleSlider()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    m_laf = std::make_unique<simpleSlider::simpleLookAndFeel>();

    setLookAndFeel(m_laf.get());
}

SimpleSlider::~SimpleSlider()
{
    setLookAndFeel(nullptr);

    m_laf = nullptr;
}

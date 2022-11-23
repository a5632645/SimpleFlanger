/*
  ==============================================================================

    SimpleSlider.h
    Created: 30 Oct 2022 10:05:47am
    Author:  mana

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/

namespace simpleSlider {
    class simpleLookAndFeel : public juce::LookAndFeel_V4
    {
    public:
        simpleLookAndFeel()
            :juce::LookAndFeel_V4()
        {
        }

        ~simpleLookAndFeel()
        {
        }

        void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
            float sliderPos, float minSliderPos, float maxSliderPos,
            const juce::Slider::SliderStyle style , juce::Slider& s) override
        {
            auto centerPos = y + height / 2.f;
            g.setColour(juce::Colours::white);
            g.drawHorizontalLine((int)centerPos, x, x + width);

            auto trueWidth = width - kSliderWidth;
            auto trueSliderPos = sliderPos * trueWidth / width;

            juce::Rectangle<float> sliderBlock{ trueSliderPos, (float)y, kSliderWidth, (float)height };
            g.setColour(juce::Colours::black);
            g.drawRect(sliderBlock, 1.f);

            g.setColour(juce::Colours::grey);
            sliderBlock.reduce(1.f, 1.f);
            g.fillRect(sliderBlock);
        }
    private:
        static constexpr float kSliderWidth = 10.f;
    };
}

class SimpleSlider : public juce::Slider
{
public:
    SimpleSlider();
    ~SimpleSlider() override;

private:
    std::unique_ptr<simpleSlider::simpleLookAndFeel> m_laf;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleSlider)
};

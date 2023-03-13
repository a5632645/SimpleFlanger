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

namespace simpleFlanger {
	class simpleLookAndFeel : public juce::LookAndFeel_V4
	{
	public:
		void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
			const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override
		{
			auto totalSize = std::min(width, height);
			auto fontHeight = g.getCurrentFont().getHeight();
			auto centerCircleBound = juce::Rectangle<int>(x, y + fontHeight, totalSize, totalSize);
			auto textBound = juce::Rectangle<int>(x, y, totalSize, totalSize);
			centerCircleBound.reduce(totalSize / 4, totalSize / 4);
			auto arcRadius = centerCircleBound.getHeight() / 2;
			auto lineEndRadius = totalSize / 2 - 8;
			auto lineStartRadius = arcRadius + 0.1f * lineEndRadius;
			auto thinLineRadius = lineEndRadius - 0.15f * lineEndRadius;
			auto halfRotaryAngle = (rotaryEndAngle - rotaryStartAngle) / 2;
			auto centerRotaryAngle = (rotaryEndAngle + rotaryStartAngle) / 2;
			auto numOneSidethinLine = 4;
			auto thickLineThickness = 4.f;
			auto thinLineThickness = 2.f;
			auto knobLineThickness = 4.f;

			// circle framework
			g.setColour(juce::Colours::black);
			g.fillEllipse(centerCircleBound.toFloat());

			// circle
			centerCircleBound.reduce(4.f, 4.f);
			g.setColour(juce::Colours::green);
			g.fillEllipse(centerCircleBound.toFloat());

			// a line from center to framework
			auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
			juce::Point<float> lineEndPoint(centerCircleBound.getCentreX() + arcRadius * std::cos(toAngle - juce::MathConstants<float>::halfPi),
				centerCircleBound.getCentreY() + arcRadius * std::sin(toAngle - juce::MathConstants<float>::halfPi));
			g.setColour(juce::Colours::black);
			g.drawLine(juce::Line<float>(centerCircleBound.getCentre().toFloat(), lineEndPoint), knobLineThickness);

			g.setColour(juce::Colours::lightgrey);
			// thick lines: start,center,end
			auto centerPoint = centerCircleBound.getCentre();
			g.drawLine(juce::Line<float>(
				centerPoint.x + lineEndRadius * std::cos(rotaryStartAngle - juce::MathConstants<float>::halfPi),
				centerPoint.y + lineEndRadius * std::sin(rotaryStartAngle - juce::MathConstants<float>::halfPi),
				centerPoint.x + lineStartRadius * std::cos(rotaryStartAngle - juce::MathConstants<float>::halfPi),
				centerPoint.y + lineStartRadius * std::sin(rotaryStartAngle - juce::MathConstants<float>::halfPi)),
				thickLineThickness);
			g.drawLine(juce::Line<float>(
				centerPoint.x + lineEndRadius * std::cos(centerRotaryAngle - juce::MathConstants<float>::halfPi),
				centerPoint.y + lineEndRadius * std::sin(centerRotaryAngle - juce::MathConstants<float>::halfPi),
				centerPoint.x + lineStartRadius * std::cos(centerRotaryAngle - juce::MathConstants<float>::halfPi),
				centerPoint.y + lineStartRadius * std::sin(centerRotaryAngle - juce::MathConstants<float>::halfPi)),
				thickLineThickness);
			g.drawLine(juce::Line<float>(
				centerPoint.x + lineEndRadius * std::cos(rotaryEndAngle - juce::MathConstants<float>::halfPi),
				centerPoint.y + lineEndRadius * std::sin(rotaryEndAngle - juce::MathConstants<float>::halfPi),
				centerPoint.x + lineStartRadius * std::cos(rotaryEndAngle - juce::MathConstants<float>::halfPi),
				centerPoint.y + lineStartRadius * std::sin(rotaryEndAngle - juce::MathConstants<float>::halfPi)),
				thickLineThickness);

			// thin lines between thick lines
			auto increaseAngle = halfRotaryAngle / (numOneSidethinLine + 1);
			auto angle = rotaryStartAngle + increaseAngle;
			for (int i = 0;
				i < numOneSidethinLine;
				angle += increaseAngle, i++) {
				g.drawLine(juce::Line<float>(
					centerPoint.x + thinLineRadius * std::cos(angle - juce::MathConstants<float>::halfPi),
					centerPoint.y + thinLineRadius * std::sin(angle - juce::MathConstants<float>::halfPi),
					centerPoint.x + lineStartRadius * std::cos(angle - juce::MathConstants<float>::halfPi),
					centerPoint.y + lineStartRadius * std::sin(angle - juce::MathConstants<float>::halfPi)),
					thinLineThickness);
			}

			angle = rotaryEndAngle - increaseAngle;
			for (int i = 0;
				i < numOneSidethinLine;
				angle -= increaseAngle, i++) {
				g.drawLine(juce::Line<float>(
					centerPoint.x + thinLineRadius * std::cos(angle - juce::MathConstants<float>::halfPi),
					centerPoint.y + thinLineRadius * std::sin(angle - juce::MathConstants<float>::halfPi),
					centerPoint.x + lineStartRadius * std::cos(angle - juce::MathConstants<float>::halfPi),
					centerPoint.y + lineStartRadius * std::sin(angle - juce::MathConstants<float>::halfPi)),
					thinLineThickness);
			}

			// some texts
			g.drawText(juce::String(slider.getMinimum()), textBound, juce::Justification::bottomLeft);
			g.drawText(juce::String(slider.getMaximum()), textBound, juce::Justification::bottomRight);
			g.drawText(slider.getName(), textBound, juce::Justification::centredTop);
		}
	};

	class Knob : public juce::Slider, public juce::SliderParameterAttachment
	{
	public:
		Knob(juce::RangedAudioParameter* p);
		~Knob() override;

	private:
		std::unique_ptr<simpleLookAndFeel> m_laf;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Knob)
	};
}

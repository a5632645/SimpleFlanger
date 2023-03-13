/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleFlangerAudioProcessorEditor::SimpleFlangerAudioProcessorEditor(SimpleFlangerAudioProcessor& p)
	: AudioProcessorEditor(&p), audioProcessor(p),
	m_phaseViewer(std::bind(&MonoDelayLine::getDelayTime, &audioProcessor.simpleFlangerTest.m_left),
		std::bind(&MonoDelayLine::getDelayTime, &audioProcessor.simpleFlangerTest.m_right)),
	m_waveViewer(audioProcessor.simpleFlangerTest.m_lfo),
	m_beginDelay(audioProcessor.paramBeginDelay),
	m_endDelay(audioProcessor.paramEndDelay),
	m_feedback(audioProcessor.paramFeedback),
	m_lfoRate(audioProcessor.paramLfoRate),
	m_drywet(audioProcessor.paramDryWet),
	m_rawMix(audioProcessor.paramRawMix),
	m_processedMix(audioProcessor.paramProcessedMix),
	m_widePhase(audioProcessor.paramWidePhase),
	m_waveTablePos(audioProcessor.paramWaveTablePos),
	m_numNoiseGen(audioProcessor.paramNumNoiseGen),
	m_noiseJitter(audioProcessor.paramNoiseJitter),
	m_feedbackDamp(audioProcessor.paramFeedbackCutoff)
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(700, 400);

	addAndMakeVisible(m_phaseViewer);
	m_phaseViewer.setMaxPhase(MonoDelayLine::kMaxDelayTime);

	addAndMakeVisible(m_waveViewer);

	addAndMakeVisible(m_beginDelay);
	m_beginDelay.setName("BeginDelay");
	addAndMakeVisible(m_drywet);
	m_drywet.setName("DryWet");
	addAndMakeVisible(m_endDelay);
	m_endDelay.setName("EndDelay");
	addAndMakeVisible(m_feedback);
	m_feedback.setName("Feedback");
	addAndMakeVisible(m_lfoRate);
	m_lfoRate.setName("LFO Rate");
	addAndMakeVisible(m_processedMix);
	m_processedMix.setName("ProcessedMix");
	addAndMakeVisible(m_rawMix);
	m_rawMix.setName("UnProcMix");
	addAndMakeVisible(m_widePhase);
	m_widePhase.setName("LR Phase");
	addAndMakeVisible(m_waveTablePos);
	m_waveTablePos.setName("LFO Shape");
	m_waveTablePos.onValueChange = [this]() { m_waveViewer.repaint(); };
	addAndMakeVisible(m_numNoiseGen);
	m_numNoiseGen.setName("Num Noise Point");
	m_numNoiseGen.onValueChange = [this]() { m_waveViewer.repaint(); };
	addAndMakeVisible(m_noiseJitter);
	m_noiseJitter.setName("Noise Jitter");
	m_noiseJitter.onValueChange = [this]() { m_waveViewer.repaint(); };
	addAndMakeVisible(m_feedbackDamp);
	m_feedbackDamp.setName("Damp");
}

//==============================================================================
void SimpleFlangerAudioProcessorEditor::paint(juce::Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.setColour(juce::Colour(50, 62, 68));
	g.fillAll();
}

void SimpleFlangerAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..
	m_phaseViewer.setBounds(0, 0, getWidth(), 40);

	m_beginDelay.setBounds(0, 40, 100, 100);
	m_endDelay.setBounds(0, 150, 100, 100);

	m_rawMix.setBounds(120, 40, 100, 100);
	m_processedMix.setBounds(120, 150, 100, 100);

	m_drywet.setBounds(240, 40, 100, 100);
	m_feedback.setBounds(240, 150, 100, 100);

	m_lfoRate.setBounds(360, 40, 100, 100);
	m_widePhase.setBounds(360, 150, 100, 100);

	m_waveTablePos.setBounds(480, 40, 100, 100);
	m_numNoiseGen.setBounds(480, 150, 100, 100);

	m_noiseJitter.setBounds(600, 40, 100, 100);
	m_feedbackDamp.setBounds(600, 150, 100, 100);

	m_waveViewer.setBounds(0, 250, getWidth(), 150);
}
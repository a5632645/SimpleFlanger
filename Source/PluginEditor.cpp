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
    m_viewer(std::bind(&MonoFlanger::getDelayTime, &audioProcessor.simpleFlangerTest.m_left),
        std::bind(&MonoFlanger::getDelayTime, &audioProcessor.simpleFlangerTest.m_right)),
    m_waveViewer(audioProcessor.simpleFlangerTest.m_lfo.tableTest)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(500, 600);

    addAndMakeVisible(m_beginDelaySlider); 
    m_beginDelaySlider.addListener(this);
    m_beginDelaySlider.setRange(0.f, MonoFlanger::kMaxDelayTime, 0.01f);
    m_beginDelaySlider.setValue(audioProcessor.simpleFlangerTest.m_Supportor->getBeginDelay(), juce::dontSendNotification);
    m_beginDelaySlider.setTextValueSuffix(" ms");
    m_beginDelaySlider.setSkewFactor(0.5f);

    addAndMakeVisible(m_endDelaySlider); 
    m_endDelaySlider.addListener(this);
    m_endDelaySlider.setRange(0.f, MonoFlanger::kMaxDelayTime, 0.01f);
    m_endDelaySlider.setValue(audioProcessor.simpleFlangerTest.m_Supportor->getEndDelay(), juce::dontSendNotification);
    m_endDelaySlider.setTextValueSuffix(" ms");
    m_endDelaySlider.setSkewFactor(0.5f);

    addAndMakeVisible(m_mixSlider);
    m_mixSlider.addListener(this);
    m_mixSlider.setRange(-100.f, 100.f, 0.01f);
    m_mixSlider.setValue(audioProcessor.simpleFlangerTest.m_mix.getTargetValue()*100.f, juce::dontSendNotification);
    m_mixSlider.setTextValueSuffix(" %");

    addAndMakeVisible(m_DelayMixSlider);
    m_DelayMixSlider.addListener(this);
    m_DelayMixSlider.setRange(-100.f, 100.f, 0.01f);
    m_DelayMixSlider.setValue(audioProcessor.simpleFlangerTest.m_DelayMix.getTargetValue() * 100.f, juce::dontSendNotification);
    m_DelayMixSlider.setTextValueSuffix(" %");

    addAndMakeVisible(m_feedbackSlider);
    m_feedbackSlider.addListener(this);
    m_feedbackSlider.setRange(-100.f, 100.f, 0.01f);
    m_feedbackSlider.setValue(audioProcessor.simpleFlangerTest.m_feedback.getTargetValue()*100.f, juce::dontSendNotification);
    m_feedbackSlider.setTextValueSuffix(" %");

    addAndMakeVisible(m_lfoRateSlider);
    m_lfoRateSlider.addListener(this);
    m_lfoRateSlider.setRange(0.f, 10.f, 0.001f);
    m_lfoRateSlider.setValue(audioProcessor.simpleFlangerTest.m_lfo.getRate(), juce::dontSendNotification);
    m_lfoRateSlider.setTextValueSuffix(" Hz");
    m_lfoRateSlider.setSkewFactor(0.5f);

    addAndMakeVisible(m_phaseSlider);
    m_phaseSlider.addListener(this);
    m_phaseSlider.setRange(0.f, 360.f, 0.01f);
    m_phaseSlider.setValue(audioProcessor.simpleFlangerTest.m_lfo.getPhase()*360.f, juce::dontSendNotification);

    addAndMakeVisible(m_dryWetSlider);
    m_dryWetSlider.addListener(this);
    m_dryWetSlider.setRange(0.f, 100.f, 0.01f);
    m_dryWetSlider.setValue(audioProcessor.simpleFlangerTest.m_wet.getTargetValue()*100.f);
    m_dryWetSlider.setTextValueSuffix(" %");

    addAndMakeVisible(m_viewer);
    addAndMakeVisible(m_waveViewer);

    addAndMakeVisible(m_sampleBeginSlider);
    m_sampleBeginSlider.addListener(this);
    m_sampleBeginSlider.setRange(0.f, 1.f, 0.0001f);
    m_sampleBeginSlider.setValue(audioProcessor.simpleFlangerTest.m_lfo.tableTest.m_sampleBegin.getTargetValue(), juce::dontSendNotification);

    addAndMakeVisible(m_sampleEndSlider);
    m_sampleEndSlider.addListener(this);
    m_sampleEndSlider.setRange(0.f, 1.f, 0.0001f);
    m_sampleEndSlider.setValue(audioProcessor.simpleFlangerTest.m_lfo.tableTest.m_sampleEnd.getTargetValue(), juce::dontSendNotification);

    addAndMakeVisible(m_lfoSyncRateSlider);
    m_lfoSyncRateSlider.addListener(this);
    m_lfoSyncRateSlider.setRange(0.03125f, 8.f, 0.03125f);
    m_lfoSyncRateSlider.setValue(audioProcessor.simpleFlangerTest.m_lfo.getSyncBPM(), juce::dontSendNotification);

    addAndMakeVisible(m_followBPM);
    m_followBPM.onClick = [this]() {
        bool state = m_followBPM.getToggleState();
        m_lfoRateSlider.setVisible(!state);
        m_lfoSyncRateSlider.setVisible(state);
        this->sliderValueChanged(state ? &m_lfoSyncRateSlider : &m_lfoRateSlider);
        audioProcessor.isFollowBPM = state;
    };
    m_followBPM.setToggleState(audioProcessor.isFollowBPM, juce::dontSendNotification);

    bool state = m_followBPM.getToggleState();
    m_lfoRateSlider.setVisible(!state);
    m_lfoSyncRateSlider.setVisible(state);

    m_viewer.setMaxPhase(MonoFlanger::kMaxDelayTime);
}

SimpleFlangerAudioProcessorEditor::~SimpleFlangerAudioProcessorEditor()
{
}

//==============================================================================
void SimpleFlangerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.setColour(juce::Colour(50, 62, 68));
    g.fillAll();

    g.setColour(juce::Colours::white);
    g.setFont(kTextHeight);

    // sliders
    g.drawSingleLineText("begin delay", 0, m_beginDelaySlider.getBounds().getCentreY());
    g.drawSingleLineText("end   delay", 0, m_endDelaySlider.getBounds().getCentreY());

    g.drawSingleLineText("origin mix", 0, m_mixSlider.getBounds().getCentreY());
    g.drawSingleLineText("delay   mix", 0, m_DelayMixSlider.getBounds().getCentreY());

    g.drawSingleLineText("feedback", 0, m_feedbackSlider.getBounds().getCentreY());

    g.drawSingleLineText("dry wet", 0, m_dryWetSlider.getBounds().getCentreY());

    g.drawSingleLineText("LFO rate", 0, m_lfoRateSlider.getBounds().getCentreY());
    g.drawSingleLineText("SyncBPM", m_followBPM.getRight(), m_followBPM.getY());
    g.drawSingleLineText("phase", 0, m_phaseSlider.getBounds().getCentreY());

    g.drawSingleLineText("sampleBgi", 0, m_sampleBeginSlider.getBounds().getCentreY());
    g.drawSingleLineText("sampleEnd", 0, m_sampleEndSlider.getBounds().getCentreY());
}

void SimpleFlangerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    m_viewer.setBounds(0, 0, getWidth(), 40);

    // slider bounds
    juce::Rectangle<int> sliderBound(kTextSize, 50, getWidth() - kTextSize, kSliderHeight);

    m_beginDelaySlider.setBounds(sliderBound); sliderBound.translate(0, kSliderInterver);
    m_endDelaySlider.setBounds(sliderBound); sliderBound.translate(0, kSliderInterver2);

    m_mixSlider.setBounds(sliderBound); sliderBound.translate(0, kSliderInterver);
    m_DelayMixSlider.setBounds(sliderBound); sliderBound.translate(0, kSliderInterver2);

    m_feedbackSlider.setBounds(sliderBound); sliderBound.translate(0, kSliderInterver2);

    m_dryWetSlider.setBounds(sliderBound); sliderBound.translate(0, kSliderInterver2);

    auto rateBound = sliderBound;
    rateBound.removeFromRight(kToggleWidth);
    m_lfoRateSlider.setBounds(rateBound);
    m_lfoSyncRateSlider.setBounds(rateBound);
    m_followBPM.setBounds(getWidth() - kToggleWidth, sliderBound.getY(), sliderBound.getHeight(), sliderBound.getHeight());
    sliderBound.translate(0, kSliderInterver2);

    m_phaseSlider.setBounds(sliderBound); sliderBound.translate(0, kSliderInterver2);

    m_sampleBeginSlider.setBounds(sliderBound); sliderBound.translate(0, kSliderInterver);
    m_sampleEndSlider.setBounds(sliderBound); sliderBound.translate(0, kSliderInterver);

    m_waveViewer.setBounds(0, getHeight() - 100, getWidth(), 100);
}

void SimpleFlangerAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    float var = (float)slider->getValue();

    if (slider == &m_lfoRateSlider) {
        audioProcessor.simpleFlangerTest.m_lfo.setRate(var);
    }
    else if (slider == &m_beginDelaySlider) {
        audioProcessor.simpleFlangerTest.m_Supportor->setBeginDelay(var);
    }
    else if (slider == &m_endDelaySlider) {
        audioProcessor.simpleFlangerTest.m_Supportor->setEndDelay(var);
    }
    else if (slider == &m_phaseSlider) {
        audioProcessor.simpleFlangerTest.m_lfo.setPhase(var / 360.f);
    }
    else if (slider == &m_mixSlider) {
        audioProcessor.simpleFlangerTest.m_mix.setTargetValue(var / 100.f);
    }
    else if (slider == &m_feedbackSlider) {
        audioProcessor.simpleFlangerTest.m_feedback.setTargetValue(var / 100.f);
    }
    else if (slider == &m_dryWetSlider) {
        audioProcessor.simpleFlangerTest.setDryWet(var / 100.f);
    }
    else if (slider == &m_DelayMixSlider) {
        audioProcessor.simpleFlangerTest.m_DelayMix.setTargetValue(var / 100.f);
    }
    else if (slider == &m_sampleBeginSlider) {
        audioProcessor.simpleFlangerTest.m_lfo.tableTest.m_sampleBegin.setTargetValue(var);
        m_waveViewer.repaint();
    }
    else if (slider == &m_sampleEndSlider) {
        audioProcessor.simpleFlangerTest.m_lfo.tableTest.m_sampleEnd.setTargetValue(var);
        m_waveViewer.repaint();
    }
    else if (slider == &m_lfoSyncRateSlider) {
        audioProcessor.simpleFlangerTest.m_lfo.setBPMRate(var);
    }
}
/*
  ==============================================================================

    WaveViewer.cpp
    Created: 15 Nov 2022 8:37:36pm
    Author:  mana

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveViewer.h"

//==============================================================================
WaveViewer::WaveViewer(WaveTable& table)
    :m_table(table), m_buttonLoadWav("LoadWav"),
    m_chooser("select wav file", juce::File(), "*.wav")
{
    // In your constructor, you should add any child components, and
    // initialize any special settings that your component needs.
    addAndMakeVisible(m_buttonLoadWav);

    m_buttonLoadWav.onClick = [this]() {
        m_chooser.launchAsync(
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& c) {
                m_table.loadNewSample(c.getResult());
                m_comboBoxWavType.setText("from file", juce::dontSendNotification);
                m_table.loadPreset("from file");
                this->repaint();
            }
        );
    };

    addAndMakeVisible(m_comboBoxWavType);
    m_comboBoxWavType.addItem("sine", 1);
    m_comboBoxWavType.addItem("triangle", 2);
    m_comboBoxWavType.addItem("sawtooth", 3);
    m_comboBoxWavType.addItem("pulse", 4);
    m_comboBoxWavType.addItem("loopedNoise", 5);
    m_comboBoxWavType.addItem("from file", 6);

    m_comboBoxWavType.onChange = [this]() {
        m_table.loadPreset(m_comboBoxWavType.getText());
        repaint();
    };

    m_comboBoxWavType.setText("sine", juce::dontSendNotification);
}

WaveViewer::~WaveViewer()
{
}

void WaveViewer::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.setColour(juce::Colours::black);
    g.fillAll();

    const int width = getWidth();
    std::vector<float> wavePoint;
    wavePoint.resize(width);
    for (int i = 0; i < width; ++i) {
        wavePoint[i] = i / (float)width;
    }
    m_table.getNextBlock(wavePoint, wavePoint);

    const int center = getHeight() / 2;
    const int height = center - 4;
    for (float& w : wavePoint) {
        w = w * height + center;
    }
    
    juce::Path p;
    p.startNewSubPath(0, wavePoint[0]);
    for (int i = 1; i < width; ++i) {
        p.lineTo(i, wavePoint[i]);
    }

    g.setColour(juce::Colours::lightgreen);
    g.strokePath(p, juce::PathStrokeType(1.f));

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1.f);
}

void WaveViewer::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    m_buttonLoadWav.setBounds(0, 0, 60, 16);
    m_comboBoxWavType.setBounds(getWidth() - 80, 0, 80, 24);
}

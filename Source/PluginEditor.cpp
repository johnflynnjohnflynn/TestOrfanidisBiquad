/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
TestOrfanidisBiquadAudioProcessorEditor::TestOrfanidisBiquadAudioProcessorEditor (TestOrfanidisBiquadAudioProcessor& p)
    : AudioProcessorEditor (&p), 
      gainLabel_       {String::empty, "Gain in dB"}, // (No component name, just set label text)
      frequencyLabel_  {String::empty, "Frequency in pi*rad/s"},
      bandwidthLabel_  {String::empty, "Bandwidth at -3dB point in pi*rad/s"},
      gainSlider_      {*p.getParameters()[gainName]},
      frequencySlider_ {*p.getParameters()[frequencyName]},
      bandwidthSlider_ {*p.getParameters()[bandwidthName]},
      processor (p)
{
    addAndMakeVisible (gainSlider_);
    addAndMakeVisible (frequencySlider_);
    addAndMakeVisible (bandwidthSlider_);
    
    addAndMakeVisible (gainLabel_);
    addAndMakeVisible (frequencyLabel_);
    addAndMakeVisible (bandwidthLabel_);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    const int numRows = p.getNumParameters();
    const int height = numRows * 48 + 24;               // obviously named constants
    setSize (512, height);                              // would be better here!
}

TestOrfanidisBiquadAudioProcessorEditor::~TestOrfanidisBiquadAudioProcessorEditor()
{
}

//==============================================================================
void TestOrfanidisBiquadAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::lightgrey);
}

void TestOrfanidisBiquadAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    const int unit = 8;
    const int margin = 2 * unit;
    const int offsetAdd = 4 * unit;
    const int offsetMult = 6 * unit;
    const int sliderWidth = 60 * unit;
    const int sliderHeight = 3 * unit;

    gainSlider_ .setBounds (margin, offsetAdd + 0 * offsetMult, sliderWidth, sliderHeight);
    frequencySlider_.setBounds (margin, offsetAdd + 1 * offsetMult, sliderWidth, sliderHeight);
    bandwidthSlider_  .setBounds (margin, offsetAdd + 2 * offsetMult, sliderWidth, sliderHeight);

    gainLabel_  .setBounds (margin, 12 + 0 * offsetMult, sliderWidth, sliderHeight);
    frequencyLabel_ .setBounds (margin, 12 + 1 * offsetMult, sliderWidth, sliderHeight);
    bandwidthLabel_   .setBounds (margin, 12 + 2 * offsetMult, sliderWidth, sliderHeight);
}

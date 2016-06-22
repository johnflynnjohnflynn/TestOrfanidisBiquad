/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "ParameterSlider.h"


//==============================================================================
/**
*/
class TestOrfanidisBiquadAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    TestOrfanidisBiquadAudioProcessorEditor (TestOrfanidisBiquadAudioProcessor&);
    ~TestOrfanidisBiquadAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    enum SymbolicIndexNames     // Allow use of symbolic names instead
    {                           // of managedParameters indices.
        gainName,               // Must have the same ordering as
        frequencyName,              // processor's managedParameters!!!
        bandwidthName
    };

    Label gainLabel_;
    Label frequencyLabel_;
    Label bandwidthLabel_;
    ParameterSlider gainSlider_;
    ParameterSlider frequencySlider_;
    ParameterSlider bandwidthSlider_;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TestOrfanidisBiquadAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestOrfanidisBiquadAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED

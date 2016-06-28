/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "OrfanidisCalc.h"


//==============================================================================
/**
*/
class TestOrfanidisBiquadAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    TestOrfanidisBiquadAudioProcessor();
    ~TestOrfanidisBiquadAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    AudioParameterFloat* gain;      // managedParameters owns
    AudioParameterFloat* frequency;
    AudioParameterFloat* bandwidth;

    OrfanidisCalc coeffs;

    std::vector<double> xn_1; // state for up to 8 chans
    std::vector<double> xn_2;
    std::vector<double> yn_1;
    std::vector<double> yn_2;

    double denormal {1.0e-16};  // use to keep mantissa from dropping below 1.xxx
                               // see http://www.earlevel.com/main/2012/12/03/a-note-about-de-normalization/
                               // also see Falco's DspFilters MathSupplement.h re: 1e-8?


    

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestOrfanidisBiquadAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED

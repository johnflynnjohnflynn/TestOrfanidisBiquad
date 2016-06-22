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
    OrfanidisCalc coeffs;

    /*const double b0 { 1.62784};     // coeffs from peq.m matlab code in peq.pdf
    const double b1 {-1.14836};     // using command...
    const double b2 {-0.20611};     // [b, a, G1] = peq(1, 2, 1.75, 0.25*pi, 0.4*pi)
    //const double a0 { 1.0};
    const double a1 {-0.806086};
    const double a2 { 0.079451};*/
    std::vector<double> xn_1; // state for up to 8 chans
    std::vector<double> xn_2;
    std::vector<double> yn_1;
    std::vector<double> yn_2;
    double denormal {1.0e-20};      // use to keep mantissa from dropping below 1.xxx
                                    // see http://www.earlevel.com/main/2012/12/03/a-note-about-de-normalization/

    

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestOrfanidisBiquadAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED

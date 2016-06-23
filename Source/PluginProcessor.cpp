/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
TestOrfanidisBiquadAudioProcessor::TestOrfanidisBiquadAudioProcessor()
    : gain      {nullptr},
      frequency {nullptr},
      bandwidth {nullptr}
{
    addParameter (gain      = new AudioParameterFloat {"GainID",      "Gain",      -36.0f,  36.0f, 0.0f});
    addParameter (frequency = new AudioParameterFloat {"FrequencyID", "Frequency",   0.0f,   1.0f, 0.5f});
    addParameter (bandwidth = new AudioParameterFloat {"BandwidthID", "Bandwidth",   0.01f,  1.0f, 0.5f});

    xn_1.resize (8, 0); // state for up to 8 chans
    xn_2.resize (8, 0);
    yn_1.resize (8, 0);
    yn_2.resize (8, 0);
}

TestOrfanidisBiquadAudioProcessor::~TestOrfanidisBiquadAudioProcessor()
{
}

//==============================================================================
const String TestOrfanidisBiquadAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TestOrfanidisBiquadAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TestOrfanidisBiquadAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double TestOrfanidisBiquadAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TestOrfanidisBiquadAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TestOrfanidisBiquadAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TestOrfanidisBiquadAudioProcessor::setCurrentProgram (int index)
{
}

const String TestOrfanidisBiquadAudioProcessor::getProgramName (int index)
{
    return String();
}

void TestOrfanidisBiquadAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TestOrfanidisBiquadAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

	xn_1.assign(8, 0); // clear unit delays
	xn_2.assign(8, 0);
	yn_1.assign(8, 0);
	yn_2.assign(8, 0);

       coeffs.setRate (sampleRate);
}

void TestOrfanidisBiquadAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TestOrfanidisBiquadAudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
{
    // Reject any bus arrangements that are not compatible with your plugin

    const int numChannels = preferredSet.size();

   #if JucePlugin_IsMidiEffect
    if (numChannels != 0)
        return false;
   #elif JucePlugin_IsSynth
    if (isInput || (numChannels != 1 && numChannels != 2))
        return false;
   #else
    if (numChannels != 1 && numChannels != 2)
        return false;

    if (! AudioProcessor::setPreferredBusArrangement (! isInput, bus, preferredSet))
        return false;
   #endif

    return AudioProcessor::setPreferredBusArrangement (isInput, bus, preferredSet);
}
#endif

void TestOrfanidisBiquadAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...

    const double G  = Decibels::decibelsToGain ((double) *gain);
   // const double GB = Decibels::decibelsToGain (*gain / 2);
   // const double w0 = *frequency * double_Pi;
   // const double Dw = std::pow (1.0/0.1, (double) *bandwidth) * double_Pi;

   // std::cout << Dw << "\n";

    coeffs.calculate(G, *frequency, *bandwidth);

    const double b0 = coeffs.b0();
    const double b1 = coeffs.b1();
    const double b2 = coeffs.b2();
    const double a1 = coeffs.a1();
    const double a2 = coeffs.a2();

    float** yn = buffer.getArrayOfWritePointers();

    for (int s = 0; s < buffer.getNumSamples(); ++s)
    {
        for (int c = 0; c < totalNumInputChannels; ++c)
        {
            const double xn = static_cast<double> (yn[c][s]); // perform calcs at double

                                          // direct form 1
            yn[c][s] = static_cast<float> (b0*xn + b1*xn_1[c] + b2*xn_2[c]
                                                 - a1*yn_1[c] - a2*yn_2[c]);

            xn_2[c] = xn_1[c];  // advance delay networks
            xn_1[c] = xn;
            yn_2[c] = yn_1[c];
            yn_1[c] = yn[c][s];
        }
    }

    denormal *= -1; // avoid removal by DC filter
}

//==============================================================================
bool TestOrfanidisBiquadAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TestOrfanidisBiquadAudioProcessor::createEditor()
{
    return new TestOrfanidisBiquadAudioProcessorEditor (*this);
}

//==============================================================================
void TestOrfanidisBiquadAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TestOrfanidisBiquadAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TestOrfanidisBiquadAudioProcessor();
}

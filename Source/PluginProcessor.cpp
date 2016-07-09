/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
TestParameters02AudioProcessor::TestParameters02AudioProcessor()
                                                      // ID            Name               Min      Max     Def nSteps   skew broadcastParam
    : gainStepSizeParam {new jf::ParamStepBroadcast  {"gainStepID", "Gain step size",  0.05f,     3.0f,   0.5f              }},
      freqStepSizeParam {new jf::ParamStepBroadcast  {"freqStepID", "Freq step size",      1,        7,      5,    6        }},
      gainParam         {new jf::ParamStepListenGain {"gainID",     "Gain",           -12.0f,    12.0f,   0.0f,    4,   0.0f, *gainStepSizeParam}},
      freqParam         {new jf::ParamStepListenFreq {"freqID",     "Freq",            20.0f, 20000.0f, 632.456f, 48,   3.0f, *freqStepSizeParam}},
      qParam            {new jf::ParamStep           {"qID",        "Q",                0.0707f,  7.07f,  0.707f, 18,   2.0f}},
      gain2Param        {new jf::ParamStep           {"gain2ID",    "Gain2",          -12.0f,    12.0f,   0.0f,    4,   0.0f}},
      freq2Param        {new jf::ParamStep           {"freq2ID",    "Freq2",           20.0f, 20000.0f, 632.456f, 48,   3.0f}},
      q2Param           {new jf::ParamStep           {"q2ID",       "Q2",               0.0707f,  7.07f,  0.707f, 18,   2.0f}}
{
        // addParameter()s to the processor's OwnedArray<AudioProcessorParameter>
        // managedParameters (which takes ownership and deletes appropriately)
    addParameter (gainStepSizeParam);
    addParameter (freqStepSizeParam);
    addParameter (gainParam);
    addParameter (freqParam);
    addParameter (qParam);
    addParameter (gain2Param);
    addParameter (freq2Param);
    addParameter (q2Param);
}

TestParameters02AudioProcessor::~TestParameters02AudioProcessor()
{
}

//==============================================================================
const String TestParameters02AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TestParameters02AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TestParameters02AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double TestParameters02AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TestParameters02AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TestParameters02AudioProcessor::getCurrentProgram()
{
    return 0;
}

void TestParameters02AudioProcessor::setCurrentProgram (int /*index*/)
{
}

const String TestParameters02AudioProcessor::getProgramName (int /*index*/)
{
    return String();
}

void TestParameters02AudioProcessor::changeProgramName (int /*index*/, const String& /*newName*/)
{
}

//==============================================================================
void TestParameters02AudioProcessor::prepareToPlay (double /*sampleRate*/, int /*samplesPerBlock*/)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void TestParameters02AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TestParameters02AudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
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

void TestParameters02AudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& /*midiMessages*/)
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
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        //float* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
    
    /*std::cout << getParameters()[1]->getName(64) << " " << (String) getParameters()[1]->getValue() << "\n";
    std::cout << "*freqStep  " << (String) *freqStepSizeParam << "\n";
    std::cout << getParameters()[3]->getName(64) << " " << (String) getParameters()[3]->getValue() << "\n";
    std::cout << "*freqparam " << (String) *freqParam << "\n";
    std::cout << "*qparam " << (String) *qParam << "\n";
    std::cout << "\n";*/
}

//==============================================================================
bool TestParameters02AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TestParameters02AudioProcessor::createEditor()
{
    return new TestParameters02AudioProcessorEditor (*this);
}

//==============================================================================
void TestParameters02AudioProcessor::getStateInformation (MemoryBlock& /*destData*/)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TestParameters02AudioProcessor::setStateInformation (const void* /*data*/, int /*sizeInBytes*/)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
   #if JF_UNIT_TESTS
    jf::runUnitTests();
   #endif

    return new TestParameters02AudioProcessor();
}

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

    : stateAB {*this},
      statePresets {*this, "JohnFlynn/TestParameters02/presets.xml"}, // ID     Name            Min      Max     Def nSteps   skew broadcastParam
      gainStepSizeParam {new parameter::ParamStepBroadcast  {"gainStepID", "Gain step size",  0.05f,     3.0f,   0.5f              }},
      freqStepSizeParam {new parameter::ParamStepBroadcast  {"freqStepID", "Freq step size",      1,        7,      5,    6        }},
      gain1Param        {new parameter::ParamStepListenGain {"gain1ID",    "Gain1",          -12.0f,    12.0f,   0.0f,   24,   0.0f, *gainStepSizeParam}},
      freq1Param        {new parameter::ParamStepListenFreq {"freq1ID",    "Freq1",           20.0f, 20000.0f, 632.456f, 48,   3.0f, *freqStepSizeParam}},
      q1Param           {new parameter::ParamStep           {"q1ID",       "Q1",               0.0707f,  7.07f,  0.707f, 18,   2.0f}},
      gain2Param        {new parameter::ParamStepListenGain {"gain2ID",    "Gain2",          -12.0f,    12.0f,   0.0f,   24,   0.0f, *gainStepSizeParam}},
      freq2Param        {new parameter::ParamStepListenFreq {"freq2ID",    "Freq2",           20.0f, 20000.0f, 632.456f, 48,   3.0f, *freqStepSizeParam}},
      q2Param           {new parameter::ParamStep           {"q2ID",       "Q2",               0.0707f,  7.07f,  0.707f, 18,   2.0f}},
      gain3Param        {new parameter::ParamStepListenGain {"gain3ID",    "Gain3",          -12.0f,    12.0f,   0.0f,   24,   0.0f, *gainStepSizeParam}},
      freq3Param        {new parameter::ParamStepListenFreq {"freq3ID",    "Freq3",           20.0f, 20000.0f, 632.456f, 48,   3.0f, *freqStepSizeParam}},
      q3Param           {new parameter::ParamStep           {"q3ID",       "Q3",               0.0707f,  7.07f,  0.707f, 18,   2.0f}},
      gain4Param        {new parameter::ParamStepListenGain {"gain4ID",    "Gain4",          -12.0f,    12.0f,   0.0f,   24,   0.0f, *gainStepSizeParam}},
      freq4Param        {new parameter::ParamStepListenFreq {"freq4ID",    "Freq4",           20.0f, 20000.0f, 632.456f, 48,   3.0f, *freqStepSizeParam}},
      q4Param           {new parameter::ParamStep           {"q4ID",       "Q4",               0.0707f,  7.07f,  0.707f, 18,   2.0f}},
      gain5Param        {new parameter::ParamStepListenGain {"gain5ID",    "Gain5",          -12.0f,    12.0f,   0.0f,   24,   0.0f, *gainStepSizeParam}},
      freq5Param        {new parameter::ParamStepListenFreq {"freq5ID",    "Freq5",           20.0f, 20000.0f, 632.456f, 48,   3.0f, *freqStepSizeParam}},
      q5Param           {new parameter::ParamStep           {"q5ID",       "Q5",               0.0707f,  7.07f,  0.707f, 18,   2.0f}},
      gain6Param        {new parameter::ParamStepListenGain {"gain6ID",    "Gain6",          -12.0f,    12.0f,   0.0f,   24,   0.0f, *gainStepSizeParam}},
      freq6Param        {new parameter::ParamStepListenFreq {"freq6ID",    "Freq6",           20.0f, 20000.0f, 632.456f, 48,   3.0f, *freqStepSizeParam}},
      q6Param           {new parameter::ParamStep           {"q6ID",       "Q6",               0.0707f,  7.07f,  0.707f, 18,   2.0f}},
      gain7Param        {new parameter::ParamStepListenGain {"gain7ID",    "Gain7",          -12.0f,    12.0f,   0.0f,   24,   0.0f, *gainStepSizeParam}},
      freq7Param        {new parameter::ParamStepListenFreq {"freq7ID",    "Freq7",           20.0f, 20000.0f, 632.456f, 48,   3.0f, *freqStepSizeParam}},
      q7Param           {new parameter::ParamStep           {"q7ID",       "Q7",               0.0707f,  7.07f,  0.707f, 18,   2.0f}}
{
        // addParameter()s to the processor's OwnedArray<AudioProcessorParameter>
        // managedParameters (which takes ownership and deletes appropriately)
    addParameter (gainStepSizeParam);
    addParameter (freqStepSizeParam);
    addParameter (gain1Param);
    addParameter (freq1Param);
    addParameter (q1Param);
    addParameter (gain2Param);
    addParameter (freq2Param);
    addParameter (q2Param);
    addParameter (gain3Param);
    addParameter (freq3Param);
    addParameter (q3Param);
    addParameter (gain4Param);
    addParameter (freq4Param);
    addParameter (q4Param);
    addParameter (gain5Param);
    addParameter (freq5Param);
    addParameter (q5Param);
    addParameter (gain6Param);
    addParameter (freq6Param);
    addParameter (q6Param);
    addParameter (gain7Param);
    addParameter (freq7Param);
    addParameter (q7Param);
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
void TestParameters02AudioProcessor::prepareToPlay (double sampleRate, int /*samplesPerBlock*/)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    band1.reset (sampleRate);
    band2.reset (sampleRate);
    band3.reset (sampleRate);
    band4.reset (sampleRate);
    band5.reset (sampleRate);
    band6.reset (sampleRate);
    band7.reset (sampleRate);
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

    /*std::cout << getParameters()[1]->getName(64) << " " << (String) getParameters()[1]->getValue() << "\n";
    std::cout << "*freqStep  " << (String) *freqStepSizeParam << "\n";
    std::cout << getParameters()[3]->getName(64) << " " << (String) getParameters()[3]->getValue() << "\n";
    std::cout << "*freqparam " << (String) *freq1Param << "\n";
    std::cout << "*qparam " << (String) *q1Param << "\n";
    std::cout << "\n";*/

    const float freq1Norm {freq1Param->getRange().convertTo0to1(*freq1Param)};
    const float freq2Norm {freq2Param->getRange().convertTo0to1(*freq2Param)};
    const float freq3Norm {freq3Param->getRange().convertTo0to1(*freq3Param)};
    const float freq4Norm {freq4Param->getRange().convertTo0to1(*freq4Param)};
    const float freq5Norm {freq5Param->getRange().convertTo0to1(*freq5Param)};
    const float freq6Norm {freq6Param->getRange().convertTo0to1(*freq6Param)};
    const float freq7Norm {freq7Param->getRange().convertTo0to1(*freq7Param)};
    
    band1.process(buffer, totalNumInputChannels, *gain1Param, freq1Norm, *q1Param);
    band2.process(buffer, totalNumInputChannels, *gain2Param, freq2Norm, *q2Param);
    band3.process(buffer, totalNumInputChannels, *gain3Param, freq3Norm, *q3Param);
    band4.process(buffer, totalNumInputChannels, *gain4Param, freq4Norm, *q4Param);
    band5.process(buffer, totalNumInputChannels, *gain5Param, freq5Norm, *q5Param);
    band6.process(buffer, totalNumInputChannels, *gain6Param, freq6Norm, *q6Param);
    band7.process(buffer, totalNumInputChannels, *gain7Param, freq7Norm, *q7Param);
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
    test::runUnitTests();
   #endif

    return new TestParameters02AudioProcessor();
}

/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Test.h"
#include "Range.h"
#include "Parameter.h"
#include "State.h"

//==============================================================================
/**
*/
class TestParameters02AudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    TestParameters02AudioProcessor();
    ~TestParameters02AudioProcessor();

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
    //==============================================================================
    jf::ParamStepBroadcast*  gainStepSizeParam;   // Raw pointers here. Processor's
    jf::ParamStepBroadcast*  freqStepSizeParam;   // managedParameters OwnedArray
    jf::ParamStepListenGain* gainParam;           // owns and manages. (See xtor.)
    jf::ParamStepListenFreq* freqParam;
    jf::ParamStep*           qParam;
    jf::ParamStep*           gain2Param;
    jf::ParamStep*           freq2Param;
    jf::ParamStep*           q2Param;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestParameters02AudioProcessor)
};

//==============================================================================
JF_DECLARE_UNIT_TEST_WITH_STATIC_INSTANCE (PluginProcessorTests);

#endif  // PLUGINPROCESSOR_H_INCLUDED

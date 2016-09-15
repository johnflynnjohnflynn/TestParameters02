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
#include "OrfanidisCalc.h"
#include "Filter.h"

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

    //==============================================================================
    state::StateAB stateAB;
    state::StatePresets statePresets;

private:
    //==============================================================================
    parameter::ParamStepBroadcast*  gainStepSizeParam;   // Raw pointers here. Processor's
    parameter::ParamStepBroadcast*  freqStepSizeParam;   // managedParameters OwnedArray
                                                         // owns and manages. (See xtor.)
    parameter::ParamStepListenGain* gain1Param;
    parameter::ParamStepListenFreq* freq1Param;
    parameter::ParamStep*           q1Param;
    parameter::ParamStepListenGain* gain2Param;
    parameter::ParamStepListenFreq* freq2Param;
    parameter::ParamStep*           q2Param;
    parameter::ParamStepListenGain* gain3Param;
    parameter::ParamStepListenFreq* freq3Param;
    parameter::ParamStep*           q3Param;
    parameter::ParamStepListenGain* gain4Param;
    parameter::ParamStepListenFreq* freq4Param;
    parameter::ParamStep*           q4Param;
    parameter::ParamStepListenGain* gain5Param;
    parameter::ParamStepListenFreq* freq5Param;
    parameter::ParamStep*           q5Param;
    parameter::ParamStepListenGain* gain6Param;
    parameter::ParamStepListenFreq* freq6Param;
    parameter::ParamStep*           q6Param;
    parameter::ParamStepListenGain* gain7Param;
    parameter::ParamStepListenFreq* freq7Param;
    parameter::ParamStep*           q7Param;

    filter::ParametricBand band1;
    filter::ParametricBand band2;
    filter::ParametricBand band3;
    filter::ParametricBand band4;
    filter::ParametricBand band5;
    filter::ParametricBand band6;
    filter::ParametricBand band7;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestParameters02AudioProcessor)
};

//==============================================================================
JF_DECLARE_UNIT_TEST_WITH_STATIC_INSTANCE (PluginProcessorTests);

#endif  // PLUGINPROCESSOR_H_INCLUDED

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
    parameter::ParamStepListenGain* gainParam;           // owns and manages. (See xtor.)
    parameter::ParamStepListenFreq* freqParam;
    parameter::ParamStep*           qParam;
    parameter::ParamStep*           gain2Param;
    parameter::ParamStep*           freq2Param;
    parameter::ParamStep*           q2Param;

    OrfanidisCalc coeffs;

    std::vector<double> xn_1; // state for up to 8 chans
    std::vector<double> xn_2;
    std::vector<double> yn_1;
    std::vector<double> yn_2;

    double denormal {1.0e-16}; // use to keep mantissa from dropping below 1.xxx
                               // see http://www.earlevel.com/main/2012/12/03/a-note-about-de-normalization/
                               // also see Falco's DspFilters MathSupplement.h re: 1e-8?

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestParameters02AudioProcessor)
};

//==============================================================================
JF_DECLARE_UNIT_TEST_WITH_STATIC_INSTANCE (PluginProcessorTests);

#endif  // PLUGINPROCESSOR_H_INCLUDED

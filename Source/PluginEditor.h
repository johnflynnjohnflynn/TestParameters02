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
#include "Slider.h"

//==============================================================================
/**
*/
class TestParameters02AudioProcessorEditor  : public AudioProcessorEditor
{
public:
    TestParameters02AudioProcessorEditor (TestParameters02AudioProcessor&);
    ~TestParameters02AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    jf::SliderStep gainStepSizeSlider;
    jf::SliderStep freqStepSizeSlider;
    jf::SliderStep gainSlider;
    jf::SliderStep freqSlider;
    jf::SliderStep qSlider;
    jf::SliderStep gain2Slider;
    jf::SliderStep freq2Slider;
    jf::SliderStep q2Slider;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TestParameters02AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestParameters02AudioProcessorEditor)
};

#endif  // PLUGINEDITOR_H_INCLUDED

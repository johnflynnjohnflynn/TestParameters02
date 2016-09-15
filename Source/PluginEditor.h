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
#include "State.h"
#include "Look.h"
#include "Utility.h"

//==============================================================================
/**
*/
class TestParameters02AudioProcessorEditor  : public AudioProcessorEditor
{
public:
    explicit TestParameters02AudioProcessorEditor (TestParameters02AudioProcessor&);
    ~TestParameters02AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    utility::UtilityComponent utilityComponent;

    slider::SliderStep gain1Slider;
    slider::SliderStep freq1Slider;
    slider::SliderStep q1Slider;
    slider::SliderStep gain2Slider;
    slider::SliderStep freq2Slider;
    slider::SliderStep q2Slider;
    slider::SliderStep gain3Slider;
    slider::SliderStep freq3Slider;
    slider::SliderStep q3Slider;
    slider::SliderStep gain4Slider;
    slider::SliderStep freq4Slider;
    slider::SliderStep q4Slider;
    slider::SliderStep gain5Slider;
    slider::SliderStep freq5Slider;
    slider::SliderStep q5Slider;
    slider::SliderStep gain6Slider;
    slider::SliderStep freq6Slider;
    slider::SliderStep q6Slider;
    slider::SliderStep gain7Slider;
    slider::SliderStep freq7Slider;
    slider::SliderStep q7Slider;

    look::CustomLook look;

    TestParameters02AudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestParameters02AudioProcessorEditor)
};

#endif  // PLUGINEDITOR_H_INCLUDED

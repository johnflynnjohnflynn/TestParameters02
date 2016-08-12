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
    state::StateComponent stateComponent;

    slider::SliderStep gainStepSizeSlider;
    slider::SliderStep freqStepSizeSlider;
    slider::SliderStep gainSlider;
    slider::SliderStep freqSlider;
    slider::SliderStep qSlider;
    slider::SliderStep gain2Slider;
    slider::SliderStep freq2Slider;
    slider::SliderStep q2Slider;

    look::CustomLook look;

    TestParameters02AudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestParameters02AudioProcessorEditor)
};

#endif  // PLUGINEDITOR_H_INCLUDED

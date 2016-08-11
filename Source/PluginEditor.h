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
class TestParameters02AudioProcessorEditor  : public AudioProcessorEditor,
                                              public Button::Listener,
                                              public ComboBox::Listener
{
public:
    explicit TestParameters02AudioProcessorEditor (TestParameters02AudioProcessor&);
    ~TestParameters02AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    TextButton toggleABButton;
    TextButton copyABButton;

    ComboBox presetBox;
    TextButton savePresetButton;
    TextButton deletePresetButton;

    slider::SliderStep gainStepSizeSlider;
    slider::SliderStep freqStepSizeSlider;
    slider::SliderStep gainSlider;
    slider::SliderStep freqSlider;
    slider::SliderStep qSlider;
    slider::SliderStep gain2Slider;
    slider::SliderStep freq2Slider;
    slider::SliderStep q2Slider;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TestParameters02AudioProcessor& processor;

    void buttonClicked (Button* clickedButton) override;
    void comboBoxChanged (ComboBox* changedComboBox) override;
    void updatePresetBox();
    void savePresetAlertWindow();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestParameters02AudioProcessorEditor)
};

#endif  // PLUGINEDITOR_H_INCLUDED

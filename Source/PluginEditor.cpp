/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TestParameters02AudioProcessorEditor::TestParameters02AudioProcessorEditor (TestParameters02AudioProcessor& p)
    : AudioProcessorEditor (&p),
      stateComponent {p.stateAB, p.statePresets},
      gainStepSizeSlider {*p.getParameters()[0]},                           // better way than indices?
      freqStepSizeSlider {*p.getParameters()[1]},
      gainSlider         {*p.getParameters()[2]},
      freqSlider         {*p.getParameters()[3]}, //freqStepSizeSlider.slider_},
      qSlider            {*p.getParameters()[4]},
      gain2Slider        {*p.getParameters()[5]},
      freq2Slider        {*p.getParameters()[6]},
      q2Slider           {*p.getParameters()[7]},
      processor (p)
{
    addAndMakeVisible (stateComponent);
    
    addAndMakeVisible (&gainStepSizeSlider);
    addAndMakeVisible (&freqStepSizeSlider);
    addAndMakeVisible (&gainSlider);
    addAndMakeVisible (&freqSlider);
    addAndMakeVisible (&qSlider);
    addAndMakeVisible (&gain2Slider);
    addAndMakeVisible (&freq2Slider);
    addAndMakeVisible (&q2Slider);

    LookAndFeel::setDefaultLookAndFeel (&look);

    setSize (1000, 700); // remember to set before xtor finished
}

TestParameters02AudioProcessorEditor::~TestParameters02AudioProcessorEditor()
{
}

//==============================================================================
void TestParameters02AudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::lightgrey);
}

void TestParameters02AudioProcessorEditor::resized()
{
    Rectangle<int> r (getLocalBounds().reduced (5));

    stateComponent.setBounds (r.removeFromTop (35));

    r.removeFromTop (10); // spacer

    const int numSliders {4};
    const int sliderHeight {r.getHeight() / numSliders};

    auto slice1 = r.removeFromTop(sliderHeight);
    auto slice2 = r.removeFromTop(sliderHeight);
    auto slice3 = r.removeFromTop(sliderHeight);
    auto slice4 = r.removeFromTop(sliderHeight);

    gainStepSizeSlider.setBounds (slice1.removeFromLeft  (200));
    freqStepSizeSlider.setBounds (slice1.removeFromRight (200));
    gainSlider        .setBounds (slice2.removeFromLeft  (200));
    gain2Slider       .setBounds (slice2.removeFromRight (200));
    freqSlider        .setBounds (slice3.removeFromLeft  (200));
    freq2Slider       .setBounds (slice3.removeFromRight (200));
    qSlider           .setBounds (slice4.removeFromLeft  (200));
    q2Slider          .setBounds (slice4.removeFromRight (200));
}

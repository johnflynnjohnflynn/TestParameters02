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
      utilityComponent {p.stateAB, p.statePresets, p},
      //gainStepSizeSlider {*p.getParameters()[0]},                             // these now live in UtilityComponent
      //freqStepSizeSlider {*p.getParameters()[1]},
      gainSlider         {*p.getParameters()[2]},                               // better way than indices?
      freqSlider         {*p.getParameters()[3]}, //freqStepSizeSlider.slider_},
      qSlider            {*p.getParameters()[4]},
      gain2Slider        {*p.getParameters()[5]},
      freq2Slider        {*p.getParameters()[6]},
      q2Slider           {*p.getParameters()[7]},
      processor (p)
{
    addAndMakeVisible (&utilityComponent);

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

    utilityComponent.setBounds (r.removeFromTop (35));

    const int rows {3};
    const int sliderHeight {r.getHeight() / rows};

    const int cols {2};
    const int sliderWidth {r.getWidth() / cols};

    auto slice1 = r.removeFromTop(sliderHeight);
    gainSlider        .setBounds (slice1.removeFromLeft (sliderWidth).reduced (10));
    gain2Slider       .setBounds (slice1.reduced (10));

    auto slice2 = r.removeFromTop(sliderHeight);
    freqSlider        .setBounds (slice2.removeFromLeft (sliderWidth).reduced (10));
    freq2Slider       .setBounds (slice2.reduced (10));
    
    auto slice3 = r.removeFromTop(sliderHeight);
    qSlider           .setBounds (slice3.removeFromLeft (sliderWidth).reduced (10));
    q2Slider          .setBounds (slice3.reduced (10));
}

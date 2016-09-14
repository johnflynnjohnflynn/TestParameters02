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

    gainStepSizeSlider.setSliderStyle (Slider::SliderStyle::IncDecButtons); // override default rotary
    freqStepSizeSlider.setSliderStyle (Slider::SliderStyle::IncDecButtons);
    gainStepSizeSlider.setTextBoxStyle (Slider::TextEntryBoxPosition::TextBoxLeft, false, 75, 16);
    freqStepSizeSlider.setTextBoxStyle (Slider::TextEntryBoxPosition::TextBoxLeft, false, 75, 16);
    
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

    auto topBar = r.removeFromTop (35);

    stateComponent.setBounds (topBar.removeFromLeft (700));

    gainStepSizeSlider.setBounds (topBar.removeFromLeft (150).reduced (5));
    freqStepSizeSlider.setBounds (topBar.reduced (5));

    r.removeFromTop (10); // spacer

    const int numSliders {3};
    const int sliderHeight {r.getHeight() / numSliders};

    auto slice1 = r.removeFromTop(sliderHeight);
    auto slice2 = r.removeFromTop(sliderHeight);
    auto slice3 = r.removeFromTop(sliderHeight);

    gainSlider        .setBounds (slice1.removeFromLeft  (200));
    gain2Slider       .setBounds (slice1.removeFromRight (200));
    freqSlider        .setBounds (slice2.removeFromLeft  (200));
    freq2Slider       .setBounds (slice2.removeFromRight (200));
    qSlider           .setBounds (slice3.removeFromLeft  (200));
    q2Slider          .setBounds (slice3.removeFromRight (200));
}

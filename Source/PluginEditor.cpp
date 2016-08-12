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

    setSize (400, 700); // remember to set before xtor finished
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
    Rectangle<int> r (getLocalBounds().reduced (10));

    stateComponent.setBounds (r.removeFromTop (225));

    r.removeFromTop (15); // spacer

    const int numSliders {8};
    const int sliderHeight {r.getHeight() / numSliders};

    gainStepSizeSlider.setBounds (r.removeFromTop (sliderHeight));
    freqStepSizeSlider.setBounds (r.removeFromTop (sliderHeight));
    gainSlider        .setBounds (r.removeFromTop (sliderHeight));
    freqSlider        .setBounds (r.removeFromTop (sliderHeight));
    qSlider           .setBounds (r.removeFromTop (sliderHeight));
    gain2Slider       .setBounds (r.removeFromTop (sliderHeight));
    freq2Slider       .setBounds (r.removeFromTop (sliderHeight));
    q2Slider          .setBounds (r.removeFromTop (sliderHeight));
}

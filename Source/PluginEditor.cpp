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
      toggleABButton {"A-B"},
      copyABButton {"Copy"},
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
    addAndMakeVisible (toggleABButton);
    addAndMakeVisible (copyABButton);
    toggleABButton.addListener (this);
    copyABButton.addListener (this);
    
    addAndMakeVisible (&gainStepSizeSlider);
    addAndMakeVisible (&freqStepSizeSlider);
    addAndMakeVisible (&gainSlider);
    addAndMakeVisible (&freqSlider);
    addAndMakeVisible (&qSlider);
    addAndMakeVisible (&gain2Slider);
    addAndMakeVisible (&freq2Slider);
    addAndMakeVisible (&q2Slider);

    setSize (400, 550); // remember to set before xtor finished
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

    const int sliderHeight {50};

    toggleABButton    .setBounds (r.removeFromTop (sliderHeight));
    copyABButton      .setBounds (r.removeFromTop (sliderHeight));
    gainStepSizeSlider.setBounds (r.removeFromTop (sliderHeight));
    freqStepSizeSlider.setBounds (r.removeFromTop (sliderHeight));
    gainSlider        .setBounds (r.removeFromTop (sliderHeight));
    freqSlider        .setBounds (r.removeFromTop (sliderHeight));
    qSlider           .setBounds (r.removeFromTop (sliderHeight));
    gain2Slider       .setBounds (r.removeFromTop (sliderHeight));
    freq2Slider       .setBounds (r.removeFromTop (sliderHeight));
    q2Slider          .setBounds (r.removeFromTop (sliderHeight));
}

void TestParameters02AudioProcessorEditor::buttonClicked (Button* clickedButton)
{
    if (clickedButton == &toggleABButton) processor.abState.toggleAB();
    if (clickedButton == &copyABButton)   processor.abState.copyAB();
}

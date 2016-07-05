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
      gainSlider {*p.getParameters()[0]},                                           // better way than indices?
      processor (p)
{
    addAndMakeVisible (&gainSlider);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
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
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    Rectangle<int> r (getLocalBounds().reduced (10));

    const int sliderHeight {50};

    gainSlider.setBounds (r.removeFromTop (sliderHeight));
}

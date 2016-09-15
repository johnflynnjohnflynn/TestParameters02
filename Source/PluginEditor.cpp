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
      gain1Slider        {*p.getParameters()[2]},                               // better way than indices?
      freq1Slider        {*p.getParameters()[3]}, //freqStepSizeSlider.slider_},
      q1Slider           {*p.getParameters()[4]},
      gain2Slider        {*p.getParameters()[5]},
      freq2Slider        {*p.getParameters()[6]},
      q2Slider           {*p.getParameters()[7]},
      gain3Slider        {*p.getParameters()[8]},
      freq3Slider        {*p.getParameters()[9]},
      q3Slider           {*p.getParameters()[10]},
      gain4Slider        {*p.getParameters()[11]},
      freq4Slider        {*p.getParameters()[12]},
      q4Slider           {*p.getParameters()[13]},
      gain5Slider        {*p.getParameters()[14]},
      freq5Slider        {*p.getParameters()[15]},
      q5Slider           {*p.getParameters()[16]},
      gain6Slider        {*p.getParameters()[17]},
      freq6Slider        {*p.getParameters()[18]},
      q6Slider           {*p.getParameters()[19]},
      gain7Slider        {*p.getParameters()[20]},
      freq7Slider        {*p.getParameters()[21]},
      q7Slider           {*p.getParameters()[22]},
      processor (p)
{
    addAndMakeVisible (&utilityComponent);

    addAndMakeVisible (&gain1Slider);
    addAndMakeVisible (&freq1Slider);
    addAndMakeVisible (&q1Slider);
    addAndMakeVisible (&gain2Slider);
    addAndMakeVisible (&freq2Slider);
    addAndMakeVisible (&q2Slider);
    addAndMakeVisible (&gain3Slider);
    addAndMakeVisible (&freq3Slider);
    addAndMakeVisible (&q3Slider);
    addAndMakeVisible (&gain4Slider);
    addAndMakeVisible (&freq4Slider);
    addAndMakeVisible (&q4Slider);
    addAndMakeVisible (&gain5Slider);
    addAndMakeVisible (&freq5Slider);
    addAndMakeVisible (&q5Slider);
    addAndMakeVisible (&gain6Slider);
    addAndMakeVisible (&freq6Slider);
    addAndMakeVisible (&q6Slider);
    addAndMakeVisible (&gain7Slider);
    addAndMakeVisible (&freq7Slider);
    addAndMakeVisible (&q7Slider);

    LookAndFeel::setDefaultLookAndFeel (&look);

    setSize (1000, 500); // remember to set before xtor finished
}

TestParameters02AudioProcessorEditor::~TestParameters02AudioProcessorEditor()
{
}

//==============================================================================
void TestParameters02AudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colour (0xff909090));
}

void TestParameters02AudioProcessorEditor::resized()
{
    Rectangle<int> r (getLocalBounds().reduced (2));

    utilityComponent.setBounds (r.removeFromTop (25));

    const int rows {3};
    const int sliderHeight {r.getHeight() / rows};

    const int cols {7};
    const int sliderWidth {r.getWidth() / cols};

    auto slice1 = r.removeFromTop(sliderHeight);
    gain1Slider.setBounds (slice1.removeFromLeft (sliderWidth).reduced (10));
    gain2Slider.setBounds (slice1.removeFromLeft (sliderWidth).reduced (10));
    gain3Slider.setBounds (slice1.removeFromLeft (sliderWidth).reduced (10));
    gain4Slider.setBounds (slice1.removeFromLeft (sliderWidth).reduced (10));
    gain5Slider.setBounds (slice1.removeFromLeft (sliderWidth).reduced (10));
    gain6Slider.setBounds (slice1.removeFromLeft (sliderWidth).reduced (10));
    gain7Slider.setBounds (slice1.reduced (10));

    auto slice2 = r.removeFromTop(sliderHeight);
    freq1Slider.setBounds (slice2.removeFromLeft (sliderWidth).reduced (10));
    freq2Slider.setBounds (slice2.removeFromLeft (sliderWidth).reduced (10));
    freq3Slider.setBounds (slice2.removeFromLeft (sliderWidth).reduced (10));
    freq4Slider.setBounds (slice2.removeFromLeft (sliderWidth).reduced (10));
    freq5Slider.setBounds (slice2.removeFromLeft (sliderWidth).reduced (10));
    freq6Slider.setBounds (slice2.removeFromLeft (sliderWidth).reduced (10));
    freq7Slider.setBounds (slice2.reduced (10));
    
    auto slice3 = r.removeFromTop(sliderHeight);
    q1Slider.setBounds (slice3.removeFromLeft (sliderWidth).reduced (10));
    q2Slider.setBounds (slice3.removeFromLeft (sliderWidth).reduced (10));
    q3Slider.setBounds (slice3.removeFromLeft (sliderWidth).reduced (10));
    q4Slider.setBounds (slice3.removeFromLeft (sliderWidth).reduced (10));
    q5Slider.setBounds (slice3.removeFromLeft (sliderWidth).reduced (10));
    q6Slider.setBounds (slice3.removeFromLeft (sliderWidth).reduced (10));
    q7Slider.setBounds (slice3.reduced (10));
}

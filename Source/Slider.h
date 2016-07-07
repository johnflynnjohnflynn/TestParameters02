/*
  ==============================================================================

    ParameterSlider.h
    Created: 5 Mar 2016 4:14:53pm

  ==============================================================================
*/

#ifndef PARAMETERSLIDER_H_INCLUDED
#define PARAMETERSLIDER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Parameter.h"

namespace jf
{

/** Modified version of ParameterSlider from Juce plugin demo that allows
    stepped sliders as well as continuous 
*/
class SliderStep  : public Slider,
                    private Timer
{
public:
    SliderStep (AudioProcessorParameter& p);

    void valueChanged() override;

    void timerCallback() override;

    void startedDragging() override;
    void stoppedDragging() override;

    double getValueFromText (const String& text) override;
    String getTextFromValue (double value) override;

    void updateSliderPos();

    AudioProcessorParameter& param;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderStep)
};

//==============================================================================
#if JF_UNIT_TESTS

class SliderTests  : public UnitTest
{
public:
    SliderTests();
    void runTest() override;
};

static SliderTests sliderTests;

#endif // JF_UNIT_TESTS

} // namespace jf

#endif  // PARAMETERSLIDER_H_INCLUDED

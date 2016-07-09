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
#include "Test.h"

namespace jf
{

//==============================================================================
/** Modified version of ParameterSlider from Juce plugin demo that allows
    stepped sliders (as well as continuous).
    
    Uses numSteps member of jf::Parameter to determine steps. (Set to 0 for 
    continuous)
    
    @see ParameterSlider, Slider, jf::Parameter
*/
class SliderStep  : public Slider,
                    private Timer
{
public:
    SliderStep (AudioProcessorParameter& p);

private:
    void valueChanged() override;

    void timerCallback() override;

    void startedDragging() override;
    void stoppedDragging() override;

    double getValueFromText (const String& text) override;
    String getTextFromValue (double value) override;

    void updateSliderPos();
    void updateInterval();

    AudioProcessorParameter& param;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderStep)
};

//==============================================================================
JF_DECLARE_UNIT_TEST_WITH_STATIC_INSTANCE (SliderTests)

//==============================================================================
} // namespace jf

#endif  // PARAMETERSLIDER_H_INCLUDED

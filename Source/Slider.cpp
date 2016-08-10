/*
  ==============================================================================

    Slider.cpp
    Created: 7 Jul 2016 9:09:46am
    Author:  John Flynn

  ==============================================================================
*/

#include "Slider.h"

namespace slider
{

SliderStep::SliderStep (AudioProcessorParameter& p)
    : Slider (p.getName (256)), param (p)
{
    if (1 <= p.getNumSteps() && p.getNumSteps() <= 100) // <=100? defaults to 37850784 steps!
    {
        const double normStepSize = 1.0 / (p.getNumSteps());
        setRange (0.0, 1.0, normStepSize); // stepped
    }
    else
        setRange (0.0, 1.0, 0.0); // continuous

    startTimerHz (30);
    updateSliderPos();
}

// private:
void SliderStep::valueChanged()
{
    param.setValueNotifyingHost ((float) Slider::getValue());
}

void SliderStep::timerCallback()
{
    updateInterval();
    updateSliderPos();
    updateText();
}

void SliderStep::startedDragging()     { param.beginChangeGesture(); }
void SliderStep::stoppedDragging()     { param.endChangeGesture();   }

double SliderStep::getValueFromText (const String& text)   { return param.getValueForText (text); }
String SliderStep::getTextFromValue (double value)         { return param.getText ((float) value, 1024); }

void SliderStep::updateSliderPos()
{
    const float newValue = param.getValue();

    if (newValue != (float) Slider::getValue() && ! isMouseButtonDown())
        Slider::setValue (newValue);
}
void SliderStep::updateInterval()
{
    if (parameter::ParamStepListenFreq* pslf = dynamic_cast<parameter::ParamStepListenFreq*> (&param))
    {
        const int numStepsParam = pslf->getNumSteps();
        const float newSliderInterval0to1 = 1.0f / numStepsParam;

        Slider::setRange (0, 1, newSliderInterval0to1);
    }
}

//==============================================================================
} // namespace slider

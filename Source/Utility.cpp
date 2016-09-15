/*
  ==============================================================================

    Utility.cpp
    Created: 15 Sep 2016 9:08:29am
    Author:  John Flynn

  ==============================================================================
*/

#include "Utility.h"

namespace utility
{

//==============================================================================
UtilityComponent::UtilityComponent (state::StateAB& sab, state::StatePresets& sp, AudioProcessor& p)
    : stateComponent {sab, sp},
      gainStepSizeSlider {*p.getParameters()[0]},                           // better way than indices?
      freqStepSizeSlider {*p.getParameters()[1]}
{
    addAndMakeVisible (stateComponent);

    gainStepSizeSlider.setSliderStyle (Slider::SliderStyle::LinearBar); // override default rotary
    freqStepSizeSlider.setSliderStyle (Slider::SliderStyle::LinearBar);

    gainStepSizeSlider.setColour (Slider::backgroundColourId, Colour (0xff808080));     // move to custom Look???
    gainStepSizeSlider.setColour (Slider::thumbColourId, Colour (0xff606060));
    freqStepSizeSlider.setColour (Slider::backgroundColourId, Colour (0xff808080));
    freqStepSizeSlider.setColour (Slider::thumbColourId, Colour (0xff606060));

    addAndMakeVisible (gainStepSizeSlider);
    addAndMakeVisible (freqStepSizeSlider);
}

void UtilityComponent::resized()
{
    auto r (getLocalBounds());

    const int componentWidth {r.getWidth() / 8};

    stateComponent.setBounds (r.removeFromLeft (componentWidth * 6));

    gainStepSizeSlider.setBounds (r.removeFromLeft (componentWidth).reduced (2));
    freqStepSizeSlider.setBounds (r.reduced (2));
}

//==============================================================================
} // namespace utility

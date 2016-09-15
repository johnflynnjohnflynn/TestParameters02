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

    gainStepSizeSlider.setSliderStyle (Slider::SliderStyle::IncDecButtons); // override default rotary
    freqStepSizeSlider.setSliderStyle (Slider::SliderStyle::IncDecButtons);

    gainStepSizeSlider.setTextBoxStyle (Slider::TextEntryBoxPosition::TextBoxLeft, false, 75, 32);
    freqStepSizeSlider.setTextBoxStyle (Slider::TextEntryBoxPosition::TextBoxLeft, false, 75, 32);

    addAndMakeVisible (gainStepSizeSlider);
    addAndMakeVisible (freqStepSizeSlider);
}

void UtilityComponent::resized()
{
    auto r (getLocalBounds());

    const int componentWidth {r.getWidth() / 8};

    stateComponent.setBounds (r.removeFromLeft (componentWidth * 6));

    gainStepSizeSlider.setBounds (r.removeFromLeft (componentWidth).reduced (5));
    freqStepSizeSlider.setBounds (r.reduced (5));
}

//==============================================================================
} // namespace utility

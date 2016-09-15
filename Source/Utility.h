/*
  ==============================================================================

    Utility.h
    Created: 15 Sep 2016 9:08:29am
    Author:  John Flynn

  ==============================================================================
*/

#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Test.h"
#include "State.h"
#include "Slider.h"

namespace utility
{

//==============================================================================
/** A utility bar for settings and preset handling. Lives at the top of the UI.

    Combines StateComponent for preset and AB handling with 
    stepSize/freqDivision sliders.
*/
class UtilityComponent  : public Component
{
public:
    UtilityComponent (state::StateAB& sab,
                      state::StatePresets& sp,
                      AudioProcessor& p);
    
    void paint (Graphics&) override {}
    void resized() override;

private:
    state::StateComponent stateComponent;

    slider::SliderStep gainStepSizeSlider;
    slider::SliderStep freqStepSizeSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UtilityComponent);
};

//==============================================================================
//JF_DECLARE_UNIT_TEST_WITH_STATIC_INSTANCE (UtilityTests)

//==============================================================================
} // namespace utility

#endif  // UTILITY_H_INCLUDED

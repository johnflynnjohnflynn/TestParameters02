/*
  ==============================================================================

    Look.h
    Created: 12 Aug 2016 5:32:46pm
    Author:  John Flynn

  ==============================================================================
*/

#ifndef LOOK_H_INCLUDED
#define LOOK_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

namespace look
{

class CustomLook  : public LookAndFeel_V3
{
public:
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos0to1,
                           float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;

private:
    Image knob       {ImageCache::getFromMemory (BinaryData::knob05LargeForeground4fs8_png,
                                                 BinaryData::knob05LargeForeground4fs8_pngSize)};
    Image knobMarker {ImageCache::getFromMemory (BinaryData::markerFilmstripfs8_png,
                                                 BinaryData::markerFilmstripfs8_pngSize)};

};

//==============================================================================
} // namespace look

#endif  // LOOK_H_INCLUDED

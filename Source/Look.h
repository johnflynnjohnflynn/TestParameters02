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
                           float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override
    {
        // const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

        jassert (knobMarker.getHeight() > knobMarker.getWidth()); // vertical strip

        const int knobSourceSize  {knobMarker.getWidth()};

        const int numFrames      {knobMarker.getHeight() / knobMarker.getWidth()};
        const int frameToDisplay {static_cast<int> (sliderPos0to1 * (numFrames - 1))};

        const int centreX {x + (width / 2)};            // x is numbox offset
        const int centreY {y + (height / 2)};
        const int knobDrawSize {jmin (width, height)};
        const int destX {centreX - (knobDrawSize / 2)};
        const int destY {centreY - (knobDrawSize / 2)};

        g.drawImage (knobMarker,
                     destX,                             // dest x
                     destY,                             // dest y
                     knobDrawSize,                      // dest w
                     knobDrawSize,                      // dest h
                     0,                                 // source x
                     frameToDisplay * knobSourceSize,   // source y (drawing offset)
                     knobSourceSize,                    // source w
                     knobSourceSize);                   // source h

        g.drawImage (knob,
                     destX,                             // dest x
                     destY,                             // dest y
                     knobDrawSize,                      // dest w
                     knobDrawSize,                      // dest h
                     0,                                 // source x
                     0,                                 // source y
                     knobSourceSize,                    // source w
                     knobSourceSize);                   // source h
    }

private:
    Image knob       {ImageCache::getFromMemory (BinaryData::knob05LargeForeground4fs8_png,
                                                 BinaryData::knob05LargeForeground4fs8_pngSize)};
    Image knobMarker {ImageCache::getFromMemory (BinaryData::markerFilmstripfs8_png,
                                                 BinaryData::markerFilmstripfs8_pngSize)};

};

//==============================================================================
} // namespace look

#endif  // LOOK_H_INCLUDED

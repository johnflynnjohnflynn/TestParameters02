/*
  ==============================================================================

    Look.cpp
    Created: 12 Aug 2016 5:32:46pm
    Author:  John Flynn

  ==============================================================================
*/

#include "Look.h"

void look::CustomLook::drawRotarySlider (Graphics& g,
                                         int x,
                                         int y,
                                         int width,
                                         int height,
                                         float sliderPos0to1,
                                         float rotaryStartAngle,
                                         float rotaryEndAngle,
                                         Slider& slider)
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
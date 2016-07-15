/*
  ==============================================================================

    Range.h
    Created: 4 Jul 2016 8:24:01pm
    Author:  John Flynn

  ==============================================================================
*/

#ifndef RANGE_H_INCLUDED
#define RANGE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Test.h"

namespace maths
{

//==============================================================================
/** Modifies JUCE's own NormalisableRange to allow more complex logarithmic
    skew factor. (Not templated, just float.)

    @see juce::NormalisableRange

    Uses a more computationally expensive calculation than JUCE's skew
    but is more accurate for things like decade based frequency scales.

    A factor of 0.0 will be a straight line x=y, (skips calculation)
    
    A factor of 1.0 will have 1 log decade per scale, 2.0 will give 2 etc. 
    A factor of -1.0 will be the inverse of +1.0.

    For a 3 decade Hz frequency scale, start and end should be 20 and 20000 
    respectively and skewLog should be set to 3.0.
*/
class RangeLog
{
public:
    RangeLog (float rangeStart,
              float rangeEnd,
              float skewLogFactor);

    float convertTo0to1 (float v) const noexcept;

    float convertFrom0to1 (float proportion) const noexcept;

    float getStart() const noexcept { return start; }
    void setStart (float newStart);

    float getEnd() const noexcept { return end; }
    void setEnd (float newEnd);

    float getSkewLog() const noexcept { return skewLog; }
    void setSkewLog (float newSkewLog);

private:
    float start;
    float end;
    float skewLog;
};

//==============================================================================
bool operator== (const RangeLog& a, const RangeLog& b);

//==============================================================================
JF_DECLARE_UNIT_TEST_WITH_STATIC_INSTANCE (RangeLogTests)

//==============================================================================
} // namespace maths

#endif  // RANGE_H_INCLUDED

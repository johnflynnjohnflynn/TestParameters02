/*
  ==============================================================================

    Range.cpp
    Created: 5 Jul 2016 7:34:19pm
    Author:  John Flynn

  ==============================================================================
*/

#include "Range.h"

namespace jf
{

//==============================================================================
bool operator== (const RangeLog& a, const RangeLog& b)
{
    return a.getStart()    == b.getStart()
        && a.getEnd()      == b.getEnd()
        && a.getSkewLog()  == b.getSkewLog();
}

bool isGoodRangeLog (float start, float end)
{
    return (end > start);       // invariants here
}

void checkRangeLog (float start, float end) // skewLog can be any value
{
   #if JF_UNIT_TESTS
    if (! isGoodRangeLog (start, end)) throw std::logic_error ("Invalid\n");
   #endif // JF_UNIT_TESTS

    jassert (isGoodRangeLog (start, end));
}

//==============================================================================
RangeLog::RangeLog (float rangeStart,
                    float rangeEnd,
                    float skewLogFactor)
    : start (rangeStart),
      end (rangeEnd),
      skewLog (skewLogFactor)
{
    checkRangeLog (start, end);
}

float RangeLog::convertTo0to1 (float v) const noexcept
{
    float proportion = (v - start) / (end - start);

    if (skewLog != 0.0f)
    {
        const float tenPowSkewLog = std::pow (10.0f, skewLog);
        proportion = (std::log10 ((proportion * (tenPowSkewLog - 1.0f)) + 1.0f))
                    / std::log10 (tenPowSkewLog);
    }

    return proportion;
}

float RangeLog::convertFrom0to1 (float proportion) const noexcept
{
    if (skewLog != 0.0f)
    {
        const float tenPowSkewLog = std::pow (10.0f, skewLog);
        proportion = (std::pow (tenPowSkewLog, proportion) - 1.0f)
                   / (tenPowSkewLog - 1.0f);
    }

    return start + ((end - start) * proportion);
}

void RangeLog::setStart (float newStart)
{
    checkRangeLog (newStart, end);
    start = newStart;
}

void RangeLog::setEnd (float newEnd)
{
    checkRangeLog (start, newEnd);
    end = newEnd;
}

void RangeLog::setSkewLog (float newSkewLog)
{
    checkRangeLog (start, end);
    skewLog = newSkewLog;
}

//==============================================================================
} // namespace jf

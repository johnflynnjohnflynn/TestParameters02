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
/** Non-member == */
bool operator== (const RangeLog& a, const RangeLog& b)
{
    return a.getStart()    == b.getStart()
        && a.getEnd()      == b.getEnd()
        && a.getSkewLog()  == b.getSkewLog();
}

/** Check invariants hold */
bool isGoodRangeLog (float start, float end)
{
    return (end > start);
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
#if JF_UNIT_TESTS

class RangeLogTests  : public UnitTest
{
public:
    RangeLogTests()
        : UnitTest ("RangeLog")
    {
    }

    bool floatEqualApprox (float a, float b)
    {
        return std::abs(b - a) < 0.01;
    }

    void runTest() override
    {
        Random rnd = getRandom();

        beginTest ("Constructor");
        expectDoesNotThrow ((RangeLog {0, 1, 0}));

        beginTest ("checkRangeLog()");
        expectDoesNotThrow ((RangeLog {-50, 50, -2}));
        expectThrows ((RangeLog {0, -1, 0})); // end before start
        expectThrows ((RangeLog {0, 0, 0}));  // end == start

        beginTest ("convertTo0to1()");
        RangeLog r0to127 {0, 127, 0};
        expect (r0to127.convertTo0to1 (127)  == 1.0f);
        expect (r0to127.convertTo0to1 (0)    == 0.0f);
        expect (r0to127.convertTo0to1 (63.5) == 0.5f);

        RangeLog rFreq {20, 20000, 3}; // 3 decade log frequency scale
        expect (rFreq.convertTo0to1 (20000) == 1.0f);
        expect (rFreq.convertTo0to1 (20)    == 0.0f);
        expect (floatEqualApprox (rFreq.convertTo0to1 (632.456), 0.5f));
        expect (floatEqualApprox (rFreq.convertTo0to1 (200), 0.333f));
        expect (floatEqualApprox (rFreq.convertTo0to1 (2000), 0.666f));
        expect (floatEqualApprox (rFreq.convertTo0to1 (6300), 0.833));

        beginTest ("convertFrom0to1()");
        expect (floatEqualApprox (rFreq.convertFrom0to1 (0.5), 632.456f));
        expect (floatEqualApprox (rFreq.convertFrom0to1 (0.0), 20.0f));
        expect (floatEqualApprox (rFreq.convertFrom0to1 (1.0), 20000.0f));
        expect (floatEqualApprox (rFreq.convertFrom0to1 (0.33333), 200.0f));
        expect (floatEqualApprox (rFreq.convertFrom0to1 (0.666666), 2000.0f));
        expect (floatEqualApprox (rFreq.convertFrom0to1 (0.8333333), 6324.56f));
                                                         // long decimals needed, why?

                                    // Todo: beginTest ("RangeLog::snapToLegalValue()");

        RangeLog rMembSets {0, 1, 0};
        RangeLog r1       {0, 1, 0};

        beginTest ("setStart()");
        expect (rMembSets == r1);
        expectThrows (rMembSets.setStart(99999));
        expect (rMembSets == r1);
        expectDoesNotThrow (rMembSets.setStart(-1));
        expectDoesNotThrow (rMembSets.setStart(0));
        expect (rMembSets == r1);

        beginTest ("setEnd()");
        expectThrows (rMembSets.setEnd(-99999));
        expectDoesNotThrow (rMembSets.setEnd(99));
        expectDoesNotThrow (rMembSets.setEnd(1));
        expect (rMembSets == r1);
        
        beginTest ("setSkewLog()");
        for (int i = 0; i < 1000; ++i)
            expectDoesNotThrow (rMembSets.setSkewLog (rnd.nextFloat()));
    }
};

static RangeLogTests rangeTests;

#endif // JF_UNIT_TESTS

} // namespace jf

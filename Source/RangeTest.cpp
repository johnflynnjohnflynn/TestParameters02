/*
  ==============================================================================

    RangeTest.cpp
    Created: 8 Jul 2016 9:13:18pm
    Author:  John Flynn

  ==============================================================================
*/

#include "Range.h"

namespace jf
{

//==============================================================================
#if JF_UNIT_TESTS

RangeLogTests::RangeLogTests()
    : UnitTest ("RangeLog")
{
}

bool floatEqualApprox (float a, float b)
{
    return std::abs(b - a) < 0.01;
}

void RangeLogTests::runTest()
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
    expect (floatEqualApprox (rFreq.convertTo0to1 (632.456f), 0.5f));
    expect (floatEqualApprox (rFreq.convertTo0to1 (200), 0.333f));
    expect (floatEqualApprox (rFreq.convertTo0to1 (2000), 0.666f));
    expect (floatEqualApprox (rFreq.convertTo0to1 (6300), 0.833f));

    beginTest ("convertFrom0to1()");
    expect (floatEqualApprox (rFreq.convertFrom0to1 (0.5), 632.456f));
    expect (floatEqualApprox (rFreq.convertFrom0to1 (0.0), 20.0f));
    expect (floatEqualApprox (rFreq.convertFrom0to1 (1.0), 20000.0f));
    expect (floatEqualApprox (rFreq.convertFrom0to1 (0.33333f), 200.0f));
    expect (floatEqualApprox (rFreq.convertFrom0to1 (0.666666f), 2000.0f));
    expect (floatEqualApprox (rFreq.convertFrom0to1 (0.8333333f), 6324.56f));
                                                     // long decimals needed, why?

    RangeLog rMembSets {0, 1, 0};
    RangeLog r1        {0, 1, 0};

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

#endif // JF_UNIT_TESTS

//==============================================================================
} // namespace jf

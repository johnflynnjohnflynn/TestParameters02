/*
  ==============================================================================

    StateTest.cpp
    Created: 28 Jul 2016 9:46:22pm
    Author:  John Flynn

  ==============================================================================
*/

#include "State.h"

namespace state
{

//==============================================================================
#if JF_UNIT_TESTS

StateTests::StateTests()
    : UnitTest ("State")
{
}

void StateTests::runTest()
{
    //beginTest ("makeValidXmlName(): Empty string");
    //expect (makeValidXmlName("") == "_");
}

#endif // JF_UNIT_TESTS

//==============================================================================
} // namespace state

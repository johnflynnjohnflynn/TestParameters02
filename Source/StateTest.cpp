/*
  ==============================================================================

    StateTest.cpp
    Created: 28 Jul 2016 9:46:22pm
    Author:  John Flynn

  ==============================================================================
*/

#include "State.h"
#include "Parameter.h"

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
    beginTest("state::createFileIfNonExistant()");
    File file {File::getSpecialLocation (File::userApplicationDataDirectory)
               .getChildFile ("JohnFlynn/TestParameters02/unit-test-createFileIfNonExistant")};
    expect (! file.exists());

    state::createFileIfNonExistant(file);
    expect (file.exists());

    state::createFileIfNonExistant(file);
    expect (file.exists());

    file.deleteFile();
    expect (! file.exists());
}

#endif // JF_UNIT_TESTS

//==============================================================================
} // namespace state

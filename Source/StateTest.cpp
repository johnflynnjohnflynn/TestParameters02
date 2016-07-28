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
    beginTest ("makeValidXmlName(): Empty string");
    expect (makeValidXmlName("") == "_");
    
    beginTest ("makeValidXmlName(): Good string");
    expect (makeValidXmlName("laksjf0923490283SDFLKDF") == "laksjf0923490283SDFLKDF");
    
    beginTest ("makeValidXmlName(): Brute force all good characters");
    expect (makeValidXmlName("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890_")
                             == "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890_");
    
    beginTest ("makeValidXmlName(): Some bad chars");
    expect (makeValidXmlName("lwekf$%lks(&3jdsfli<>#sdlk") == "lwekflks3jdsflisdlk");
    
    beginTest ("makeValidXmlName(): Only bad chars");
    expect (makeValidXmlName("<>:;?\[]") == "_");
    
    beginTest ("makeValidXmlName(): Some spaces");
    expect (makeValidXmlName("slkdfj sdlfkj sdlkfj") == "slkdfjsdlfkjsdlkfj");
    
    beginTest ("makeValidXmlName(): Starting with numbers");
    expect (makeValidXmlName("293847skdjfwne2343kjhw skdjhf wer njs%^&") == "skdjfwne2343kjhwskdjhfwernjs");
    
    beginTest ("makeValidXmlName(): Starting with underscores");
    expect (makeValidXmlName("_2w93wer_njs%^&") == "w93wer_njs");
}

#endif // JF_UNIT_TESTS

//==============================================================================
} // namespace state

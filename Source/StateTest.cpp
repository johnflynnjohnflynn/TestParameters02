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
    beginTest ("makeValidIdentifier(): Empty string");
    expect (makeValidIdentifier("") == "_");
    
    beginTest ("makeValidIdentifier(): Good string");
    expect (makeValidIdentifier("laksjf0923490283SDFLKDF") == "laksjf0923490283SDFLKDF");
    
    beginTest ("makeValidIdentifier(): Brute force all good characters");
    expect (makeValidIdentifier("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890_")
                             == "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890_");
    
    beginTest ("makeValidIdentifier(): Some bad chars");
    expect (makeValidIdentifier("lwekf$%lks(&3jdsfli<>#sdlk") == "lwekflks3jdsflisdlk");
    
    beginTest ("makeValidIdentifier(): Only bad chars");
    expect (makeValidIdentifier("<>:;?\[]") == "_");
    
    beginTest ("makeValidIdentifier(): Some spaces");
    expect (makeValidIdentifier("slkdfj sdlfkj sdlkfj") == "slkdfjsdlfkjsdlkfj");
}

#endif // JF_UNIT_TESTS

//==============================================================================
} // namespace state

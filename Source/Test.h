/*
  ==============================================================================

    Test.h
    Created: 4 Jul 2016 8:01:54pm
    Author:  John Flynn

  ==============================================================================
*/

#ifndef TESTJF_H_INCLUDED
#define TESTJF_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

namespace test {

//==============================================================================
class ConsoleLogger : public Logger
{
    //void logMessage (const String& message) override; // uncomment and customise these if needed
};

//==============================================================================
class ConsoleUnitTestRunner : public UnitTestRunner
{
    //void logMessage (const String& message) override;
};

//==============================================================================
/**
    Creates a UnitTestRunner then calls runAllTests()
*/
void runUnitTests();

} // namespace test

#endif  // TESTJF_H_INCLUDED

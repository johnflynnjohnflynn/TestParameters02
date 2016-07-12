/*
  ==============================================================================

    Test.cpp
    Created: 4 Jul 2016 9:22:40pm
    Author:  John Flynn

  ==============================================================================
*/

#include "Test.h"

namespace jf
{

//==============================================================================
void runUnitTests()
{
    ScopedPointer<ConsoleLogger> logger;
    Logger::setCurrentLogger (logger);

    ConsoleUnitTestRunner runner;
    runner.runAllTests();
}

//==============================================================================
} // namespace jf
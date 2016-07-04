/*
  ==============================================================================

    Test.cpp
    Created: 4 Jul 2016 9:22:40pm
    Author:  John Flynn

  ==============================================================================
*/

#include "Test.h"

namespace test {

//==============================================================================
/*void ConsoleLogger::logMessage (const String& message) override
{
    std::cout << message << std::endl;
}*/

//==============================================================================
/*void ConsoleUnitTestRunner::logMessage (const String& message)
{
    Logger::writeToLog (message);
}*/

//==============================================================================
void runUnitTests()
{
    ScopedPointer<ConsoleLogger> logger;
    Logger::setCurrentLogger (logger);

    ConsoleUnitTestRunner runner;
    runner.runAllTests();
}

} // namespace test
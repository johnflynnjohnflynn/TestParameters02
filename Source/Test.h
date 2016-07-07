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

namespace jf {

//==============================================================================
class ConsoleLogger : public Logger {};
class ConsoleUnitTestRunner : public UnitTestRunner {};

//==============================================================================
/** Namespace level method creates a UnitTestRunner then calls runAllTests() 
    when JF_UNIT_TESTS=1 preprocessor flag set in Jucer.

   #if JF_UNIT_TESTS
    jf::runUnitTests();
   #endif
   
    ...in plugin processor's constructor will run all unit tests automatically. 
    You will probably need an instance of the class in the plugin somewhere so
    that at the static unit test member is created.

    See bottom of classes for unit tests i.e. @see RangeLog
    
    Leaked object assertions? Remember to set JF_UNIT_TEST=0 and search for a 
    problem jassert outside of the tests.
*/
void runUnitTests();

} // namespace jf

#endif  // TESTJF_H_INCLUDED
